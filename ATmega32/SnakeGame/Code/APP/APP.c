/****************************************************************************
 * @file    APP.c
 * @author  Boles Medhat
 * @brief   Snake Game Application - ATmega32
 * @version 1.0
 * @date    [2024-12-07]
 *
 * @details
 * This file contains the main logic for a Snake game implemented on the
 * AVR ATmega32 microcontroller. The game uses a dot matrix display (via
 * shift registers) for rendering, and a 7-segment display for showing the score.
 * User input is read via four push buttons for direction control.
 *
 * Key Features:
 * - Snake movement, collision detection, and fruit generation logic.
 * - Speed scaling based on score.
 * - Dot matrix multiplexing for flexible display sizes.
 * - Optional snake wrapping or wall collision modes.
 * - Score display via 7-segment display.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "APP.h"


/* Display Row & Column Data */
uint32 row, columns;

/* Snake Properties */
sint8 snake_x[SNAKE_MAX_LENGTH], snake_y[SNAKE_MAX_LENGTH];
uint16 snake_len = SNAKE_MIN_LENGTH;
uint16 segment_idx;
uint8 direction = STOP;

/* Fruit Coordinates & Retry Logic */
uint8 fruit_x, fruit_y;
uint8 fruit_retry_count;

/* Game State & Speed */
uint8 score = 0;
uint8 frame_count = 0, speed_boost = 0;
bool valid_fruit;
bool game_over = false;

/* Display Matrix Coordinates */
sint8 x, y;

/* 7-Segment Display Configuration */
Seg7 score_display = {
    SEGMENT_PORT,
    SEGMENT_E_PORT,
    SEGMENT_FIRST_PIN,
    SEGMENT_MUNBER
};





/*
 * @brief Initialize the game application, peripherals, and game state.
 *
 * This function sets up the ADC, seeds the random number generator, initializes
 * the 7-segment display, configures input pins for control buttons with pull-ups,
 * initializes the shift register for the matrix display, and sets the initial
 * positions of the snake and fruit.
 */
void APP_Init()
{

	/* Initialize the ADC */
	ADC_Init();

	/* Read the floating analog pin as a random seed to ensure */
	/* different random values each time the game starts */
	srand( ADC_Read_10_Bits( FLOATING_ADC_CHANNEL ) );

	/* Disable the ADC to save power */
	ADC_Disable();

	/* Initialize 7-segment for score display */
	SEG7_Multiplex_Init( score_display );

	/* Configure input pins for control buttons with pull-up resistors */
	DIO_SetPinDirection( UB_PORT , UB_PIN , INPUT_PULLUP );
	DIO_SetPinDirection( DB_PORT , DB_PIN , INPUT_PULLUP );
	DIO_SetPinDirection( LB_PORT , LB_PIN , INPUT_PULLUP );
	DIO_SetPinDirection( RB_PORT , RB_PIN , INPUT_PULLUP );

	/* Initialize shift register for matrix display (dot/led matrix) */
	SHIFT_OUT_Init();

	/* Set initial snake head position */
	snake_x[ HEAD ] = MAP_WIDTH / 2 + 2;
	snake_y[ HEAD ] = MAP_HEIGHT / 2 - 1;

	/* Initialize snake body behind the head */
	for( segment_idx = 1 ; segment_idx < snake_len ; segment_idx++ )
	{
		snake_x[ segment_idx ] = snake_x[ segment_idx - 1 ] + 1;
		snake_y[ segment_idx ] = snake_y[ segment_idx - 1 ];
	}

	/* Place the initial fruit */
	fruit_x = MAP_WIDTH / 2 - 2;
	fruit_y = MAP_HEIGHT / 2 - 1;

}





/*
 * @brief Handle user input to update snake direction.
 *
 * Reads the status of control buttons and updates the snake's direction accordingly.
 * Prevents 180-degree turns to avoid immediate self-collision.
 */
