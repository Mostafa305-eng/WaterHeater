/*
 * LM35.c
 *
 * Created: 1/24/2020 2:30:03 PM
 *  Author: Mostafa Metwaly
 */ 
/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/

#include "common_macros.h"
#include "std_types.h"

#include "LM35.h"
#include "ADC.h"
#include"DIO.h"
#include "LM35_Config.h"

/******************************************************************************************
*                                                                                         *
*                                        DEFINES                                          *
*																						  *
*																						  *
*******************************************************************************************/
#define CONVERT_TO_CELLICOUS		4.88/10

/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/
uint16 u16_ADCReading;


/************************************************************************/
/*						FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


void LM_ReadingADC_CBK(void)
{
	ADC_ReadResult(&u16_ADCReading);
}
/**************************************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function initializes the LM35 module.
 * 							
 **************************************************************************/
extern void LM_init(void)
{
    ADC_init(A_A_A_A,ADC_RIGHT_ADJUST,ADC_POLLING_MODE,ADC_PRESCALER_32,NULL);

#if LM35_CHANNEL == ADC_CHANNEL_0
    DIO_Write(GPIOA,BIT0,INPUT);
#elif LM35_CHANNEL == ADC_CHANNEL_1
    DIO_Write(GPIOA,BIT1,INPUT);
#elif LM35_CHANNEL == ADC_CHANNEL_2
    DIO_Write(GPIOA,BIT2,INPUT);
#elif LM35_CHANNEL == ADC_CHANNEL_3
    DIO_Write(GPIOA,BIT3,INPUT);
#endif

	u16_ADCReading=0;	

}


/**************************************************************************************************
 * Description: Update the reading of lm35
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 ************************************************************************************************/
extern void LM_Update(void)
{
        ADC_startConversion(ADC_CHANNEL_2);
        ADC_ReadResult(&u16_ADCReading);
}

/**************************************************************************
 * Input: 
 * Output: pu8_temperature ==> value of reading
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function reads temperature from LM35 module.
 * 							
 **************************************************************************/
extern void LM_Read(uint8 *pu8_temperature)
{
	*pu8_temperature = (u16_ADCReading * CONVERT_TO_CELLICOUS);
	//u16_ADCReading=0;

}