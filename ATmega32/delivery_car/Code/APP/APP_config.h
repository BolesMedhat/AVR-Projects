#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_


/*Set the DIO Ports:
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define RIGHT_MOTOR_PORT			DIO_PORTC	/* Port used for the right motors control pins */
#define LEFT_MOTOR_PORT				DIO_PORTC	/* Port used for the left motors control pins */

#define FRONT_USONIC_PORT			DIO_PORTB	/* Port used for the front ultrasonic sensor */
#define BACK_USONIC_PORT			DIO_PORTB	/* Port used for the back ultrasonic sensor */

#define BUZZER_PORT					DIO_PORTD	/* Port used for the buzzer control pin */



/*Set the DIO Pins:
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
#define RIGHT_MOTOR_F_PIN			DIO_PIN0	/* First pin for right motors */
#define RIGHT_MOTOR_S_PIN			DIO_PIN1	/* Second pin for right motors */

#define LEFT_MOTOR_F_PIN			DIO_PIN2	/* First pin for left motors */
#define LEFT_MOTOR_S_PIN			DIO_PIN3	/* Second pin for left motors */

#define FRONT_USONIC_ECHO_PIN		DIO_PIN0	/* Echo input pin for front ultrasonic sensor */
#define FRONT_USONIC_TRIG_PIN		DIO_PIN1	/* Trigger output pin for front ultrasonic sensor */

#define BACK_USONIC_ECHO_PIN		DIO_PIN2	/* Echo input pin for back ultrasonic sensor */
#define BACK_USONIC_TRIG_PIN		DIO_PIN3	/* Trigger output pin for back ultrasonic sensor */

#define BUZZER_PIN					DIO_PIN6	/* Output pin connected to the buzzer */


#endif /* APP_CONFIG_H_ */
