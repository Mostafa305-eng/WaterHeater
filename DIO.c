/*
*	File name: GPIO.c
*	Author : Metwally
*
*/

/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "DIO.h"
#include <pic16f877a.h>



/************************************************************************/
/*                          	 DEFINES                		        */
/************************************************************************/


#define PORTA_DATA 	(PORTA)
#define PORTA_DIR  	(TRISA)


#define PORTB_DATA 	(PORTB)
#define PORTB_DIR  	(TRISB)

#define PORTC_DATA 	(PORTC)
#define PORTC_DIR  	(TRISC)


#define PORTD_DATA 	(PORTD)
#define PORTD_DIR  	(TRISD)

#define PORTE_DATA  (PORTE)
#define PORTE_DIR  	(TRISE)


/************************************************************************/
/*				  DIO FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/*****************************************************************************
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*	direction   -> The desired value
*					- OUTPUT
*					- INPUT
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*****************************************************************************/

void DIO_init(uint8 u8_port, uint8 u8_pins, uint8 u8_direction)
{
    switch(u8_port)
	{
		case GPIOA :
			if (u8_direction)
			{
				SET_BIT(PORTA_DIR,u8_pins);
			}
			else
			{
				CLR_BIT(PORTA_DIR,u8_pins);
			}
			break;
		case GPIOB :
			if (u8_direction)
			{
				SET_BIT(PORTB_DIR,u8_pins);
			}
			else
			{
				CLR_BIT(PORTB_DIR,u8_pins);
			}
			break;
		case GPIOC :
			if (u8_direction)
			{
				SET_BIT(PORTC_DIR,u8_pins);
			}
			else
			{
				CLR_BIT(PORTC_DIR,u8_pins);
			}
			break;
		case GPIOD :
			if (u8_direction)
			{
				SET_BIT(PORTD_DIR,u8_pins);
			}
			else
			{
				CLR_BIT(PORTD_DIR,u8_pins);
			}
			break;
		case GPIOE :
			if (u8_direction)
			{
				SET_BIT(PORTE_DIR,u8_pins);
			}
			else
			{
				CLR_BIT(PORTE_DIR,u8_pins);
			}
			break;
        default :
            /*do nothing*/
            break;
        }
}


/***************************************************************************
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: No output
*In/Out: No In/Out
*Description: This function can set or clear the value of a full port, a nibble
* 			  or even one pin.
*******************************************************************************/
void DIO_Write (uint8 u8_GPIO, uint8 u8_pins, uint8 u8_value)
{
    switch(u8_GPIO)
	{
		case GPIOA :
			if (u8_value)
			{
				SET_BIT(PORTA_DATA,u8_pins);
			}
			else
			{
				CLR_BIT(PORTA_DATA,u8_pins);
			}
			break;
		case GPIOB :
			if (u8_value)
			{
				SET_BIT(PORTB_DATA,u8_pins);
			}
			else
			{
				CLR_BIT(PORTB_DATA,u8_pins);
			}
			break;
		case GPIOC :
			if (u8_value)
			{
				SET_BIT(PORTC_DATA,u8_pins);
			}
			else
			{
				CLR_BIT(PORTC_DATA,u8_pins);
			}
			break;
		case GPIOD :
			if (u8_value)
			{
				SET_BIT(PORTD_DATA,u8_pins);
			}
			else
			{
				CLR_BIT(PORTD_DATA,u8_pins);
			}
			break;
		case GPIOE :
			if (u8_value)
			{
				SET_BIT(PORTE_DATA,u8_pins);
			}
			else
			{
				CLR_BIT(PORTE_DATA,u8_pins);
			}
			break;
        default :
            /*do nothing*/
            break;
	}
}

/******************************************************************************
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: data -> the acquired data which could be PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
******************************************************************************/
void DIO_Read (uint8 u8_GPIO,uint8 u8_pins, uint8 *pu8_data)
{
    switch(u8_GPIO)
	{
		case GPIOA :
			if(GET_BIT(PORTA_DATA,u8_pins))
			{
                *pu8_data = HIGH;
			}
			else
            {
                *pu8_data = LOW;
			}
			break;
		case GPIOB :
			if(GET_BIT(PORTB_DATA,u8_pins))
			{
                *pu8_data = HIGH;
			}
			else
            {
                *pu8_data = LOW;
			}
			break;
		case GPIOC :
			if(GET_BIT(PORTC_DATA,u8_pins))
			{
                *pu8_data = HIGH;
			}
			else
            {
                *pu8_data = LOW;
			}
			break;
		case GPIOD :
			if(GET_BIT(PORTD_DATA,u8_pins))
			{
                *pu8_data = HIGH;
			}
			else
            {
                *pu8_data = LOW;
			}
			break;
		case GPIOE :
			if(GET_BIT(PORTE_DATA,u8_pins))
			{
                *pu8_data = HIGH;
			}
			else
            {
                *pu8_data = LOW;
			}
			break;
        default :
            /*do nothing*/
            break;
	}

}

/******************************************************************************
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output:  No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*****************************************************************************/
void DIO_Toggle (uint8 u8_GPIO, uint8 u8_pins)
{
	switch (u8_GPIO)
	{
		case GPIOA :
			TOGGLE_BIT(PORTA_DATA,u8_pins);
			break;
		case GPIOB :
			TOGGLE_BIT(PORTB_DATA,u8_pins);
			break;
		case GPIOC :
			TOGGLE_BIT(PORTC_DATA,u8_pins);
			break;
		case GPIOD :
			TOGGLE_BIT(PORTD_DATA,u8_pins);
			break;
		case GPIOE :
			TOGGLE_BIT(PORTE_DATA,u8_pins);
			break;
        default :
            /*do nothing*/
            break;
	}
}


/*****************************************************************************
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: No output
*In/Out: No In/Out
*Description: This function can write a value directly on full port
* 			  
*******************************************************************************/
void DIO_PortWrite (uint8 u8_GPIO, uint8 u8_value)
{
	switch (u8_GPIO)
	{
		case GPIOA :
			PORTA_DATA = u8_value ;
			break;
		case GPIOB :
			PORTB_DATA = u8_value ;
			break;
		case GPIOC :
			PORTC_DATA = u8_value ;
			break;
		case GPIOD :
			PORTD_DATA = u8_value ;
			break;
		case GPIOE :
			PORTE_DATA = u8_value ;
			break;
	}
}
