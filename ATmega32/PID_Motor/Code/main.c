/****************************************************************************
 * @file    main.c
 * @author  Boles Medhat
 * @brief   PID Motor Control Application - ATmega32
 * @version 1.0
 * @date    [2024-05-20]
 *
 * @details
 * This application implements a closed-loop PID controller for DC motor
 * position control using the AVR ATmega32 microcontroller. The system
 * supports both digital and analog PID tuning:
 *
 * - In **digital mode**, the user is prompted via UART to enter the Kp, Ki,
 *   and Kd values, and the desired setpoint.
 * - In **analog mode**, these values are dynamically read from ADC channels.
 *   Analog mode is the **default** if no UART input is received within 5 seconds.
 *
 * The PID controller is executed periodically using Timer2 interrupts.
 * The output is applied to a DC motor using PWM (Timer0) and direction control
 * pins, with optional DAC output for oscilloscope visualization.
 *
 * Core components:
 * - ADC for feedback and tuning input.
 * - UART for digital input and live monitoring.
 * - Timer0 for PWM output.
 * - Timer2 for fixed-interval ISR-based control.
 * - DIO for motor control and DAC emulation.
 *
 * @note
 * - The control loop runs every 20 ms (SAMPLE_MS).
 * - DAC (R-2R ladder assumed) output is optional and intended for debugging/monitoring.
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ***************************************************************************/


#include "APP/APP.h"





/*
 * @brief Main entry point for the PID motor control application.
 *
 * Initializes all system modules and enters the main loop to handle
 * UART interaction and monitor system behavior.
 */
int main(void)
{
	/* Initialize application components: UART, ADC, timers, motor, etc. */
	APP_Init();

	/* Enter the main control loop (interrupt-driven PID execution) */
	APP_main_loop();

	/* Infinite loop to ensure the program doesn't exit */
	while(1);

	return 0;
}



