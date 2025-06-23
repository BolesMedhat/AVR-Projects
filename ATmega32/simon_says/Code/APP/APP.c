/****************************************************************************
 * @file    APP.c
 * @author  Boles Medhat
 * @brief   Simon says Application - ATmega32
 * @version 1.0
 * @date    [2024-12-02]
 *
 * @details
 * This header defines the interface for the main application logic of a
 * Simon Says-style memory game implemented on the AVR ATmega32 microcontroller.
 * The game uses LEDs and buttons to test memory, with increasing difficulty
 * per level. It utilizes lower-level drivers such as DIO, LCD, and Delay.
 *
 * The APP layer includes:
 * - Initialization of hardware components
 * - LED-based command sequence generation and display
 * - User input validation against the generated sequence
 * - Level control and game logic management
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "APP.h"





/*
 * @brief Initialize the Simon Says game components and system peripherals.
 *
 * This function sets up all necessary peripherals and game state for the Simon Says game,
 * including the ADC for randomness, DIO for button inputs, LCD for instructions and feedback,
 * and initializes any necessary game variables.
 *
 * Key Initialization Steps:
 * - ADC initialized to generate random seed values.
 * - LCD initialized to display instructions and feedback.
 * - Input buttons configured with pull-up resistors.
 * - Game memory (sequence array) cleared.
 */
void APP_Init()
{

	/* Initialize the LCD */
	LCD_Init();

	/* Initialize the ADC */
	ADC_Init();

	/* Read the floating analog pin as a random seed to ensure */
	/* different random values each time the game starts */
	srand( ADC_Read_10_Bits( FLOATING_ADC_CHANNEL ) );

	/* Disable the ADC to save power */
	ADC_Disable();

	/* Configure output pins for control leds */
	DIO_SetPinDirection( LED_PORT , B_LED , OUTPUT );
	DIO_SetPinDirection( LED_PORT , Y_LED , OUTPUT );
	DIO_SetPinDirection( LED_PORT , G_LED , OUTPUT );
	DIO_SetPinDirection( LED_PORT , R_LED , OUTPUT );

	/* Configure input pins for control buttons with pull-up resistors */
	DIO_SetPinDirection( BUTTON_PORT , B_BUTTON , INPUT_PULLUP );
	DIO_SetPinDirection( BUTTON_PORT , Y_BUTTON , INPUT_PULLUP );
	DIO_SetPinDirection( BUTTON_PORT , G_BUTTON , INPUT_PULLUP );
	DIO_SetPinDirection( BUTTON_PORT , R_BUTTON , INPUT_PULLUP );
}





/*
 * @brief Display a sequence of directional commands to the player.
 *
 * Iterates through a given array of directions and displays each one briefly using LEDs
 * or an LCD screen, depending on the hardware setup. Used to show the player the pattern
 * they must later replicate.
 *
 * @param commands: Pointer to an array of command directions (UP, DOWN, LEFT, RIGHT).
 * @param Size:     The number of commands in the sequence.
 */
void DisplayCommands ( uint8 * commands , uint16 Size )
{

	uint8 LED_PIN = 0;

	/* Loop through each command in the sequence */
	for(uint16 cmd_num = 0 ; cmd_num < Size ; cmd_num++ )
	{

		/* Map the command value to the corresponding LED pin */
		switch (commands[cmd_num])
		{
			/* Blue LED */
			case 0:
				LED_PIN = B_LED;
				break;

			/* Yellow LED */
			case 1:
				LED_PIN = Y_LED;
				break;

			/* Green LED */
			case 2:
				LED_PIN = G_LED;
				break;

			/* Red LED */
			default:

				LED_PIN = R_LED;
				break;

		}

		/* Turn the corresponding LED ON to indicate the command */
		DIO_SetPinValue( LED_PORT , LED_PIN , HIGH );

		/* Wait to let the player see the LED */
		_delay_ms( 900 );

		/* Turn the LED OFF */
		DIO_SetPinValue( LED_PORT , LED_PIN , LOW );

		/* Short pause before the next command */
		_delay_ms( 100 );
	}
}





/*
 * @brief Verify if the player’s input matches the expected command sequence.
 *
 * Waits for the player to input a sequence of directions using buttons or ADC-based analog controls.
 * Compares the input with the original command list and returns true only if all inputs match exactly.
 *
 * @param  commands: Pointer to the original command sequence.
 * @param  Size:     Number of commands in the sequence.
 *
 * @return (bool) true if the player input matches the expected sequence.
 * 				  false if any mismatch occurs in the input.
 */
