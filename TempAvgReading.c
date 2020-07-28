/*
 * File:   TempReading.c
 * Author: mosta
 *
 * Created on July 7, 2020, 5:54 PM
 */


/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/

#include"TemperatureAvgReading.h"
#include"LM35.h"


/******************************************************************************************
*                                                                                         *
*                                        DEFINES                                          *
*																						  *
*																						  *
*******************************************************************************************/
#define NO_READING_SAMPLES		10
#define LAST_SAMPLE         9


#define TR_PERIOD_MS        100
/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/
uint8 au8_TemperatureSamples[NO_READING_SAMPLES]={0,0,0,0,0,0,0,0,0,0};



uint8 u8_TR_TickCounter=0; 
/************************************************************************/
/*						FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/**************************************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function initializes the module.
 * 							
 **************************************************************************/
extern void TemperatureAVGReading_init(void)
{
    LM_init();
}



/**************************************************************************************************
 * Description: Update the reading of lm35
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 ************************************************************************************************/
extern void TemperatureAVGReading_Update(void)
{
        u8_TR_TickCounter += TICK_MS;

    if (u8_TR_TickCounter != TR_PERIOD_MS){
        return;
    }
    
    u8_TR_TickCounter = 0 ;
    
    
    uint8 u8_LMTemperature;
    uint8 u8_LoopCounter;

    LM_Update();
    LM_Read(&u8_LMTemperature);

    for(u8_LoopCounter=0;u8_LoopCounter < (NO_READING_SAMPLES-1);u8_LoopCounter++)
    {
        au8_TemperatureSamples[u8_LoopCounter] = au8_TemperatureSamples[(u8_LoopCounter+1)];
    }
    
    au8_TemperatureSamples[LAST_SAMPLE]=u8_LMTemperature;
    
    
}



/**************************************************************************
 * Input: 
 * Output: pu8_AVGtemperature ==> value of reading
 * In/Out:			
 * Return: 		
 * Description: This function reads AVG temperature from LM35 module.
 * 							
 **************************************************************************/
extern void TemperatureAVGReading_Read(uint8 *pu8_AVGtemperature)
{
    uint16 u16_CurrentAvgTemerature=0;
    uint8 u8_LoopCounter;
    for(u8_LoopCounter=0;u8_LoopCounter < (NO_READING_SAMPLES);u8_LoopCounter++)
    {
        u16_CurrentAvgTemerature += au8_TemperatureSamples[u8_LoopCounter];
    }   
    u16_CurrentAvgTemerature /= NO_READING_SAMPLES;
    
    *pu8_AVGtemperature=u16_CurrentAvgTemerature;
}