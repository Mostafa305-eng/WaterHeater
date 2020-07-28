/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/


#include <pic16f877a.h>

#include "Timer.h"
#include "std_types.h"
#include "common_macros.h"
#include "DIO.h"
#include "Interrupts.h"

/************************************************************************/
/*                           DEFINES                    		        */
/************************************************************************/

#define Started					1
#define NotStarted				0

#define MSB_BYTE    	0xFF00
#define LSB_BYTE        0x00FF

#define T0_COUNTER_MAX              255
#define T0_COUNTER_MODE_BIT         0x20
#define T0_PRESCALER_ASSIGNMENT_BIT 0x08
#define T0_SOURCE_EDGE_SELECT_BIT   0x10
#define T0_INT_EN_BIT               0x20
#define T0_INT_FLAG_BIT             0x04

#define T1_ON_BIT                   0x01
#define T1_COUNTER_MAX              65535
#define T1_TIMER_INT_EN_BIT         0x01
#define T1_TIMER_INT_FLAG_BIT       0x01
#define T1_COUNTER_MODE_BIT         0x02

#define T2_COUNTER_MAX          255
#define T2_INT_EN_BIT 			0x02
#define T2_INT_FLAG_BIT 		0x02
#define T2_PRESCALER_1          0x00
#define T2_PRESCALER_4          0x01
#define T2_PRESCALER_16         0x02
#define T2_POSTSCALER_1         0x00
#define T2_POSTSCALER_2         0x08
#define T2_POSTSCALER_3         0x010
#define T2_POSTSCALER_4         0x18
#define T2_POSTSCALER_5         0x20
#define T2_POSTSCALER_6         0x28
#define T2_POSTSCALER_7         0x30
#define T2_POSTSCALER_8         0x38
#define T2_POSTSCALER_9         0x40
#define T2_POSTSCALER_10        0x48
#define T2_POSTSCALER_11        0x50
#define T2_POSTSCALER_12        0x58
#define T2_POSTSCALER_13        0x60
#define T2_POSTSCALER_14        0x68
#define T2_POSTSCALER_15        0x70
#define T2_POSTSCALER_16        0x78
#define T2_ON_BIT               0x04

#define NO_OF_TIMERS			3


/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/

static uint8 au8_Timer_Prescalar[]={0,0,0};
static uint8 au8_Timer_Started[]={NotStarted,NotStarted,NotStarted};
static uint8 au8_Timer0_PrescalerTable[]={0x00,0x00,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};
static uint8 au8_Timer1_PrescalerTable[]={0x00,0x00,0x00,0x00,0x10,0x20,0x30,0x00,0x00,0x00};


static uint16 au8_PrescalerValue[]={0,0,0};
static uint16 au8_PrescalerValueTable[]={0,1,2,4,8,16,32,64,128,256};



/************************************************************************/
/*				  TIMER FUNCTIONS IMPLEMENTATION				        */
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

