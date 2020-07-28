/* 
 * File:  Heater.c 
 * Author: Metwaly
 * Comments:
 * Revision history: 
 */


/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "Heater.h"
#include "Heater_Config.h"
#include "DIO.h"



/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize the Heater bit as output
 * 
 * 				  
 *
 *****************************************************************************/
void Heater_Init(void)
{
    DIO_init(HEATER_GPIO,HEATER_BIT,OUTPUT);
}

/*****************************************************************************
 * Description: Turn on/off the cooler
 * 
 * 				  
 *
 *****************************************************************************/
void Heater_Turn(uint8 u8_State)
{
    DIO_Write(HEATER_GPIO,HEATER_BIT,u8_State);
}