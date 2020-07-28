/*
 * File:   Interrupts.c
 * Author: mosta
 *
 * Created on July 6, 2020, 3:34 PM
 */

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include <pic16f877a.h>
#include "Interrupts.h"
#include "Interrupt_Config.h"
#include "Timer.h"

/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/

#define EN_GLOBAL_INT_BIT           0x80
#define EN_PERIPHERAL_INT_BIT       0x40



/************************************************************************/
/*						Typedefs defines                               	*/
/************************************************************************/

typedef struct ST_INTs_t{
    
    Ptrfunc aptrf_INT;
    volatile uint8 * REGISTER;
    uint8 MASK;
}ST_INTs_t;


/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/

static ST_INTs_t ast_INTS[MAX_NUM_OF_INT];

/************************************************************************/
/*                       FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/



static void __interrupt() myIsr(void)  
{
    uint8 u8_counter;
    for(u8_counter=0;u8_counter<MAX_NUM_OF_INT;u8_counter++)
    {
        if ( TRUE == GET_BIT((* (ast_INTS[u8_counter].REGISTER)),ast_INTS[u8_counter].MASK))
        {
           ast_INTS[u8_counter].aptrf_INT();
           CLR_BIT((* (ast_INTS[u8_counter].REGISTER)),ast_INTS[u8_counter].MASK);
           break;
        }
    }
}



/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Enable Global Interrupt.
 **************************************************************************/
void INT_SetEnable(void)
{
    SET_BIT(INTCON,EN_GLOBAL_INT_BIT);
    SET_BIT(INTCON,EN_PERIPHERAL_INT_BIT);
}






/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Disable Global Interrupt.
 **************************************************************************/
void INT_ClrEnable(void)
{
    CLR_BIT(INTCON,EN_GLOBAL_INT_BIT);
    CLR_BIT(INTCON,EN_PERIPHERAL_INT_BIT);    
}




/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: 			
 * Description: set the call back function
 **************************************************************************/

void INT_SetCallBackFunc(uint8 u8_INT_Priority,volatile uint8 * pu8_Register,uint8 u8_MASK ,
                         Ptrfunc ptrf_CallBkFunc  )
{
    ast_INTS[u8_INT_Priority].REGISTER=pu8_Register;
    ast_INTS[u8_INT_Priority].MASK=u8_MASK;
    if(NULL != ptrf_CallBkFunc )
    {
        ast_INTS[u8_INT_Priority].aptrf_INT= ptrf_CallBkFunc;
    }
}
