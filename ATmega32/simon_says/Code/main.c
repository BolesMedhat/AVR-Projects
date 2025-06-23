/****************************************************************************
 * @file    main.c
 * @author  Boles Medhat
 * @brief   Entry point for the Simon Says Game Application - AVR ATmega32
 * @version 1.0
 * @date    [2024-12-07]
 *
 * @details
 * This file serves as the entry point for the Simon Says memory game implemented
 * on the AVR ATmega32 microcontroller. The game challenges the user to remember
 * and repeat sequences of LED patterns using button inputs.
 *
 * Key Features:
 * - Level-based gameplay with increasing difficulty.
 * - Randomized command sequences using ADC-seeded PRNG.
 * - LCD feedback for success, failure, and level transitions.
 * - Input via four color-coded buttons (Blue, Yellow, Green, Red).
 * - Visual command display using matching LEDs.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ***************************************************************************/

#include "APP/APP.h"


int main()
{

	/* Initialize the game application */
	APP_Init();

	/* Start the main game loop */
	APP_main_loop();

	/* Should never reach here */
	while(1);

	return 0;
}
