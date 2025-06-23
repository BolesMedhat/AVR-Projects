/****************************************************************************
 * @file    main.c
 * @author  Boles Medhat
 * @brief   Entry point for the Snake Game Application - AVR ATmega32
 * @version 1.0
 * @date    [2024-12-07]
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

	/* Infinite loop to prevent exiting main */
	while(1);

	return 0;
}
