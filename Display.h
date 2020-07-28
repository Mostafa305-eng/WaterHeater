/* 
 * File:  Display.h 
 * Author: Metwaly
 * Comments:
 * Revision history: 
 */


#ifndef DISPLAY_H_
#define DISPLAY_H_

/************************************************************************/
/*				 I				INCLUDES						        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"

/************************************************************************/
/*								 DEFINES						        */
/************************************************************************/


#define NO_DISPLAY               0
#define BLINKING_DISPLAY         1
#define CONTINUOUS_DISPLAY       2

/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/



/*****************************************************************************
 * Description: Initialize the display module
 * @param : 
 *
 *****************************************************************************/
void Display_Init(void);


/**************************************************************************************************
 * Description: Update the display module
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 ************************************************************************************************/
void Display_Update(void);



/*****************************************************************************
 * Description: Set the data that will be displayed 
 * @param u8_DisplayData: the data will be displayed
 *        u8_DisplayMode : determine if the display is blinking or continuous 
 *                          or there is no displaying 
 *****************************************************************************/

void Display_SetData(uint8 u8_DisplayData,uint8 u8_DisplayMode);


/*****************************************************************************
 * Description: Turn off the display immediately
 * @param 
 *****************************************************************************/

void Display_TurnOff(void);




#endif