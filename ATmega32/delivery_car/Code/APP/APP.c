#include "APP.h"


uint8 input_pass[ PASS_SIZE ] = {};
uint8 pass[ PASS_SIZE ] = {};


uint8 gear = MIN_GEAR;
uint8 command = STOP;
uint8 reversed_mode = STOP;


uint8 tcnt;
uint16 ovfCounts = 0;
extern uint16 g_TIMER0_Overflow;



uint16 front_distance;
uint16 back_distance;

bool front_blocked = false;
bool back_blocked  = false;

bool car_connected = true;

char uart_rx_buffer[34] = "";


struct reverse stack[ MAX_MOVES ] = {};
uint8 top = 0;


Motor right_motor = {
		RIGHT_MOTOR_PORT,
		RIGHT_MOTOR_F_PIN,
		RIGHT_MOTOR_S_PIN
};

Motor left_motor  = {
		LEFT_MOTOR_PORT,
		LEFT_MOTOR_F_PIN,
		LEFT_MOTOR_S_PIN
};

Usonic front_usonic = {
		FRONT_USONIC_PORT,
		FRONT_USONIC_ECHO_PIN,
		FRONT_USONIC_TRIG_PIN
};

Usonic back_usonic  = {
		BACK_USONIC_PORT,
		BACK_USONIC_ECHO_PIN,
		BACK_USONIC_TRIG_PIN
};




void Back_Reverse();

void Save_Move();

void UART_Get_Cmd();

void UART_Get_LCD_msg();

void Check_Connection();

void Keypad_Get_Pass( uint8 * password );

void Save_pass( uint8 * password );

bool Is_Pass_Valid();

void Check_Pass();

void Obstacle_Detection();

void APP_Init();

void APP_main_loop();




void Back_Reverse()
{
	static volatile uint16 counter = 0;
	counter++;

	if (counter < ovfCounts) return;
	counter = 0;

	if (top == 0)
	{
		MOTOR_BothStop( right_motor , left_motor );
		WDT_RESET_MCU();
		return;
	}

	top--;

	if (reversed_mode != STOP)
	{
		ovfCounts = stack[ top ].ovfs;
		TIMER0_SetTimerValue( stack[ top ].tcnt );
		TIMER2_SetCompareValue( 51 * stack[ top ].gear );
		MOTOR_SET_Direction( right_motor , left_motor , stack[ top ].mode );
	}
}

void Save_Move()
{
	if( (reversed_mode != STOP) && (top < MAX_MOVES) )
	{
		stack[ top ].tcnt = TIMER0_GetTimerValue();
		stack[ top ].ovfs = g_TIMER0_Overflow;
		stack[ top ].mode = reversed_mode;
		stack[ top ].gear = gear;

		top++;
	}

	TIMER0_RESET();
}

void UART_Get_Cmd()
{
	command = uart_rx_buffer[0];
	car_connected = true;

	switch ( command )
	{

		case FORWARD:

			MOTOR_BothForward( right_motor , left_motor );
			Save_Move();
			reversed_mode = BACKWARD;
			break;

		case BACKWARD:

			MOTOR_BothBackward( right_motor , left_motor );
			Save_Move();
			reversed_mode = FORWARD;
			break;

		case STOP:

			MOTOR_BothStop( right_motor , left_motor );
			Save_Move();
			reversed_mode = STOP;
			break;

		case STEER_RIGHT:

			MOTOR_TurnRight( right_motor , left_motor );
			Save_Move();
			reversed_mode = STEER_LEFT;
			break;

		case STEER_LEFT:

			MOTOR_TurnLeft( right_motor , left_motor );
			Save_Move();
			reversed_mode = STEER_RIGHT;
			break;

		case GEARUP:

			if(gear < MAX_GEAR)
			{
				gear++;
				TIMER2_SetCompareValue( 51 * gear );
				Save_Move();
			}
			break;


		case GEARDOWN:

			if(gear > MIN_GEAR)
			{
				gear--;
				TIMER2_SetCompareValue( 51 * gear );
				Save_Move();
			}
			break;


		case CLR_SCREEN:

			LCD_ClearScreen();
			break;

		case SEND_LCD:

			UART_Set_RX_Callback( UART_Get_LCD_msg , (uint8 *) uart_rx_buffer , 34 , UART_STOPCHAR );
			break;

		case REVERSE:

			Save_Move();

			MOTOR_BothStop( right_motor , left_motor );
			UART_InterruptDisable( UART_INT_RX_ID );
			TIMER0_SetCallback( TIMER0_OVF_ID , Back_Reverse );
			ovfCounts = 0;
			TIMER0_SetTimerValue( 255 );
			break;

		case BUZZER_ON:

			DIO_SetPinValue(BUZZER_PORT,BUZZER_PIN,HIGH);
			break;

		case BUZZER_OFF:

			DIO_SetPinValue(BUZZER_PORT,BUZZER_PIN,LOW);
			break;

	}

}

void UART_Get_LCD_msg()
{
	LCD_ClearScreen();
	LCD_PrintString(uart_rx_buffer);
	UART_Set_RX_Callback( UART_Get_Cmd , (uint8 *)uart_rx_buffer , 1 , UART_STOPCHAR );
	car_connected = true;
}

