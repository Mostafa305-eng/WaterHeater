/*
 * File:   SSD.c
 * Author: Metwaly
 *
 * Created on June 30, 2020, 9:55 PM
 */

/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "SSD.h"
#include "SSD_Config.h"
#include "DIO.h"

/************************************************************************/
/*						        defines                                */
/************************************************************************/
#define TWENTY_MS           20

#define SSD_PERIOD_MS       20



/************************************************************************/
/*						Typedefs defines                               	*/
/************************************************************************/


typedef struct ST_SSD_t{
	uint8 u8_SSD_Data;
    uint8 u8_SSD_State;
}ST_SSD_t;


/************************************************************************/
/*						Static Variables                               	*/
/************************************************************************/
static ST_SSD_t astr_SSDs[]={    {0,SSD_OFF,},
                            {0,SSD_OFF},
                            {0,SSD_OFF},
                            {0,SSD_OFF},
                            } ;

static uint8 u8_SSD_Current=FIRST_SSD;


static uint8 au8_SSD_DataMask[] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
};


 static uint8 u8_SSD_TickCounter = 0;

/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize the x_SSD (where x First, second, third, fourth) as output
 * @param u8_SSD_ID: The SSD to be initialized and it takes
 * 				  one of defines
 *
 *****************************************************************************/
void SSD_Init(uint8 u8_SSD_ID)
{
    /* start displaying with first ssd*/
    u8_SSD_Current=FIRST_SSD;
    u8_SSD_TickCounter = 0;
    
    switch(u8_SSD_ID)
    {
        case FIRST_SSD :
            DIO_init(SSD_0_GPIO,SSD_0_BIT,OUTPUT);
            break;
        case SECOND_SSD :
            DIO_init(SSD_1_GPIO,SSD_1_BIT,OUTPUT);
            break;
        case THIRD_SSD :
            DIO_init(SSD_2_GPIO,SSD_2_BIT,OUTPUT);
            break;
        case FOURTH_SSD :
            DIO_init(SSD_3_GPIO,SSD_3_BIT,OUTPUT);
            break;
        default :
            break;
    }
    DIO_init(SSD_DATA_GPIO,FULL_PORT,OUTPUT);
}


/*******************************************************************************
 * Description: Update all x_SSD (where x First, second, third, fourth)  to show
 *              the required numbers
 *
 * @note : this function must be called in the system tick handler or in the 
 *          super loop handler
 *****************************************************************************/
void SSD_Update(void)
{

    /* Check if it is time for the SSD_Update to run */
    u8_SSD_TickCounter += TICK_MS;

    if (u8_SSD_TickCounter != SSD_PERIOD_MS){
        return;
    }
    
    u8_SSD_TickCounter = 0 ;
            
    /**turn off all the SSDs*/
    DIO_Write(SSD_0_GPIO,SSD_0_BIT,LOW);
    DIO_Write(SSD_1_GPIO,SSD_1_BIT,LOW);
    DIO_Write(SSD_2_GPIO,SSD_2_BIT,LOW);
    DIO_Write(SSD_3_GPIO,SSD_3_BIT,LOW);

 
    /*check the state of the SSD if it is on or not*/
    if(astr_SSDs[u8_SSD_Current].u8_SSD_State == SSD_ON )
    {
        /* Turn on the SSD */
        switch(u8_SSD_Current)
        {
            case FIRST_SSD :
                /*put the data of the digit on GPIO_Data*/
                DIO_PortWrite (SSD_DATA_GPIO, au8_SSD_DataMask [ astr_SSDs[u8_SSD_Current].u8_SSD_Data ] );
                /*enable the ssd*/
                DIO_Write(SSD_0_GPIO,SSD_0_BIT,HIGH);
                break;
            case SECOND_SSD :
                /*put the data of the digit on GPIO_Data*/
                DIO_PortWrite (SSD_DATA_GPIO, au8_SSD_DataMask [ astr_SSDs[u8_SSD_Current].u8_SSD_Data ] );
                /*enable the ssd*/
                DIO_Write(SSD_1_GPIO,SSD_1_BIT,HIGH);
                break;
            case THIRD_SSD :
                /*put the data of the digit on GPIO_Data*/
                DIO_PortWrite (SSD_DATA_GPIO, au8_SSD_DataMask [ astr_SSDs[u8_SSD_Current].u8_SSD_Data ] );
                /*enable the ssd*/
                DIO_Write(SSD_2_GPIO,SSD_2_BIT,HIGH);
                break;
            case FOURTH_SSD :
                /*put the data of the digit on GPIO_Data*/
                DIO_PortWrite (SSD_DATA_GPIO, au8_SSD_DataMask [ astr_SSDs[u8_SSD_Current].u8_SSD_Data ] );
                /*enable the ssd*/
                DIO_Write(SSD_3_GPIO,SSD_3_BIT,HIGH);
                break;
            default :
                break;
        }
    }
    else
    {
        DIO_Write(SSD_DATA_GPIO,FULL_PORT,LOW);
    }
    
    #if NUMBER_OF_SSDS_USES == 2
    if(u8_SSD_Current == SECOND_SSD)
    {
        u8_SSD_Current=FIRST_SSD;
    }
    else
    {
        u8_SSD_Current++;
    }
    #elif NUMBER_OF_SSDS_USES == 3
    if(u8_SSD_Current == THIRD_SSD)
    {
        u8_SSD_Current=FIRST_SSD;
    }
    else
    {
        u8_SSD_Current++;
    }
    #elif NUMBER_OF_SSDS_USES == 4
    if(u8_SSD_Current == FOURTH_SSD)
    {
        u8_SSD_Current=FIRST_SSD;
    }
    else
    {
        u8_SSD_Current++;
    }
    #else

    #endif
}




