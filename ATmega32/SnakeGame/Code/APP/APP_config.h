/****************************************************************************
 * @file    APP_config.h
 * @author  Boles Medhat
 * @brief   Configuration Header File for Snake Game Application
 * @version 1.0
 * @date    [2024-12-07]
 *
 * @details
 * This file contains all configurable macros used in the Snake Game
 * application. It allows the user to easily adjust input pin assignments,
 * display settings, game dimensions, and other system-level options without
 * modifying the main application logic.
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

#include "APP_def.h"


/*Set the width and height of the snake game grid in pixels*/
#define MAP_WIDTH					16
#define MAP_HEIGHT					16



/*Set whether the snake wraps around screen edges or not:
 * choose between:
 * 1. DISABLE_WRAPPING
 * 2. ENABLE_WRAPPING
 */
#define SNAKE_WRAPPING				DISABLE_WRAPPING



/*Set the DIO Ports for up, dowm, left, and right buttons:
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define UB_PORT						DIO_PORTD
#define DB_PORT						DIO_PORTD
#define RB_PORT						DIO_PORTD
#define LB_PORT						DIO_PORTD



/*Set the DIO Pin for up, dowm, left, and right buttons:
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
#define UB_PIN						DIO_PIN3
#define DB_PIN						DIO_PIN4
#define LB_PIN						DIO_PIN5
#define RB_PIN						DIO_PIN6



/*Set the DIO Ports for seven segment data lines, and enable pins:
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define SEGMENT_PORT				DIO_PORTC
#define SEGMENT_E_PORT				DIO_PORTB



/*Set the DIO Pin for seven segment first enable pin:
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
#define SEGMENT_FIRST_PIN			DIO_PIN0



/*Set the number of seven segment digits*/
#define SEGMENT_MUNBER				2



/*Set random Seed ADC Channel, must be a floating (unconnected)*/
#define FLOATING_ADC_CHANNEL		ADC0


#endif /* APP_CONFIG_H_ */
