/****************************************************************************
 * @file    SERVO_def.h
 * @author  Boles Medhat
 * @brief   Servo Motor Driver Definitions Header File
 * @version 1.0
 * @date    [2024-07-05]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This file contains the macro definitions, types, and constants used by the
 * Servo Motor Driver to control servo motors via PWM signals. It supports up
 * to 9 servos and utilizes Timer1 in normal mode for generating timing intervals.
 * The driver uses software PWM to handle multiple servos efficiently.
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

#ifndef SERVO_DEF_H_
#define SERVO_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*------------------------------------------   macros    ----------------------------------------*/

/*Convert Microseconds to Timer Ticks*/
#define SERVO_US_TO_TICKS( US )				( ( ( US ) * ( F_CPU / 1000000UL ) ) / ( TIMER1_PRESCALER ) )
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*Servo Angles*/
#define SERVO_MIN_ANGLE						-90											/*Minimum servo angle (0   degrees)*/
#define SERVO_MAX_ANGLE						90											/*Maximum servo angle (180 degrees)*/

/*Servo Min pulse width*/
#define SERVO_MIN_PULSE_US					1000										/*Number of microseconds in minimum pulse width (1ms)*/
/*_______________________________________________________________________________________________*/


#endif /* SERVO_DEF_H_ */
