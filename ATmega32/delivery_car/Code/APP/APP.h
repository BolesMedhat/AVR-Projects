#ifndef APP_H_
#define APP_H_


/*--------------------------- Include Dependencies --------------------------*/
#include "APP_config.h"
#include "APP_def.h"

#include "../MCAL/UART/UART.h"
#include "../MCAL/TIMER0/TIMER0.h"
#include "../MCAL/TIMER1/TIMER1.h"
#include "../MCAL/TIMER2/TIMER2.h"
#include "../MCAL/EEPROM/EEPROM.h"
#include "../MCAL/WDT/WDT.h"

#include "../HAL/LCD/LCD.h"
#include "../HAL/DC_MOTOR/MOTOR.h"
#include "../HAL/KEYPAD/Keypad.h"
#include "../HAL/USONIC/USONIC.h"
#include "../HAL/SERVO/SERVO.h"


/*---------------------------- Function Prototypes --------------------------*/



void APP_Init();



void APP_main_loop();


#endif /* APP_H_ */
