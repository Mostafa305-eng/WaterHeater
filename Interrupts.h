/*
 * Interrupts.h
 *
 *  Created on: July 6, 2020
 *      Author: Metwaly
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include"Interrupt_Config.h"
#include "std_types.h"
#include "common_macros.h"



/************************************************************************/
/*                          FUNCTIONS' PROTOTYPES       		        */
/************************************************************************/


/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Enable Global Interrupt.
 **************************************************************************/
void INT_SetEnable(void);




/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Disable Global Interrupt.
 **************************************************************************/
void INT_ClrEnable(void);



/******************************************************************************
 * fun
 * Input:  uint8 u8_INT_Priority : the priotiy the user configured to the required interrupt
 *         volatile uint8 * pu8_Register : pointer to register which will be checked 
 *         uint8 u8_MASK : the mask of the flag of the required interrupt
 *          Ptrfunc ptrf_CallBkFunc : the function which will be executed when 
 *                                  interrupt flag is  
 * Output:
 * In/Out:			
 * Return: 			
 * Description: set the call back function
 **************************************************************************/

void INT_SetCallBackFunc(uint8 u8_INT_Priority,volatile uint8 * pu8_Register,uint8 u8_MASK ,
                         Ptrfunc ptrf_CallBkFunc  );

#endif