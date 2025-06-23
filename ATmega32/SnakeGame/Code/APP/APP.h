/****************************************************************************
 * @file    APP.h
 * @author  Boles Medhat
 * @brief   Snake Game Application Header File - ATmega32
 * @version 1.0
 * @date    [2024-12-07]
 *
 * @details
 * This file declares the core initialization and main loop functions for the
 * Snake Game application. It includes all necessary headers and configuration
 * files required to run the game on the ATmega32 platform.
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
#include "../MCAL/WDT/WDT.h"

#include "../HAL/SEG7/SEG7.h"
#include "../HAL/ShiftRegister/Shift.h"

#include <stdlib.h>


/*---------------------------- Function Prototypes --------------------------*/


/*
 * @brief Initialize the game application, peripherals, and game state.
 *
 * This function sets up the ADC, seeds the random number generator, initializes
 * the 7-segment display, configures input pins for control buttons with pull-ups,
 * initializes the shift register for the matrix display, and sets the initial
 * positions of the snake and fruit.
 */
void APP_Init(void);


/*
 * @brief Main game loop controlling input, game speed, logic, and display.
 *
 * Runs until the game is over. Handles input, updates snake position at intervals
 * based on score-modified speed, refreshes display, and triggers a software reset
 * on game over.
 */
void APP_main_loop(void);


#endif /* APP_H_ */
