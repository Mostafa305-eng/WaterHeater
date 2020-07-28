/* 
 * File:  Cooler.c 
 * Author: Metwaly
 * Comments:
 * Revision history: 
 */


/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "Cooler.h"
#include "Cooler_Config.h"
#include "DIO.h"



/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize the Cooler bit as output
 * 
 * 				  
 *
 *****************************************************************************/
void Cooler_Init()
{
    DIO_init(COOLER_GPIO,COOLER_BIT,OUTPUT);
}

/*****************************************************************************
 * Description: Turn on/off the cooler
 * 
 * 				  
 *
 *****************************************************************************/
void Cooler_Turn(uint8 u8_State)
{
    DIO_Write(COOLER_GPIO,COOLER_BIT,u8_State);
}