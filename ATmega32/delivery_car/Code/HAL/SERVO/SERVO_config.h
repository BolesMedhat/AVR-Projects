/****************************************************************************
 * @file    SERVO_config.h
 * @author  Boles Medhat
 * @brief   Servo Motor Driver Configuration Header File
 * @version 1.0
 * @date    [2024-07-05]
 * @license MIT License Copyright (c) 2025 Boles Medhat
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

#ifndef SERVO_CONFIG_H_
#define SERVO_CONFIG_H_

#include "SERVO_def.h"
#include "../../MCAL/TIMER1/TIMER1.h"


/* You must initialize Timer1 manually "TIMER1_Init()" before using this driver */
#ifndef TIMER1_IN_HAL
#define TIMER1_IN_HAL
	#warning "⚠️ Initialize Timer1 manually before using this driver."
#endif


/* Configure Timer1 to Normal mode */
#if TIMER1_WAVEFORM_GENERATION_MODE != TIMER1_FAST_PWM_OCR1A_MODE
	#warning "⚠️ Configure Timer1 in TIMER1_FAST_PWM_OCR1A_MODE mode."
#endif


#endif /* SERVO_CONFIG_H_ */
