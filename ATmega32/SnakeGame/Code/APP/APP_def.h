/****************************************************************************
 * @file    APP_def.h
 * @author  Boles Medhat
 * @brief   Snake Game Definitions Header - ATmega32
 * @version 1.0
 * @date    [2024-12-07]
 *
 * @details
 * This file contains constant definitions and configuration values used
 * throughout the Snake Game application.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ***************************************************************************/

#ifndef APP_DEF_H_
#define APP_DEF_H_


/*------------------------------------------   values    ----------------------------------------*/

#define ENABLE_WRAPPING				1	/*Allows the snake to wrap around edges*/
#define DISABLE_WRAPPING			0	/*Stops the game (loss) when the snake hits an edge*/

#define SNAKE_MAX_LENGTH			MAP_WIDTH * MAP_HEIGHT	/*Maximum possible snake length (entire grid)*/

#define SNAKE_MIN_LENGTH			2	/*Initial length of the snake*/

#define MAX_FRUIT_RETRY 			10	/*Max attempts to place a new fruit in an unoccupied position*/

#define SNAKE_SPEED_BASE			20	/*Initial game speed factor; lower means faster*/

#define STOP						0	/*Snake is not moving*/
#define LEFT						1	/*Snake move left*/
#define RIGHT						2	/*Snake move right*/
#define UP							3	/*Snake move up*/
#define DOWN						4	/*Snake move down*/

#define HEAD						0	/*Index in the array of the snake's head*/
/*_______________________________________________________________________________________________*/


#endif /* APP_DEF_H_ */