/*****************************************************************************
 * Description: Set the value that will be displayed on
 *              the x_SSD (where x First, second, third, fourth)
 * @param u8_SSD_ID: The SSD to be changed and it takes
 * 				  one of defines
 *        u8_SSD_Data : The number will be displayed on SSD
 *****************************************************************************/

void SSD_SetValue(uint8 u8_SSD_ID,uint8 u8_SSD_Data)
{
    switch(u8_SSD_ID)
    {
        case FIRST_SSD :
            astr_SSDs[FIRST_SSD].u8_SSD_Data = u8_SSD_Data ;
            break;
        case SECOND_SSD :
            astr_SSDs[SECOND_SSD].u8_SSD_Data = u8_SSD_Data; 
            break;
        case THIRD_SSD :
            astr_SSDs[THIRD_SSD].u8_SSD_Data = u8_SSD_Data;
            break;
        case FOURTH_SSD :
            astr_SSDs[FOURTH_SSD].u8_SSD_Data = u8_SSD_Data;
            break;
        default :
            break;
    }  
}


/*****************************************************************************
 * Description: Set the state of displaying on
 *  the x_SSD (where x First, second, third, fourth) 
 * @param u8_SSD_ID: The SSD to be changed and it takes
 * 				  one of defines
 *        u8_SSD_State : The State of SSD ( ON or OFF )
 *****************************************************************************/

void SSD_SetState(uint8 u8_SSD_ID,uint8 u8_SSD_State)
{
    astr_SSDs[u8_SSD_ID].u8_SSD_State = u8_SSD_State;
}



/*****************************************************************************
 * Description: Get the state of required SSD  
 *  the x_SSD (where x First, second, third, fourth)
 * @param u8_SSD_ID: The SSD to be changed and it takes
 * 				  one of defines
 * OUTPUT :       u8_SSD_State : The State of SSD ( ON or OFF )
 *****************************************************************************/

void SSD_GetState(uint8 u8_SSD_ID,uint8 * u8_SSD_State)
{
    *u8_SSD_State = astr_SSDs[u8_SSD_ID].u8_SSD_State;
}


/*****************************************************************************
 * Description: Turn off the required SSD  
 *  the x_SSD (where x First, second, third, fourth) immediately
 * @param u8_SSD_ID: The SSD to be turned off and it takes
 * 				  one of defines
 * OUTPUT :       
 *****************************************************************************/

void SSD_TurnOff(uint8 u8_SSD_ID)
{
    DIO_Write(SSD_DATA_GPIO,FULL_PORT,LOW);
    switch(u8_SSD_ID)
    {
        case FIRST_SSD :
            DIO_Write(SSD_0_GPIO,SSD_0_BIT,LOW);
            astr_SSDs[FIRST_SSD].u8_SSD_State = SSD_OFF ;
            break;
        case SECOND_SSD :
            DIO_Write(SSD_1_GPIO,SSD_1_BIT,LOW);
            astr_SSDs[SECOND_SSD].u8_SSD_State = SSD_OFF; 
            break;
        case THIRD_SSD :
            DIO_Write(SSD_2_GPIO,SSD_2_BIT,LOW);
            astr_SSDs[THIRD_SSD].u8_SSD_State = SSD_OFF;
            break;
        case FOURTH_SSD :
            DIO_Write(SSD_3_GPIO,SSD_3_BIT,LOW);
            astr_SSDs[FOURTH_SSD].u8_SSD_State = SSD_OFF;
            break;
        default :
            break;
    }      
}


    
    
    
    