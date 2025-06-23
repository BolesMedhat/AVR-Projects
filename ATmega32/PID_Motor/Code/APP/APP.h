/****************************************************************************
 * @file    APP.h
 * @author  Boles Medhat
 * @brief	PID Motor Control Application Header File - ATmega32
 * @version 1.0
 * @date    [2024-05-20]
 *
 * @details
 * This application implements a real-time PID control loop using the ATmega32
 * microcontroller to control the speed or position of a DC motor. The control
 * system supports both digital and analog modes:
 *
 * - In **digital mode**, the user is prompted through UART to enter the Kp, Ki,
 *   and Kd values manually, and a desired setpoint. This is ideal for testing
 *   and real-time tuning over serial.
 *
 * - In **analog mode**, PID constants and setpoint are read from ADC channels,
 *   making the system fully autonomous. Analog mode is selected by default
 *   if no user input is received within 5 seconds.
 *
 * The control loop runs periodically using TIMER2 interrupts. The PID output
 * is applied to a DC motor using PWM via TIMER0, and direction control is
 * managed through DIO. The resulting control signal is also output via PORTC
 * for DAC-based visualization (e.g., using an R-2R ladder).
 *
 * Features:
 * - PID controller with anti-oscillation deadband
 * - UART-based user interaction
 * - Real-time ADC-based gain and setpoint input
 * - Motor direction and PWM control
 * - Optional DAC output for debugging
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

#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"
#include "../MCAL/TIMER0/TIMER0.h"
#include "../MCAL/TIMER2/TIMER2.h"
#include "../MCAL/UART/UART.h"

#include "../HAL/DC_MOTOR/MOTOR.h"

#include <util/delay.h>


/*---------------------------- Function Prototypes --------------------------*/


/*
 * @brief Initializes the main application modules.
 *
 * This function sets up UART, ADC, motor control, timers, and ISR configuration.
 * It determines whether to use digital or analog mode and prepares everything for PID control.
 */
void APP_Init(void);


/*
 * @brief Main application loop for user interaction and system monitoring.
 *
 * Continuously monitors system state and handles UART interaction for setpoint input or status reporting.
 * In digital mode, displays error and PID constants when a significant change occurs.
 * In analog mode, continuously prints system status.
 */
void APP_main_loop(void);


#endif /* APP_H_ */
