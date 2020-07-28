/*
 * led.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Metwaly
 */

#ifndef LED_H_
#define LED_H_

/************************************************************************/
/*				 I				INCLUDES						        */
/************************************************************************/

#include "std_types.h"
#include "std_types.h"

/************************************************************************/
/*								 DEFINES						        */
/************************************************************************/


#define LED_0	0
#define LED_1	1
#define LED_2	2
#define LED_3	3





/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/



/***************************************************************************
 * Description: Initialize the LED_x (where x 0, 1, 2, 3) as output
 * @param u8_led_ID: The led to be initialized and it takes
 * 				  one of defines
 *
 ******************************************************************************/
void Led_Init(uint8 u8_LED_ID);

/**************************************************************************
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be on
 * @param u8_led_ID: The led to be initialized and it takes
 * 				  one of defines
 *
 ************************************************************************/
void Led_On(uint8 u8_led_ID);


/*********************************************************************
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be off
 * @param u8_led_ID: The led to be initialized and it takes
 * 				  one of defines
 *
 ***********************************************************************/
void Led_Off(uint8 u8_led_ID);


/******************************************************************
 * Description: Toggle the LED_x state (where x 0, 1, 2, 3)
 * @param u8_led_ID: The led to be initialized and it takes
 * 				  one of defines
 *
 *******************************************************************/
void Led_Toggle(uint8 u8_led_ID);



#endif /* LED_H_ */
