/****************************************************************************
 * @file    APP.h
 * @author  Boles Medhat
 * @brief	Simon says Application Header File - ATmega32
 * @version 1.0
 * @date    [2024-12-02]
 *
 * @details
 * This header defines the interface for the main application logic of a
 * Simon Says-style memory game implemented on the AVR ATmega32 microcontroller.
 * The game uses LEDs and buttons to test memory, with increasing difficulty
 * per level. It utilizes lower-level drivers such as DIO, LCD, and Delay.
 *
 * @note
 * - Ensure APP_config.h is properly set before building the application.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ***************************************************************************/

#ifndef APP_H_
#define APP_H_


/*--------------------------- Include Dependencies --------------------------*/
#include "APP_config.h"
#include "APP_def.h"

#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"

#include "../HAL/LCD/LCD.h"

#include <stdlib.h>


/*---------------------------- Function Prototypes --------------------------*/


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
void APP_Init(void);


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
void APP_main_loop(void);


#endif /* APP_H_ */