bool CheckCommands ( uint8 * commands , uint16 Size )
{
	/* Array to track button states */
	uint8 buttons[4] = {0,0,0,0};

	/* Tracks whether the player succeeds */
	bool Player_Win = true;

	/* Ensures one valid press per command */
	bool Button_flag = true;

	/* Loop through all expected commands */
	for(uint16 cmd_num = 0 ; cmd_num < Size ; cmd_num++ )
	{
		while(1)
		{
			/* Read the state of each button (active LOW) */
			buttons[0] = ! DIO_GetPinValue( BUTTON_PORT , B_BUTTON );
			buttons[1] = ! DIO_GetPinValue( BUTTON_PORT , Y_BUTTON );
			buttons[2] = ! DIO_GetPinValue( BUTTON_PORT , G_BUTTON );
			buttons[3] = ! DIO_GetPinValue( BUTTON_PORT , R_BUTTON );

			/* Debounce delay */
			_delay_ms( 20 );

			/* The sum of total buttons pressed */
			uint8 sum = buttons[0] + buttons[1] + buttons[2] + buttons[3];

			/* Check that single button press detected */
			if ( (sum == 1) && (Button_flag == true) )
			{
				/* Check that this is the correct button */
				if( buttons[ commands[ cmd_num ] ] == HIGH )
				{
					/* Wait for release before accepting next input */
					Button_flag = false;

					/* Move to the next command */
					break;
				}
				/* If wrong button */
				else
				{
					/* Player loses */
					Player_Win = false;
					break;
				}

			}

			/* If all buttons released enable buttons pressed */
			else if(sum == 0)
			{
				Button_flag = true;
			}

			/* If multiple buttons pressed player loses */
			else if (sum > 1 )
			{
				Player_Win = false;
				break;
			}

		}

		/* Early exit if player already failed */
		if (Player_Win == false)
		{
			break;
		}
	}

	/* ereturn if player wins or loses */
	return Player_Win;
}





/*
 * @brief Main loop for running the Simon Says memory game.
 *
 * Continuously manages the game's progression through levels by:
 * - Generating and displaying a random sequence.
 * - Waiting for player input.
 * - Checking input correctness.
 * - Advancing to higher levels or ending the game on failure.
 *
 * The game increases in difficulty by extending the command sequence at each level.
 * Feedback is displayed through LEDs or an LCD after each round.
 */
void APP_main_loop()
{
	/* Stores the LED/button sequence */
	uint8 commands[MAX_LEVEL] ={};

	/* Current game level */
	uint16 Level = MIN_LEVEL;

	/* Index for motivational messages */
	uint8 msg_idx = 0;

	/* Predefined motivational messages shown after each successful level */
	const char lvl_msg[8][2][17] = {
	    { "   LEVEL UP!!   ", "  KEEP GOING!!  " },
	    { "   NICE WORK!   ", " NEXT ONE AHEAD " },
	    { " YOU LEVELED UP ", "  STAY SHARP!!  " },
	    { "ADVANCE MODE ON!", "DON'T LOOK BACK!" },
	    { "   GREAT JOB!   ", "NOW IT'S HARDER!" },
	    { " LOOK TO RECORD ", "  STAY FOCUSED  " },
	    { "CLIMBING HIGHER!", " STILL NOT OVER " },
	    { "NEXT LEVEL READY", "CAN YOU SURVIVE?" }
	};

	/* Generate a random command for the first level */
	for(uint16 cmd_num = 0 ; cmd_num < Level - 1 ; cmd_num++ )
	{
		commands[ cmd_num ] = rand() & 0x03;
	}

	while(1)
	{
		/* Show current level on the LCD */
		LCD_ClearScreen();
		LCD_SetCursor( 0 , 4 );
		LCD_PrintString( "LEVEL " );
		LCD_PrintNumber( Level - MIN_LEVEL + 1 );

		/* Generate a new random command for the current level */
		commands[ Level - 1 ] = rand() & 0x03;

		/* Display the sequence of commands using LEDs */
		DisplayCommands( commands , Level );

		/* Check player's response to the sequence */
		if ( CheckCommands( commands , Level ) )
		{
			/* Advance to next level */
			Level++;

			/* Check if maximum level reached */
			if ( Level == MAX_LEVEL)
			{
				/* Reset to level 1 */
				Level = MIN_LEVEL;

				/* Generate a random command for the first level */
				for(uint16 cmd_num = 0 ; cmd_num < Level - 1 ; cmd_num++ )
				{
					commands[ cmd_num ] = rand() & 0x03;
				}

				/* Show that maximum level reached on the LCD */
				LCD_ClearScreen();
				LCD_SetCursor( 0 , 3 );
				LCD_PrintString( "MAX LEVEL!" );
				LCD_SetCursor( 1 , 1 );
				LCD_PrintString( "YOU BROKE IT!!" );

				_delay_ms( 1000 );

				LCD_ClearScreen();
				LCD_SetCursor( 0 , 0 );
				LCD_PrintString( "WRAP TO LVL 1 :(" );

				_delay_ms( 1000 );

			}
			else
			{
				/* Display motivational message	 */
				LCD_ClearScreen();
				LCD_SetCursor( 0 , 0 );
				LCD_PrintString( lvl_msg[ msg_idx ][0] );
				LCD_SetCursor( 1 , 0 );
				LCD_PrintString( lvl_msg[ msg_idx ][1] );

				/* Loop message index */
				msg_idx = (msg_idx + 1) & 0x07;

				_delay_ms( 1000 );
			}


		}
		else
		{
			/* Player failed — reset level */
			Level = MIN_LEVEL;

			/* Generate a random command for the first level */
			for(uint16 cmd_num = 0 ; cmd_num < Level - 1 ; cmd_num++ )
			{
				commands[ cmd_num ] = rand() & 0x03;
			}

			/* Show game over message */
			LCD_ClearScreen();
			LCD_SetCursor( 0 , 2 );
			LCD_PrintString( "WRONG CHOICE" );
			LCD_SetCursor( 1 , 1 );
			LCD_PrintString( "GAME OVER :(" );

			_delay_ms( 500 );

			LCD_ClearScreen();
			LCD_SetCursor( 0 , 3 );
			LCD_PrintString( "Try Again!" );

			_delay_ms( 500 );
		}
	}
}










