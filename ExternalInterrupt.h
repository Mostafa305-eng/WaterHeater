/*
 * file: externalInterrupt.h
 * Author: Hassan and Ghanem.
 * version: 1.0.5 
 */


#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_


/************************************************************************/
/*				 		      INCLUDES                                  */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"

/************************************************************************/
/*				 		       Defines                                  */
/************************************************************************/

#define EXTERN_INT_RB0           0
#define EXTERN_INT_PORTB         1    


#define FALLING_EDGE             2
#define RISING_EDGE              3

/************************************************************************/
/*				 		           DataTypes                            */
/************************************************************************/

typedef struct ExternInt_Cfg_s{

	uint8 ExternInt_No; 
	uint8 ExternInt_Event; 
	void (*ExternInt_CBF_Ptr)(void); 
}ExternInt_Cfg_s;

/************************************************************************/
/*				 		Functions ProtoTypes                            */
/************************************************************************/


/****************************************************************************
 * Function: ExternInt_Init 
 * Inputs:	ExternIntCfg -> pointer of type ExternInt_Cfg_s which points to structure
 *  that contain the initialized data.
 * Outputs: 
 * In Out: 
 * Return: 
 * Description: Initiate the required external interrupt configuration as it specify
 *	event of interrupt.
 *	Enable the required external interrupt but to allow the interrupt global interrupt must be set
 *****************************************************************************/
void  ExternInt_Init(ExternInt_Cfg_s * pstr_ExternIntCfg);


/*****************************************************************************
 * Function: ExternInt_SetEvent
 * Inputs: u8_InterruptEvent -> indicate required event for RB0 there are 2 events to 
 *                            check (RISING_EDGE,FALLING_EDGE).
 * Outputs: 
 * In Out:
 * Return: 
 * Description: function is used to set event of RB0 external interrupt. 
 * 				
 ******************************************************************************/
void ExternInt_SetEvent(uint8 u8_InterruptEvent);


/******************************************************************************
 * Function: ExternInt_Getpu8_Status
 * Inputs: 
 * Outputs: *status -> points to the value of RB0 interrupt flag.
 * In Out:
 * Return: 
 * Description: function is used to get flag of RB0 interrupt status. 
 * 				note: usually used to poll on the flag.
 *****************************************************************************/
void ExternInt_GetStatus(uint8 *pu8_Status);


/*****************************************************************************
 * Function: ExternInt_Enable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (RB0 , PORTB)
 * Outputs:
 * In Out:
 * Return: 
 * Description: Enable the required external interrupt.
 ******************************************************************************/
void ExternInt_Enable(uint8 u8_ExternInt_Type);





/******************************************************************************
 * Function: ExternInt_Disable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (RB0 , PORTB)
 * Outputs:
 * In Out:
 * Return: 
 * Description: Disable the required external interrupt.
 ******************************************************************************/
void ExternInt_Disable(uint8 u8_ExternInt_Type);


#endif /*EXTERNAL_INTERRUPT_H_*/
