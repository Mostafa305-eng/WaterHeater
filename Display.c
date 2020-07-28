/*
 * File:   Display.c
 * Author: mosta
 *
 * Created on July 7, 2020, 4:06 PM
 */


/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/
#include "Display.h"
#include "SSD.h"

/************************************************************************/
/*						        defines                                */
/************************************************************************/
#define SSD_DATA_UNITS  FIRST_SSD
#define SSD_DATA_TENS   SECOND_SSD


#define DISPLAY_PERIOD_MS                   40
#define BLINKING_PERIOD_MS                  1000
#define RESET_BLINKING_PERIOD_MS            2000



/************************************************************************/
/*						Static Variables                               	*/
/************************************************************************/

static uint8 u8_Data=0;
static uint8 u8_Mode=NO_DISPLAY;
static uint8 u8_DisplayTickCounter=0;
static uint16 u16_DisplayBlinkCounter=0;


/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize the display module
 * @param : 
 *
 *****************************************************************************/
void Display_Init(void)
{
    SSD_Init(SSD_DATA_UNITS);
    SSD_Init(SSD_DATA_TENS);
    
    u16_DisplayBlinkCounter=0;
    u8_DisplayTickCounter=0;
    u8_Mode=NO_DISPLAY;
    u8_Data=0;

}


/**************************************************************************************************
 * Description: Update the display module
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 ************************************************************************************************/
void Display_Update(void)
{
    u8_DisplayTickCounter += TICK_MS ;
    
    
    if (u8_DisplayTickCounter != DISPLAY_PERIOD_MS )
    {
        return;
    } 
    u8_DisplayTickCounter=0;
    
    switch(u8_Mode)
    {
        case CONTINUOUS_DISPLAY :
            SSD_SetState(SSD_DATA_UNITS,SSD_ON);
            SSD_SetState(SSD_DATA_TENS,SSD_ON);

            SSD_SetValue(SSD_DATA_UNITS,u8_Data%10);
            SSD_SetValue(SSD_DATA_TENS,u8_Data/10);
            
            u16_DisplayBlinkCounter = 0 ;
            break;
            
        case BLINKING_DISPLAY :
            u16_DisplayBlinkCounter+= DISPLAY_PERIOD_MS;
            
            if(u16_DisplayBlinkCounter >= RESET_BLINKING_PERIOD_MS)
            {
                u16_DisplayBlinkCounter=0;
            }
            else if(u16_DisplayBlinkCounter > BLINKING_PERIOD_MS)
            {
                SSD_SetState(SSD_DATA_UNITS,SSD_OFF);
                SSD_SetState(SSD_DATA_TENS,SSD_OFF);
            }
            else
            {
                SSD_SetState(SSD_DATA_UNITS,SSD_ON);
                SSD_SetState(SSD_DATA_TENS,SSD_ON);

                SSD_SetValue(SSD_DATA_UNITS,u8_Data%10);
                SSD_SetValue(SSD_DATA_TENS,u8_Data/10);                                
            }
            break;
            
            
        case NO_DISPLAY :
            SSD_SetState(SSD_DATA_UNITS,SSD_OFF);
            SSD_SetState(SSD_DATA_TENS,SSD_OFF);
            u16_DisplayBlinkCounter=0;
            break;            
            
    }
    
}



/*****************************************************************************
 * Description: Set the data that will be displayed 
 * @param u8_DisplayData: the data will be displayed
 *        u8_DisplayMode : determine if the display is blinking or continuous 
 *                          or there is no displaying 
 *****************************************************************************/
void Display_SetData(uint8 u8_DisplayData,uint8 u8_DisplayMode)
{
    u8_Data=u8_DisplayData;
    u8_Mode=u8_DisplayMode;
}




/*****************************************************************************
 * Description: Turn off the display immediately
 *
 *****************************************************************************/

void Display_TurnOff(void)
{
    SSD_TurnOff(SSD_DATA_UNITS);
    SSD_TurnOff(SSD_DATA_TENS);
    u8_Mode=NO_DISPLAY;
}