void Timer_Init(str_Timer_cfg_t* st_Timer_cfg)
{
	switch(st_Timer_cfg->Timer_CH_NO)
	{
		case (TIMER_CH0) :
			switch(st_Timer_cfg->Timer_Mode)
			{
				case(TIMER_MODE) :
                    
                    /* choose external clock to make sure the T0 doesn't count*/
                    SET_BIT(OPTION_REG,T0_COUNTER_MODE_BIT); 
                    
					
					if(st_Timer_cfg->Timer_Prescaler == TIMER_PRESCALER_NO)
                    {
                        /* assign the prescaler to WDT */
                        SET_BIT(OPTION_REG,T0_PRESCALER_ASSIGNMENT_BIT);
                    }
                    else
                    {
                        /* assign the prescaler to T0  */
                        CLR_BIT(OPTION_REG,T0_PRESCALER_ASSIGNMENT_BIT);

                        /* find the prescaler mask from masks table */
                        SET_BIT(OPTION_REG, au8_Timer0_PrescalerTable[st_Timer_cfg->Timer_Prescaler] ) ;                        
                    }
					break;

				case (COUNTER_RISING_MODE):
                    /* choose external clock */
					SET_BIT(OPTION_REG,T0_COUNTER_MODE_BIT);
                    
                    /*Clear edge select bit to choose Rising edge*/
                    CLR_BIT(OPTION_REG,T0_SOURCE_EDGE_SELECT_BIT);
                    
					if(st_Timer_cfg->Timer_Prescaler == TIMER_PRESCALER_NO)
                    {
                        /* assign the prescaler to WDT */
                        SET_BIT(OPTION_REG,T0_PRESCALER_ASSIGNMENT_BIT);
                    }
                    else
                    {
                        /* assign the prescaler to T0  */
                        CLR_BIT(OPTION_REG,T0_PRESCALER_ASSIGNMENT_BIT);

                        /* find the prescaler mask from masks table */
                        SET_BIT(OPTION_REG, au8_Timer0_PrescalerTable[st_Timer_cfg->Timer_Prescaler] ) ;                        
                    }
					break;					
		
				case (COUNTER_FALLING_MODE):
                    /* choose external clock */
					SET_BIT(OPTION_REG,T0_COUNTER_MODE_BIT);

                    /*Sit edge select bit to choose Rising edge*/
                    SET_BIT(OPTION_REG,T0_SOURCE_EDGE_SELECT_BIT);

					if(st_Timer_cfg->Timer_Prescaler == TIMER_PRESCALER_NO)
                    {
                        /* assign the prescaler to WDT */
                        SET_BIT(OPTION_REG,T0_PRESCALER_ASSIGNMENT_BIT);
                    }
                    else
                    {
                        /* assign the prescaler to T0  */
                        CLR_BIT(OPTION_REG,T0_PRESCALER_ASSIGNMENT_BIT);

                        /* find the prescaler mask from masks table */
                        SET_BIT(OPTION_REG, au8_Timer0_PrescalerTable[st_Timer_cfg->Timer_Prescaler] ) ;                        
                    }
					break;					
				default :
					break;
			}
			switch(st_Timer_cfg->Timer_Polling_Or_Interrupt)
			{
				case(TIMER_INTERRUPT_MODE) :
                    SET_BIT(INTCON,T0_INT_EN_BIT);
                    /*      not developed yet
                     * if(NULL != st_Timer_cfg->aptrf_INT)
                    {
                        INT_SetCallBackFunc(TIMER0_PRIORITY,,,st_Timer_cfg->aptrf_INT );
                    }*/
					break;
				case(TIMER_POLLING_MODE) :
					CLR_BIT(INTCON,T0_INT_EN_BIT);
					break;
				default :
					break;
			}
            /*Store the value of the prescaler to use in Tick time calculating*/
			au8_PrescalerValue[TIMER_CH0]=au8_PrescalerValueTable[st_Timer_cfg->Timer_Prescaler];			
			break;
			
		case (TIMER_CH1) :
			switch(st_Timer_cfg->Timer_Mode)
			{
				case(TIMER_MODE):
 					break;
                    
				case (COUNTER_RISING_MODE):		
				case (COUNTER_FALLING_MODE):
                    /* choose external clock */
                    SET_BIT(T1CON,T1_COUNTER_MODE_BIT);
					break;
                    
                default :
                    break;
			}
            
            switch(st_Timer_cfg->Timer_Polling_Or_Interrupt)
            {
                case TIMER_INTERRUPT_MODE:
                    SET_BIT(PIE1,T1_TIMER_INT_EN_BIT);
                    if(NULL != st_Timer_cfg->aptrf_INT)
                    {
                        /* set the call back function in interrupt */
                        INT_SetCallBackFunc(TIMER1_PRIORITY,&PIR1,T1_TIMER_INT_FLAG_BIT,st_Timer_cfg->aptrf_INT );
                    }
                    break;

                case TIMER_POLLING_MODE:
                    CLR_BIT(PIE1,T1_TIMER_INT_EN_BIT);
                    break;
                    
            }
            /*Store the value of the prescaler to use in Tick time calculating*/
			au8_PrescalerValue[TIMER_CH1]=au8_PrescalerValueTable[st_Timer_cfg->Timer_Prescaler];
            
            /* find the prescaler mask from masks table */
            SET_BIT(T1CON, au8_Timer1_PrescalerTable[st_Timer_cfg->Timer_Prescaler] ); 
			break;
		
		case (TIMER_CH2) :
			switch(st_Timer_cfg->Timer_Mode)
			{
				case(TIMER_MODE):   
					break;
				default :
					break;
			}
            CLR_BIT(T2CON,FULL_PORT);
            switch(st_Timer_cfg->Timer_Prescaler)
            {
                case TIMER_PRESCALER_NO :
                    break;
                case TIMER_PRESCALER_2 :
                    SET_BIT(T2CON,T2_POSTSCALER_2);
                    break;
                case TIMER_PRESCALER_4:
                    SET_BIT(T2CON,T2_PRESCALER_4);
                    break;
                case TIMER_PRESCALER_8:
                    SET_BIT(T2CON,T2_POSTSCALER_2);
                    SET_BIT(T2CON,T2_PRESCALER_4);
                    break;
                case TIMER_PRESCALER_16:
                    SET_BIT(T2CON,T2_PRESCALER_16);
                    break;
                case TIMER_PRESCALER_32:
                    SET_BIT(T2CON,T2_POSTSCALER_2);
                    SET_BIT(T2CON,T2_PRESCALER_16);
                    break;
                case TIMER_PRESCALER_64:
                    SET_BIT(T2CON,T2_POSTSCALER_4);
                    SET_BIT(T2CON,T2_PRESCALER_16);
                    break;
                 case TIMER_PRESCALER_128:
                    SET_BIT(T2CON,T2_POSTSCALER_8);
                    SET_BIT(T2CON,T2_PRESCALER_16);
                    break;
                case TIMER_PRESCALER_256:
                    SET_BIT(T2CON,T2_POSTSCALER_16);
                    SET_BIT(T2CON,T2_PRESCALER_16);
                    break;
           }

            switch(st_Timer_cfg->Timer_Polling_Or_Interrupt  )
            {
                case TIMER_INTERRUPT_MODE : 
                    SET_BIT(PIE1,T2_INT_EN_BIT);
                    break;
                
                case TIMER_POLLING_MODE : 
                    CLR_BIT(PIE1,T2_INT_EN_BIT);
                     break;
                default :
                    break;
            }
			
			au8_PrescalerValue[TIMER_CH2]=au8_PrescalerValueTable[st_Timer_cfg->Timer_Prescaler]; 
			break;
	
		default :
			break;
		
	}
}



