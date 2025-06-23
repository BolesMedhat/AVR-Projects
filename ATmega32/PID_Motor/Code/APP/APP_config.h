/****************************************************************************
 * @file    APP_config.h
 * @author  Boles Medhat
 * @brief   Configuration Header File for PID Motor Control
 * @version 1.0
 * @date    [2024-05-20]
 *
 * @details
 * This file contains user-defined macros for configuring the PID motor control
 * application on the ATmega32 microcontroller. It defines pin assignments,
 * ADC channels, and maximum values for PID constants (Kp, Ki, Kd).
 *
 * Configuration parameters include:
 * - ADC channels for feedback, setpoint, and analog PID tuning
 * - DAC output port for optional signal visualization
 * - Motor direction and PWM control pins
 * - Sampling interval and deadband threshold
 * - Digital/Analog mode selection defaults
 *
 * @note
 * - This configuration must match your hardware wiring and display setup.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ***************************************************************************/

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_



/*Maximum value for proportional gain (Kp) when use analog mode by KP_ADC channel*/
#define KP_MAX				5


/*Maximum value for integral gain (Ki) when use analog mode by KP_ADC channel*/
#define KI_MAX				1


/*Maximum value for derivative gain (Kd) when use analog mode by KP_ADC channel*/
#define KD_MAX				1


/*Sampling interval in milliseconds for the PID loop*/
#define SAMPLE_MS			20


/*Error threshold below which no control action is taken (dead zone)*/
#define DEADBAND			5


/*Terminating character for UART string input*/
#define STOP_CHAR			' '



/*Set the DIO Port for motor (PID Actuator):
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define MOTOR_PORT			DIO_PORTB



/*Set the DIO Pins for motor (PID Actuator):
 * choose between:
 * 1. DIO_PIN0
 * 2. DIO_PIN1
 * 3. DIO_PIN2
 * 4. DIO_PIN3
 * 5. DIO_PIN4
 * 6. DIO_PIN5
 * 7. DIO_PIN6
 * 8. DIO_PIN7
 */
#define MOTOR_IN1			DIO_PIN1
#define MOTOR_IN2			DIO_PIN2



/*Set the DIO Port for DAC (Digital-to-Analog Converter):
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define DAC_PORT			DIO_PORTC



/*Set the ADC channels:
 * choose between:
 * 1. ADC0
 * 2. ADC1
 * 3. ADC2
 * 4. ADC3
 * 5. ADC4
 * 6. ADC5
 * 7. ADC6
 * 8. ADC7
 */
#define FEEDBACK_ADC		ADC0  // PA0
#define SETPOINT_ADC		ADC1  // PA1
#define KP_ADC				ADC2  // PA2
#define KI_ADC				ADC3  // PA3
#define KD_ADC				ADC4  // PA4



#endif /* APP_CONFIG_H_ */
