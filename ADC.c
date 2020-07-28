/*
 * File:   ADC.c
 * Author: Metwaly
 *
 * Created on July 1, 2020, 4:53 PM
 */


/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/


#include <pic16f877a.h>

#include "common_macros.h"
#include "std_types.h"

#include "ADC.h"
#include "DIO.h"


/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/
static uint8 u8_Mode;
static Ptrfunc ptrf_ADC_cbk;


/************************************************************************/
/*                          	 DEFINES                		        */
/************************************************************************/

#define ADC_CHANNEL_CONFIG_MASK 0x0F
#define ADC_ADJUST_RESULT_MASK  0x80
#define ADC_CHANNEL_MASK        0x38

#define ADCS2_BIT               0x40
#define ADCS1_BIT               0x80
#define ADCS0_BIT               0x40
#define GO_DONE_BIT             0x04
#define ADON_BIT                0x01
/************************************************************************/
/*						FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/



/******************************************************************************************
 * Input: 
 *		  uint8 u8_ADC_Channels_Config : ADC PORT CONFIG CONTROL BITS ( AN3_AN2_AN1_AN0 )
 *        uint8 u8_ADC_adjustResult : Control result format
 *        uint8 u8_ADC_interruptMode : choose interrupt or polling mode
 *        uint8 u8_ADC_prescaler :
 *        Ptrfunc ptrf_ADC_cbk : ptr to function which will be called in interrupt 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function initializes the ADC module.
 * 				
 * caution@ the user should config dio as an input			
 *********************************************************************************************/
extern void ADC_init(uint8 u8_ADC_Channels_Config , uint8 u8_ADC_adjustResult , uint8 u8_ADC_Mode , 
                    uint8 u8_ADC_prescaler , Ptrfunc ptrf_ADC_cbk)

{
    /* Enable the module */
    SET_BIT(ADCON0,ADON_BIT);
    
    /* clear the channel config bits to do new init */
    CLR_BIT(ADCON1,ADC_CHANNEL_CONFIG_MASK);
    /* make sure that the variable holds the value of config only */
    u8_ADC_Channels_Config &= (ADC_CHANNEL_CONFIG_MASK); 
    /* A/D Port Configuration Control Bits ( AN3_AN2_AN1_AN0 )*/
    SET_BIT(ADCON1,u8_ADC_Channels_Config);

    
    
    /* clear the Adjust config bit to do new init */    
    CLR_BIT(ADCON1,ADC_ADJUST_RESULT_MASK);
    /* make sure that the variable holds the value of config only */
    u8_ADC_adjustResult &= (ADC_ADJUST_RESULT_MASK);
    SET_BIT(ADCON1,u8_ADC_adjustResult);
    
    
    
    /* init the interrupt mode */
    u8_Mode = u8_ADC_Mode;
    
    
    /* config the adjust format */
    CLR_BIT(ADCON0,ADCS1_BIT);
    CLR_BIT(ADCON0,ADCS0_BIT);
    CLR_BIT(ADCON1,ADCS2_BIT);
    
    switch(u8_ADC_prescaler)
    {
        case ADC_PRESCALER_2 :
            CLR_BIT(ADCON0,ADCS1_BIT);
            CLR_BIT(ADCON0,ADCS0_BIT);
            CLR_BIT(ADCON1,ADCS2_BIT);
            break;
        
        case ADC_PRESCALER_4 :
            CLR_BIT(ADCON0,ADCS1_BIT);
            CLR_BIT(ADCON0,ADCS0_BIT);
            SET_BIT(ADCON1,ADCS2_BIT);
            break;

        case ADC_PRESCALER_8 :
            CLR_BIT(ADCON0,ADCS1_BIT);
            SET_BIT(ADCON0,ADCS0_BIT);
            CLR_BIT(ADCON1,ADCS2_BIT);
            break;

        case ADC_PRESCALER_16 :
            CLR_BIT(ADCON0,ADCS1_BIT);
            SET_BIT(ADCON0,ADCS0_BIT);
            SET_BIT(ADCON1,ADCS2_BIT);
            break;
            
        case ADC_PRESCALER_32 :
            SET_BIT(ADCON0,ADCS1_BIT);
            CLR_BIT(ADCON0,ADCS0_BIT);
            CLR_BIT(ADCON1,ADCS2_BIT);
            break;

        case ADC_PRESCALER_64 :
            SET_BIT(ADCON0,ADCS1_BIT);
            CLR_BIT(ADCON0,ADCS0_BIT);
            SET_BIT(ADCON1,ADCS2_BIT);
            break;

    }
    
}


/**************************************************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function starts the conversion of ADC.
 * 							
 **************************************************************************************/
extern void ADC_startConversion(uint8 u8_channel)
{
    u8_channel &= ADC_CHANNEL_MASK;
    /* clear the channel config bits to select new channel */
    CLR_BIT(ADCON0,ADC_CHANNEL_MASK);
    SET_BIT(ADCON0,u8_channel);
    
    /* start conversion */
    SET_BIT(ADCON0,GO_DONE_BIT);
}




/**************************************************************************************
 * Input: 
 *			ptru8_Result: the function will write the result in it.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function return the result of the  ADC conversion .
 * 							
 **************************************************************************************/

extern void ADC_ReadResult(uint16 *ptru16_Result)
{
    switch (u8_Mode)
    {
        case ADC_POLLING_MODE :
            /* wait for finishing the conversion*/
            while((ADCON0 & GO_DONE_BIT));
            *ptru16_Result = 0;
            *ptru16_Result = ADRESL;
            *ptru16_Result |= (uint16)(ADRESH<<8);
            break;
        
        case ADC_INTERRUPT_MODE :
            break;
    }
}