/***************************************************************************
 * Input: 
 * 	u8_Timer_CH_NO: The channel number of the timer needed to be started.
 *	u16_u16_Timer_Count: The start value of the timer.
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function starts the needed timer.
 * 							
 ****************************************************************************/
 
void Timer_Start(uint8 u8_Timer_CH_NO, uint16 u16_Timer_Count)
{
	switch(u8_Timer_CH_NO)
	{
		case TIMER_CH0 :
            /*checks the timer counts */
			if(u16_Timer_Count > T0_COUNTER_MAX)
			{
                /* do nothing*/
			}
			else
			{	
				/*init the flag as started*/
				au8_Timer_Started[TIMER_CH0]=Started;

                /*calculate the start of counter in the timer*/
                u16_Timer_Count = T0_COUNTER_MAX - u16_Timer_Count;            
                
                
                TMR0 = u16_Timer_Count;

				/*start the timer*/
				CLR_BIT(OPTION_REG,T0_COUNTER_MODE_BIT);
			}
			break;

		case TIMER_CH1 :
			if(u16_Timer_Count > T1_COUNTER_MAX)
			{
			}
			else
			{

                /*calculate the start of counter in the timer*/
                u16_Timer_Count = T1_COUNTER_MAX - u16_Timer_Count;

                
                TMR1L = u16_Timer_Count & LSB_BYTE;
                TMR1H = (u16_Timer_Count & MSB_BYTE)>>8;

                /*init the flag as started*/
				au8_Timer_Started[TIMER_CH1]=Started;
                
                /*start the timer*/
                SET_BIT(T1CON,T1_ON_BIT);
			}
			break;
			
		case TIMER_CH2 :
            u16_Timer_Count = T2_COUNTER_MAX - u16_Timer_Count;
			if(u16_Timer_Count > T2_COUNTER_MAX)
			{
		
			}
			else
			{
                TMR2 = u16_Timer_Count;    
				au8_Timer_Started[TIMER_CH2]=Started;
                SET_BIT(T2CON,T2_ON_BIT);
			}
			break;
		default:
			break;
	}
}


