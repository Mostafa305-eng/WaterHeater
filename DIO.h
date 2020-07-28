/*
*	File name: GPIO.h
*	Author : Metwally
*
*/

#ifndef DIO_H_INCLUDED
#define DIO_H_INCLUDED


/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"


/************************************************************************/
/*						PINS/BITS defines                               */
/************************************************************************/

#define PIN0	0x01
#define PIN1	0x02
#define PIN2	0x04
#define PIN3	0x08
#define PIN4	0x10
#define PIN5	0x20
#define PIN6	0x40
#define PIN7	0x80

#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

#define UPPER_NIBBLE	0xF0
#define LOWER_NIBBLE	0x0F
#define FULL_PORT		0xFF

#define GPIOA			0
#define GPIOB			1
#define GPIOC			2
#define GPIOD			3
#define GPIOE           4

#define OUTPUT			0x00
#define INPUT			0xFF


/************************************************************************/
/*				  GPIO FUNCTIONS PROTOTYPES				        */
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
void DIO_init(uint8 u8_port, uint8 u8_pins, uint8 u8_direction);




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
void DIO_Write (uint8 u8_GPIO, uint8 u8_pins, uint8 u8_value);




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
void DIO_Read (uint8 u8_GPIO,uint8 u8_pins, uint8 *pu8_data);



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
void DIO_Toggle (uint8 u8_GPIO, uint8 u8_pins);


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
void DIO_PortWrite (uint8 u8_GPIO, uint8 u8_value);


#endif // GPIO_H_INCLUDED
