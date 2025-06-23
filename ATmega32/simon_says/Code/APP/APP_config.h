/****************************************************************************
 * @file    APP_config.h
 * @author  Boles Medhat
 * @brief	Configuration Header File for Simon says Game Application
 * @version 1.0
 * @date    [2024-12-02]
 *
 * @details
 * This header defines constants related to the game levels in the simon says.
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


/*Set the DIO Ports for blue, yellow, green, and red buttons:
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define BUTTON_PORT					DIO_PORTD



/*Set the DIO Pin for blue, yellow, green, and red buttons:
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
#define B_BUTTON					DIO_PIN0
#define Y_BUTTON					DIO_PIN1
#define G_BUTTON					DIO_PIN2
#define R_BUTTON					DIO_PIN3



/*Set the DIO Ports for blue, yellow, green, and red leds:
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define LED_PORT					DIO_PORTD



/*Set the DIO Pin for blue, yellow, green, and red leds:
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
#define B_LED						DIO_PIN4
#define Y_LED						DIO_PIN5
#define G_LED						DIO_PIN6
#define R_LED						DIO_PIN7



/*Set random Seed ADC Channel, must be a floating (unconnected)*/
#define FLOATING_ADC_CHANNEL		ADC0


#endif /* APP_CONFIG_H_ */