void Check_Connection()
{
	static volatile uint16 counter = 0;
	counter++;
	if(counter >= ovfCounts)
	{
		TIMER0_SetTimerValue( tcnt );
		counter = 0;

		if( car_connected == false )
		{
			Save_Move();
			MOTOR_BothStop( right_motor , left_motor );
			UART_InterruptDisable( UART_INT_RX_ID );
			TIMER0_SetCallback( TIMER0_OVF_ID , Back_Reverse );
			ovfCounts = 0;
			TIMER0_SetTimerValue( 255 );
			command = REVERSE;
		}
		else if( (command == STOP) || (command == SEND_LCD) )
		{
			car_connected = true;
		}
		else
		{
			car_connected = false;
		}
	}
}

void Keypad_Get_Pass( uint8 * password )
{
	LCD_ClearScreen();
	LCD_PrintString("set pass:");

	uint8 key;

	for ( uint8 i = 0 ; i < PASS_SIZE ; i++ )
	{
		do
		{
			key = KEYPAD_GetPressedKey();
		}while ( key == KEYPAD_NOT_PRESSED );

		password[i] = key;

		LCD_PrintCharacter( key );
		_delay_ms(500);

		LCD_SetCursor( 0 , 9 + i );
		LCD_PrintCharacter('*');

	}
	_delay_ms(500);
	LCD_ClearScreen();


}

void Save_pass( uint8 * password )
{
	EEPROM_WriteArray( PASS_ADDRESS , password , PASS_SIZE );

	LCD_ClearScreen();
	LCD_PrintString("Password is set");
	_delay_ms(1000);
	LCD_ClearScreen();
}

bool Is_Pass_Valid()
{
	for ( uint8 i = 0 ; i < PASS_SIZE ; i++ )
	{
		if( input_pass[i] != pass[i] )
		{
			LCD_ClearScreen();
			LCD_PrintString("Wrong password");

			return false;
		}
	}

	LCD_ClearScreen();
	LCD_PrintString("Password correct");

	return true;
}

void Check_Pass()
{
	uint8 key = KEYPAD_GetPressedKey();

	if ( (key != KEYPAD_NOT_PRESSED) && (key != '*') )
	{
		Keypad_Get_Pass( input_pass );

		if ( Is_Pass_Valid() )
		{

			LCD_SetCursor(1,3);
			LCD_PrintString("BOX OPENED");
			SERVO_SetAngle( 90 );
		}

		_delay_ms(1000);
		LCD_ClearScreen();

	}
	else if (key == '*')
	{
		LCD_ClearScreen();
		LCD_PrintString(" Enter old pass");
		_delay_ms(1000);

		Keypad_Get_Pass( input_pass );

		if( Is_Pass_Valid() )
		{
			LCD_SetCursor( 1 , 0 );
			LCD_PrintString(" Enter new pass");
			_delay_ms(1000);

			Keypad_Get_Pass( pass );
			Save_pass( pass );
		}
		else
		{
			_delay_ms(1000);
			LCD_ClearScreen();
		}
	}
}

void Obstacle_Detection()
{
	front_distance = USONIC_Read(front_usonic);
	back_distance = USONIC_Read(back_usonic);

	if (((command == FORWARD) || ((command == REVERSE) && (reversed_mode == FORWARD))) && front_distance < 10)
	{
		if (!front_blocked)
		{
			MOTOR_BothStop(right_motor, left_motor);
			TIMER0_Disable();
			front_blocked = true;
		}
	}
	else if (front_blocked && front_distance >= 10)
	{
		MOTOR_BothForward(right_motor, left_motor);
		TIMER0_Enable();
		front_blocked = false;
	}

	if (((command == BACKWARD) || ((command == REVERSE) && (reversed_mode == BACKWARD))) && back_distance < 10)
	{
		if (!back_blocked)
		{
			MOTOR_BothStop(right_motor, left_motor);
			TIMER0_Disable();
			back_blocked = true;
		}
	}
	else if (back_blocked && back_distance >= 10)
	{
		MOTOR_BothBackward(right_motor, left_motor);
		TIMER0_Enable();
		back_blocked = false;
	}
}

void APP_Init()
{
	TIMER0_Init();
	TIMER1_Init();
	TIMER2_Init();

	UART_Init();

	LCD_Init();

	KEYPAD_Init();


	MOTOR_Init( right_motor );
	MOTOR_Init( left_motor );


	DIO_SetPinDirection( BUZZER_PORT , BUZZER_PIN , OUTPUT );


	LCD_SetCursor( 0 , 5 );
	LCD_PrintString( "HELLO!" );

	SERVO_SetAngle( 90 );
	_delay_ms( 500 );
	SERVO_SetAngle( -90 );
	_delay_ms( 500 );

	LCD_ClearScreen();

	TIMER2_SetCompareValue( 51 * MIN_GEAR );


	if ( EEPROM_ReadByte( PASS_STATUS_ADDRESS ) == NO_PASS )
	{
		Keypad_Get_Pass( pass );
		Save_pass( pass );
		EEPROM_WriteByte( PASS_STATUS_ADDRESS , PASS_SAVED );
	}
	else
	{
		EEPROM_ReadArray( PASS_ADDRESS , pass , PASS_SIZE );
	}


	UART_Set_RX_Callback( UART_Get_Cmd , (uint8 *)uart_rx_buffer , 1 , UART_STOPCHAR );


	TIMER0_RESET();
	TIMER0_Calc_ISR_Timing_ms( 5000 , &ovfCounts , &tcnt );
	TIMER0_SetCallback( TIMER0_OVF_ID , Check_Connection );
}

void APP_main_loop()
{
	while(1)
	{
		Check_Pass();
		Obstacle_Detection();
	}
}

