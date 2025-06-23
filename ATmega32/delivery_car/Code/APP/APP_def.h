#ifndef APP_DEF_H_
#define APP_DEF_H_

#include "../LIB/STD_TYPES.h"


/*------------------------------------------   types    -----------------------------------------*/

/*Struct to store a single movement record for reverse playback*/
struct reverse
{
	uint32 mode : 3;	/*Movement mode (FORWARD, BACKWARD, etc.)*/
	uint32 gear : 3;	/*Gear level (1 to 5)*/
	uint32 ovfs : 16;	/*Number of timer overflows*/
	uint32 tcnt : 8;	/*Timer counter preload value*/
};
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*EEPROM addresses for storing password and its status and size*/
#define PASS_STATUS_ADDRESS			0x20	/* EEPROM address to check if password is set */
#define PASS_ADDRESS				0x21	/* EEPROM starting address to store the password */
#define NO_PASS						0xFF	/* Indicates that no password is currently saved */
#define PASS_SAVED					0x00	/* Indicates that a password is stored */
#define PASS_SIZE					4		/* Number of characters in the password */

/*Gear limits for the RC car*/
#define MAX_GEAR 					5		/* Maximum gear level */
#define MIN_GEAR 					1		/* Minimum gear level */

/*UART command values for car control*/
#define NOTHING						'0'		/* No command (used to confirm ongoing connection) */
#define FORWARD						'1'		/* Move the car forward */
#define BACKWARD					'2'		/* Move the car backward */
#define STOP						'3'		/* Stop both motors */
#define STEER_RIGHT					'4'		/* Turn the car right */
#define STEER_LEFT					'5'		/* Turn the car left */
#define GEARUP						'6'		/* Increase gear (speed up) */
#define GEARDOWN					'7'		/* Decrease gear (slow down) */
#define CLR_SCREEN					'8'		/* Clear LCD screen */
#define SEND_LCD					'9'		/* Receive and display LCD message over UART */
#define UART_STOPCHAR				':'		/* Indicates end of UART transmission */
#define REVERSE						';'		/* Start reverse playback of recorded path */
#define BUZZER_ON					'o'		/* Turn the buzzer ON */
#define BUZZER_OFF					'f'		/* Turn the buzzer OFF */

/*Movement recording limit for reverse playback*/
#define MAX_MOVES					300		/* Maximum number of moves to store for reverse playback */
/*_______________________________________________________________________________________________*/


#endif /* APP_DEF_H_ */
