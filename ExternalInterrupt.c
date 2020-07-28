/*
 * ExternalInterrupt.c
 *
 * Created: 12/23/2019 10:11:49 PM
 *  Author: Mostafa Metwaly
 */ 

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/


#include <pic16f877a.h>

#include "ExternalInterrupt.h"
#include "Interrupts.h"
#include "std_types.h"
#include "common_macros.h"



/************************************************************************/
/*								 DEFINES						        */
/************************************************************************/


#define NO_OF_INT 2



#define RB0_EdgeFalling        0x40
#define RB0_EdgeRisiging       0x40
#define RB0_Mask_EdgeBit       0x00

#define RB0_ENABLE_MASK			0x10
#define PORTB_ENABLE_MASK		0x08

#define RB0_INT_FLAG            0x02




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

void  ExternInt_Init(ExternInt_Cfg_s * pstr_ExternIntCfg)
{
	switch(pstr_ExternIntCfg->ExternInt_No)
	{
		/*set the edge event*/
		case (EXTERN_INT_RB0) :
            CLR_BIT(OPTION_REG,RB0_Mask_EdgeBit);
			switch (pstr_ExternIntCfg->ExternInt_Event)
			{
			case FALLING_EDGE :
                SET_BIT(OPTION_REG,RB0_EdgeFalling);
				break;
			case RISING_EDGE:
                SET_BIT(OPTION_REG,RB0_EdgeRisiging);
				break;
			default:
                break;
			}
			/*store the call back function */
			if ( NULL !=  pstr_ExternIntCfg->ExternInt_CBF_Ptr)
			{
                INT_SetCallBackFunc(RB0_PRIORITY,&INTCON,RB0_INT_FLAG,pstr_ExternIntCfg->ExternInt_CBF_Ptr );
			}
			break;
		case (EXTERN_INT_PORTB) :
			/*store the call back function */
			if ( NULL !=  pstr_ExternIntCfg->ExternInt_CBF_Ptr)
			{
                /* not develped yet*/
			}
			break;
		default:
            break;
	}
}



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
void ExternInt_SetEvent(uint8 u8_InterruptEvent)
{
    CLR_BIT(OPTION_REG,RB0_Mask_EdgeBit);
    switch (u8_InterruptEvent)
    {
    case FALLING_EDGE :
        SET_BIT(OPTION_REG,RB0_EdgeFalling);
        break;
    case RISING_EDGE:
        SET_BIT(OPTION_REG,RB0_EdgeRisiging);
        break;
    default:
        break;
    }
	
}


/*****************************************************************************
 * Function: ExternInt_Enable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (RB0 , PORTB)
 * Outputs:
 * In Out:
 * Return: 
 * Description: Enable the required external interrupt.
 ******************************************************************************/
void ExternInt_Enable(uint8 u8_ExternInt_Type)
{
	/* set the the bit to enable the external interrupt channel*/
	switch (u8_ExternInt_Type)
	{
		case EXTERN_INT_RB0 :
			SET_BIT(INTCON,RB0_ENABLE_MASK);
			break;
		case EXTERN_INT_PORTB :
			SET_BIT(INTCON,PORTB_ENABLE_MASK);
			break;
		default:
			break;
	}	
}


/******************************************************************************
 * Function: ExternInt_Disable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (RB0 , PORTB)
 * Outputs:
 * In Out:
 * Return: 
 * Description: Disable the required external interrupt.
 ******************************************************************************/
void ExternInt_Disable(uint8 u8_ExternInt_Type)
{
	/* set the the bit to enable the external interrupt channel*/
	switch (u8_ExternInt_Type)
	{
		case EXTERN_INT_RB0 :
			CLR_BIT(INTCON,RB0_ENABLE_MASK);
			break;
		case EXTERN_INT_PORTB :
			CLR_BIT(INTCON,PORTB_ENABLE_MASK);
			break;
		default:
			break;
	}	
}