/****************************************************************************
 * Input: 
 * 	u8_Timer_CH_NO: The channel number of the timer will be stopped.
 * Output:
 * In/Out:			
 * Return: 		
 * Description: This function stops the needed timer.
 * 							
******************************************************************************/
void Timer_Stop(uint8 u8_Timer_CH_NO)
{
	switch(u8_Timer_CH_NO)
	{
		case TIMER_CH0 :
			/*check if the timer is started or not*/
			if(au8_Timer_Started[TIMER_CH0] != Started)
			{
			}
			else
			{
				/*stop the timer  */
                SET_BIT(OPTION_REG,T0_COUNTER_MODE_BIT);
				au8_Timer_Started[TIMER_CH0]=NotStarted;
			}
			break;
		case TIMER_CH1 :
			if(au8_Timer_Started[TIMER_CH1] != Started)
			{
				
			}
			else
			{
				CLR_BIT(T1CON,T1_ON_BIT);
				au8_Timer_Started[TIMER_CH1]=NotStarted;
			}
			break;
		case TIMER_CH2 :
			if(au8_Timer_Started[TIMER_CH2] != Started)
			{
			}
			else
			{
				CLR_BIT(T1CON,T2_ON_BIT);
				au8_Timer_Started[TIMER_CH2]=NotStarted;
			}
			break;
		default:
            break;
	}
}
    

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
void Timer_GetStatus(uint8 u8_Timer_CH_NO,  bool* Data)
{
	switch(u8_Timer_CH_NO)
	{
		case TIMER_CH0 :
			/*get the flag of the output compare timer*/
			* Data = GET_BIT(INTCON,T0_INT_FLAG_BIT);
			break;
		case TIMER_CH1 :
            * Data = GET_BIT(PIR1,T1_TIMER_INT_FLAG_BIT);
              
			break;
		case TIMER_CH2 :
			* Data = GET_BIT(PIR1,T2_INT_FLAG_BIT);
			break;
		default :
            break;
	}
    if ((*Data) == TRUE)
    {
        /*if the flag is raised , set the flag to clear */
        Timer_ClrStatus(u8_Timer_CH_NO);
    }
}


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

void Timer_GetValue(uint8 u8_Timer_CH_NO, uint16* pu16_Data)
{
    * pu16_Data =0;
	switch(u8_Timer_CH_NO)
	{
		case TIMER_CH0 :
			* pu16_Data = TMR0;
			break;
		case TIMER_CH1 :
			* pu16_Data = TMR1L;
            * pu16_Data |= (TMR1H<<8);
			break;
		case TIMER_CH2 :
			* pu16_Data = TMR2;
			break;
		default :
            break;
	}	
}


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
void Timer_GetTickTime(uint8 u8_Timer_CH_NO,uint8 *pu8_Time)
{
	*pu8_Time = au8_PrescalerValue[u8_Timer_CH_NO]/F_CPU_MHZ;
}



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
void Timer_SetValue(uint8 u8_Timer_CH_NO, uint16 u16_Timer_Count)
{
	switch(u8_Timer_CH_NO)
	{
		case TIMER_CH0 :
			/*checks the timer counts */
			if(u16_Timer_Count > T0_COUNTER_MAX)
			{
			}
			else
			{	
                /*calculate the start of counter in the timer*/
                u16_Timer_Count = T0_COUNTER_MAX - u16_Timer_Count;
				TMR0 = u16_Timer_Count;
			}
			break;

		case TIMER_CH1 :
			if(u16_Timer_Count > T1_COUNTER_MAX)
			{
			}
			else
			{
                /*calculate the start of counter in the timer*/
                u16_Timer_Count = T1_COUNTER_MAX - u16_Timer_Count;
                
                TMR1L = u16_Timer_Count & LSB_BYTE;
                TMR1H = (u16_Timer_Count & MSB_BYTE)>>8;
			}
			break;
			
		case TIMER_CH2 :
            
			if(u16_Timer_Count > T2_COUNTER_MAX)
			{
		
			}
			else
			{
                u16_Timer_Count = T2_COUNTER_MAX - u16_Timer_Count;
                TMR2 = u16_Timer_Count;    
			}
			break;
		default:
			break;
	}
    
}

/*****************************************************************************
 * Input: 
 * 	u8_Timer_CH_NO: The channel number of the timer needed to clear its status.
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to clear the flag of the timer .
 * 							
 *****************************************************************************/
void Timer_ClrStatus(uint8 u8_Timer_CH_NO)
{
    switch (u8_Timer_CH_NO)
    {
        case TIMER_CH0:
            CLR_BIT(INTCON,T0_INT_FLAG_BIT);
            break;

        case TIMER_CH1:
            CLR_BIT(PIR1,T1_TIMER_INT_FLAG_BIT);
            break;

        case TIMER_CH2:
            CLR_BIT(PIR1,T2_INT_FLAG_BIT);
            break;

    }
}



