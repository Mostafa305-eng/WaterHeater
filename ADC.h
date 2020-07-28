
/*
 * ADC.h
 *
 * Created: 1/2/2020 12:01:24 AM
 *  Author: Mostafa Metwaly
 */ 
#ifndef ADC_H_
#define ADC_H_
/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/

#include "common_macros.h"
#include "std_types.h"


/******************************************************************************************
*                                                                                         *
*                                        DEFINES                                          *
*																						  *
*																						  *
*******************************************************************************************/

#define ADC_LEFT_ADJUST				(0x00)
#define ADC_RIGHT_ADJUST			(0x80)

/* AN3_AN2_AN1_AN0 */
#define A_A_A_A 					(0x00)
#define VPOS_A_A_A      			(0x01)
#define A_D_A_A 					(0x04)
#define VPOS_D_A_A  				(0x05)
#define D_D_D_D         			(0x06)
#define VPOS_VNEG_A_A   			(0x08)
#define D_D_D_A         			(0x0E)
#define VPOS_VNEG_D_A   			(0x0F)


#define ADC_INTERRUPT_MODE			(0x08)
#define ADC_POLLING_MODE			(0x00)

#define ADC_PRESCALER_2				(0x00)
#define ADC_PRESCALER_4				(0x04)
#define ADC_PRESCALER_8				(0x01)
#define ADC_PRESCALER_16			(0x05)
#define ADC_PRESCALER_32			(0x02)
#define ADC_PRESCALER_64			(0x06)

#define ADC_CHANNEL_0               (0x00)
#define ADC_CHANNEL_1               (0x08)
#define ADC_CHANNEL_2               (0x10)
#define ADC_CHANNEL_3               (0x18)
#define ADC_CHANNEL_4               (0x20)









/******************************************************************************************
*                                                                                         *
*                                 PROTOTYPES                                              *
*																						  *
*																						  *
*******************************************************************************************/


/******************************************************************************************
 * Input: 
 *		  uint8 u8_ADC_Channels_Config : ADC PORT CONFIG CONTROL BITS ( AN3_AN2_AN1_AN0 )
 *        uint8 u8_ADC_adjustResult : Control result format
 *        uint8 u8_ADC_Mode : choose interrupt or polling mode
 *        uint8 u8_ADC_prescaler :
 *        Ptrfunc ptrf_ADC_cbk : ptr to function which will be called in interrupt 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function initializes the ADC module.
 * 							
 * caution@ the user should config dio as an input
 *********************************************************************************************/
extern void ADC_init(uint8 u8_ADC_Channels_Config , uint8 u8_ADC_adjustResult , uint8 u8_ADC_Mode , 
                    uint8 u8_ADC_prescaler , Ptrfunc ptrf_ADC_cbk);


/**************************************************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: 		
 * Description: This function starts the conversion of ADC.
 * 							
 **************************************************************************************/
extern void ADC_startConversion(uint8 u8_channel);




/**************************************************************************************
 * Input: 
 *			ptru8_Result: the function will write the result in it.
 * Output:
 * In/Out:			
 * Return: 		
 * Description: This function return the result of the  ADC conversion .
 * 							
 **************************************************************************************/

extern void ADC_ReadResult(uint16 *ptru16_Result);

#endif