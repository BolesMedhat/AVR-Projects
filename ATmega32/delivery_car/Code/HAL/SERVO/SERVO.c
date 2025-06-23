/****************************************************************************
 * @file    SERVO.c
 * @author  Boles Medhat
 * @brief   Servo Motor Driver Source File
 * @version 1.0
 * @date    [2024-07-05]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This file provides an abstraction for controlling servo motors.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the TIMER1 module in TIMER1_FAST_PWM_OCR1A_MODE mode
 * 				   **before** calling SERVO function. This driver does not initialize
 *	 	 	 	   TIMER1 module in TIMER1_FAST_PWM_OCR1A_MODE mode internally.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#include "SERVO.h"


/*
 * @brief Sets the angle of a servo motor by its unique ID.
 *
 * This function sets the desired angle of the servo.
 * The angle must be within the valid range of -90 to 90 degrees.
 *
 * @param angle:    The desired angle for the servo (in degrees).
 */
void SERVO_SetAngle( sint8 angle )
{

	/* Check if the Angle is within the Valid Range and the Servo ID is Valid */
	if ( ( angle >= SERVO_MIN_ANGLE ) && ( angle <= SERVO_MAX_ANGLE ) )
	{
		/* Convert the angle to microseconds ( -90 -> 1000 US  , 90 -> 2000 US ) */
		uint16 microseconds = SERVO_MIN_PULSE_US + (angle + 90) * ( 1000.0 / 180 );

		/* Convert the microseconds to Timer Ticks for the PWM signal and Store it */
		TIMER1_SetCompare_B_Value( SERVO_US_TO_TICKS( microseconds ) );
	}
}


