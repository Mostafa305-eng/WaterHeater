/*
 * CFile1.c
 *
 * Created: 12/3/2019 7:43:21 PM
 *  Author: Metwaly
 */ 

/************************************************************************/
/*				 I				INCLUDES						        */
/************************************************************************/
#include "led.h"
#include "ledConfig.h"
#include "DIO.h"


 
/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/***************************************************************************
 * Description: Initialize the LED_x (where x 0, 1, 2, 3) as output
 * @param u8_led_ID: The led to be initialized and it takes
 * 				  one of defines
 *
 ******************************************************************************/

void Led_Init(uint8 u8_LED_ID){
	switch(u8_LED_ID){
		case (LED_0) :
            DIO_init(LED_0_GPIO,LED_0_BIT,OUTPUT);
			break;	
		case (LED_1) :
            DIO_init(LED_1_GPIO,LED_1_BIT,OUTPUT);
			break;	
		case (LED_2) :
            DIO_init(LED_2_GPIO,LED_2_BIT,OUTPUT);
			break;	
		case (LED_3) :
            DIO_init(LED_3_GPIO,LED_3_BIT,OUTPUT);
			break;	
		default:
			break;
	}
}


/**************************************************************************
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be on
 * @param u8_led_ID: The led to be initialized and it takes
 * 				  one of defines
 *
 ************************************************************************/

void Led_On(uint8 u8_led_ID){
	switch(u8_led_ID){
		case (LED_0) :
			DIO_Write(LED_0_GPIO, LED_0_BIT , HIGH);
			break;
		case (LED_1) :
			DIO_Write(LED_1_GPIO, LED_1_BIT , HIGH);
			break;
		case (LED_2) :
			DIO_Write(LED_2_GPIO, LED_2_BIT , HIGH);
			break;
		case (LED_3) :
			DIO_Write(LED_3_GPIO, LED_3_BIT , HIGH);
			break;
	}	
}


/*********************************************************************
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be off
 * @param u8_led_ID: The led to be initialized and it takes
 * 				  one of defines
 *
 ***********************************************************************/
void Led_Off(uint8 u8_led_ID){
	switch(u8_led_ID){
		case (LED_0) :
			DIO_Write(LED_0_GPIO, LED_0_BIT , LOW);
			break;
		case (LED_1) :
			DIO_Write(LED_1_GPIO, LED_1_BIT , LOW);
			break;
		case (LED_2) :
			DIO_Write(LED_2_GPIO, LED_2_BIT , LOW);
			break;
		case (LED_3) :
			DIO_Write(LED_3_GPIO, LED_3_BIT , LOW);
			break;
	}
}

/******************************************************************
 * Description: Toggle the LED_x state (where x 0, 1, 2, 3)
 * @param u8_led_ID: The led to be initialized and it takes
 * 				  one of defines
 *
 *******************************************************************/
void Led_Toggle(uint8 u8_led_ID){
	switch(u8_led_ID){
		case (LED_0) :
			DIO_Toggle(LED_0_GPIO, LED_0_BIT );
			break;
		case (LED_1) :
			DIO_Toggle(LED_1_GPIO, LED_1_BIT );
			break;
		case (LED_2) :
			DIO_Toggle(LED_2_GPIO, LED_2_BIT );
			break;
		case (LED_3) :
			DIO_Toggle(LED_3_GPIO, LED_3_BIT );
			break;
	}
}
	