void Input_handle()
{

	/* Check if UP button is pressed and prevent 180-degree turn from DOWN */
	if		( (DIO_GetPinValue( UB_PORT , UB_PIN ) == 0) && (direction != DOWN) )
	{
		direction = UP;
	}
	/* Check if DOWN button is pressed and prevent 180-degree turn from UP */
	else if ( (DIO_GetPinValue( DB_PORT , DB_PIN ) == 0) && (direction != UP) )
	{
		direction = DOWN;
	}
	/* Check if LEFT button is pressed and prevent 180-degree turn from RIGHT */
	else if ( (DIO_GetPinValue( LB_PORT , LB_PIN ) == 0) && (direction != RIGHT) )
	{
		direction = LEFT;
	}
	/* Check if RIGHT button is pressed and prevent 180-degree turn from LEFT */
	else if ( (DIO_GetPinValue( RB_PORT , RB_PIN ) == 0) && (direction != LEFT) )
	{
		direction = RIGHT;
	}
}





/*
 * @brief Update the snake’s position and game logic.
 *
 * Checks for fruit collision, increases snake length and score, attempts to place
 * new fruit avoiding snake's body. Updates snake segments positions and checks for
 * boundary collisions (wrapping or walls) and self-collision.
 */
void Snake_Logic()
{

	/* Check if snake eats the fruit */
	if ( ( snake_x[ HEAD ] == fruit_x ) && ( snake_y[ HEAD ] == fruit_y ) )
	{
		/* Increase snake length and update the score */
		snake_len++;
		score++;

		/* Reset retry counter for fruit placement attempts */
		fruit_retry_count = 0;


		do{

			/* Assume the new fruit position is valid initially */
			valid_fruit = true;

			/* Generate new fruit coordinates within the map size:
			 * rand() produces a 15-bit random number (0 to 32767),
			 * multiplying by MAP_WIDTH or MAP_HEIGHT and then shifting right by 15
			 * scales the random number to the range [1, MAP_WIDTH-2] or [1, MAP_HEIGHT-2]*/
			fruit_x = ( ( (uint32)rand() * (MAP_WIDTH - 2)  ) >> 15 ) + 1;
			fruit_y = ( ( (uint32)rand() * (MAP_HEIGHT - 2) ) >> 15 ) + 1;

			/* Increment the number of attempts to place fruit */
			fruit_retry_count++;

			/* Verify that the new fruit position does not overlap with any segment of the snake’s body */
			for( segment_idx = 0 ; segment_idx < snake_len ; segment_idx++ )
			{
				if( ( snake_x[ segment_idx ] == fruit_x ) && ( snake_y[ segment_idx ] == fruit_y ) )
				{
					/* Invalid position due to collision */
					valid_fruit = false;
					break;
				}
			}

		/* Repeat the process if the fruit position was invalid and the retry limit has not been exceeded */
		/* Limit the number of retries to avoid excessive delay which may cause the display to freeze */
		}while( ( valid_fruit == false ) && ( fruit_retry_count <= MAX_FRUIT_RETRY  ) );


	}

	/* Shift each segment of the snake to the position of the previous one if it move */
	if (direction != STOP)
	{
		for( segment_idx = snake_len - 1 ; segment_idx > 0  ; segment_idx-- )
		{
			snake_x[ segment_idx ] = snake_x[ segment_idx - 1 ];
			snake_y[ segment_idx ] = snake_y[ segment_idx - 1 ];
		}
	}

	/* Update head position based on direction */
	switch (direction)
	{
		case LEFT:	snake_x[ HEAD ]--;	break;
		case RIGHT:	snake_x[ HEAD ]++;	break;
		case UP:	snake_y[ HEAD ]--;	break;
		case DOWN:	snake_y[ HEAD ]++;	break;
	}

	/* Wrap the snake around the screen edges if enable */
	#if SNAKE_WRAPPING == ENABLE

		if ( snake_x[ HEAD ] < 0 )
		{
			snake_x[ HEAD ] = MAP_WIDTH - 1;
		}
		else if ( snake_x[ HEAD ] >=  MAP_WIDTH )
		{
			snake_x[ HEAD ] = 0;
		}
		else if ( snake_y[ HEAD ] < 0 )
		{
			snake_y[ HEAD ] = MAP_HEIGHT - 1;
		}
		else if ( snake_y[ HEAD ] >=  MAP_HEIGHT )
		{
			snake_y[ HEAD ] = 0;
		}

	#endif

	/* Check self-collision */
	for( segment_idx = 1 ; segment_idx < snake_len  ; segment_idx++ )
	{

		if( ( snake_x[ HEAD ] == snake_x[ segment_idx ] ) &&
			( snake_y[ HEAD ] == snake_y[ segment_idx ] ) )
		{
			game_over = true;
		}
	}

	/* Check wall collision if wrap disable */
	#if SNAKE_WRAPPING == DISABLE

		if( (snake_x[ HEAD ] == 0) || (snake_x[ HEAD ] == MAP_WIDTH - 1) ||
			(snake_y[ HEAD ] == 0) || (snake_y[ HEAD ] == MAP_HEIGHT - 1) )
		{
			game_over = true;
		}

	#endif

}





