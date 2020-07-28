/*
 * Timer.h
 *
 *  Created on: Dec 21, 2019
 *      Author: Metwaly
 */

#ifndef TIMER_H_
#define TIMER_H_

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/


#include "std_types.h"
#include "common_macros.h"



/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/


#define		TIMER_CH0						0
#define		TIMER_CH1						1
#define		TIMER_CH2						2

#define		TIMER_MODE						0
#define		COUNTER_RISING_MODE				1
#define		COUNTER_FALLING_MODE			2


#define		TIMER_POLLING_MODE				0
#define		TIMER_INTERRUPT_MODE			1

#define		TIMER_NO_CLOCK					0
#define		TIMER_PRESCALER_NO				1
#define		TIMER_PRESCALER_2				2
#define		TIMER_PRESCALER_4				3
#define		TIMER_PRESCALER_8				4
#define		TIMER_PRESCALER_16				5
#define		TIMER_PRESCALER_32				6
#define		TIMER_PRESCALER_64				7
#define		TIMER_PRESCALER_128				8
#define		TIMER_PRESCALER_256				9


/************************************************************************/
/*			  Structures Definitions		        */
/************************************************************************/

typedef struct str_Timer_cfg_t
{
	uint8 Timer_CH_NO;
	uint8 Timer_Mode;   /*Timer or Counter Mode*/
	uint8 Timer_Polling_Or_Interrupt;
	uint8 Timer_Prescaler; 
    Ptrfunc aptrf_INT; /*Call back function if the interrupt is used */
}str_Timer_cfg_t;


/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES		        */
/************************************************************************/


/******************************************************************************
 * fun
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Initiates the module.
 * 
 * caution@ Timer_CH1 comes with PRESCALER_4,8,16,32 only
 **************************************************************************/
 void Timer_Init(str_Timer_cfg_t * st_Timer_cfg);

 
/***************************************************************************
 * Input: 
 * 	u8_Timer_CH_NO: The channel number of the timer needed to be started.
 *	u16_Timer_Count: The start value of the timer.
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function starts the needed timer.
 * 							
 ****************************************************************************/
 
void Timer_Start(uint8 u8_Timer_CH_NO, uint16 u16_Timer_Count);


/****************************************************************************
 * Input: 
 * 	u8_Timer_CH_NO: The channel number of the timer will be stopped.
 * Output:
 * In/Out:			
 * Return: 		
 * Description: This function stops the needed timer.
 * 							
******************************************************************************/
void Timer_Stop(uint8 u8_Timer_CH_NO);


/******************************************************************************
 * Input: 
 * 	u8_Timer_CH_NO: The channel number of the timer needed to get its status (flag).
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:			
 * Return: 			
 * Description: This function is used to return if the flag of the timer is raised or not
 * 				and if it is raised , the function will clear the flag			
 ********************************************************************************/
void Timer_GetStatus(uint8 u8_Timer_CH_NO, bool* Data);


/*****************************************************************************
 * Input: 
 * 	u8_Timer_CH_NO: The channel number of the timer needed to clear its status.
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to clear the flag of the timer .
 * 							
 *****************************************************************************/
void Timer_ClrStatus(uint8 u8_Timer_CH_NO);



/******************************************************************************
 * Input: 
 * 	u8_Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:			
 * Return: 		
 * Description: This function is used to return the value of the timer.
 * 							
 *****************************************************************************/
void Timer_GetValue(uint8 u8_Timer_CH_NO, uint16* pu16_Data);


/******************************************************************************
 * Input: 
 * 	u8_Timer_CH_NO: The channel number of the timer needed to get its value.
 * u16_timer_count : no of the ticks which the counter will count
 *  * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is set the value of the timer.
 * 							
 ******************************************************************************/
void Timer_SetValue(uint8 u8_Timer_CH_NO, uint16 u16_Timer_Count);



/******************************************************************************
 * Input: 
 * 			u8_Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 			pu8_Time : this is the time of one tick of the timer
 * In/Out:			
 * Return: 		
 * Description: This function is used to return the value of the time of one tick.
 * 				
 *caution : this function is not working with prescaler (PRESCALER_4,PRESCALER_2,PRESCALER_NO)			
 ******************************************************************************/
void Timer_GetTickTime(uint8 u8_Timer_CH_NO,uint8 * pu8_Time);



#endif /* TIMER_H_ */
