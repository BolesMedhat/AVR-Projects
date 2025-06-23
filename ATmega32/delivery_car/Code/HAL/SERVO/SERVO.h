/****************************************************************************
 * @file    SERVO.h
 * @author  Boles Medhat
 * @brief   Servo Motor Driver Header File
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

#ifndef SERVO_H_
#define SERVO_H_

#include "../../MCAL/TIMER1/TIMER1.h"
#include "../../MCAL/DIO/DIO.h"
#include "SERVO_def.h"


/*
 * @brief Sets the angle of a servo motor by its unique ID.
 *
 * This function sets the desired angle of the servo.
 * The angle must be within the valid range of -90 to 90 degrees.
 *
 * @param angle:    The desired angle for the servo (in degrees).
 */
void SERVO_SetAngle( sint8 angle );


#endif /* SERVO_H_ */