/*
 * @brief Render the current game state on the dot matrix and 7-segment display.
 *
 * Loops through each row and column, sets bits to represent the snake, fruit, and borders
 * (if wrapping disabled). Sends row and column data in 8-bit chunks to shift registers
 * and updates the 7-segment score display.
 */
void Dispaly()
{

	/* Loop on each row */
	for( y = 0 ; y < MAP_HEIGHT ; y++ )
	{
		/* Activate only the current row on the dot matrix by setting it LOW, all other rows remain HIGH */
		row = ~(1 << y);

		/* Reset the columns for this row */
		columns = 0;

		/* Iterate through all columns in this row */
		for( x  = 0 ; x < MAP_WIDTH ; x++ )
		{
			 /* Check if the current (x,y) matches any snake segment position */
			for( segment_idx = 0 ; segment_idx < snake_len  ; segment_idx++ )
			{
				if( ( snake_x[ segment_idx ] == x ) && ( snake_y[ segment_idx ] == y ) )
				{
					/* Set the corresponding bit in column to light the snake dot */
					columns |= 1 << x;
				}
			}

			/* Check if the fruit is at this position */
			if( ( fruit_x == x ) && ( fruit_y == y ) )
			{
				  /* Set the bit to display the fruit */
				columns |= 1 << x;
			}

			 /* If wrapping is disabled, mark the border cells to be lit */
			#if SNAKE_WRAPPING == DISABLE

				if( (x == 0) || (x == MAP_WIDTH - 1) || (y == 0) || (y == MAP_HEIGHT - 1) )
				{
					 /* Set the bit to display the border */
					columns |= 1 << x;
				}
			#endif

		}

		/* Send row data to the shift register in 8-bit chunks to support variable map sizes */
		for ( x = MAP_HEIGHT - 8 ; x >= 0 ; x-=8)
		{
			SHIFT_OUT_Byte( row >> x );
		}

		/* Send column data similarly in 8-bit chunks */
		for ( x = MAP_WIDTH - 8 ; x >= 0 ; x-=8)
		{
			SHIFT_OUT_Byte( columns >> x );
		}

		 /* Latch the shifted data to update the physical display */
		SHIFT_OUT_Latch();

		/* Update the 7-segment display with the current score */
		SEG7_Multiplex_Display(score_display, score);
	}
}





/*
 * @brief Main game loop controlling input, game speed, logic, and display.
 *
 * Runs until the game is over. Handles input, updates snake position at intervals
 * based on score-modified speed, refreshes display, and triggers a software reset
 * on game over.
 */
void APP_main_loop()
{

	/* Run the game loop until the player loses */
	while(game_over == false)
	{
		/* Handle user input (direction changes) */
		Input_handle();

		/* Control snake speed based on score */
		/* Apply game logic after a certain number of frame renders */
		/* Higher score means fewer frames per move → faster speed */
		if(frame_count >= ( SNAKE_SPEED_BASE - speed_boost ) )
		{
			frame_count = 0;

			/* Increase speed with score but clamp it to the base limit */
			speed_boost = score;
			if (speed_boost > SNAKE_SPEED_BASE)
			{
				speed_boost = SNAKE_SPEED_BASE;
			}

			/* Update snake movement and game logic */
			Snake_Logic();

		}

		/* Refresh display (snake, fruit, boundaries) */
		Dispaly();

		/* Increment frame counter for timing */
		frame_count++;
	}

	/* If game over, trigger a soft reset using the watchdog timer */
	WDT_RESET_MCU();
}
