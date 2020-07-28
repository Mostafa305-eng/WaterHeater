/*
 * File:   I2c.c
 * Author: mosta
 *
 * Created on July 10, 2020, 9:00 PM
 */


/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/
#include "DIO.h"
#include "I2C.h"
#include <pic16f877a.h>



/************************************************************************/
/*						        defines                                */
/************************************************************************/

#define I2C_MASTER_MODE                 0X08
#define I2C_SERIAL_PORT_ENABLE          0X20

#define I2C_MASTER_ENABLE_RECIEVE       0X08

#define START_CONDITION_ENABLE          0x01
#define REPEATED_START_CONDITION_ENABLE 0x02
#define STOP_CONDITION_ENABLE           0x04
#define ACK_CONDITION_ENABLE            0x10
#define ACK_DATA                        0x20
#define ACK_FLAG                        0x40

#define I2C_INT_EN                      0x08

#define TRANSMIT_STATE                  0x04
#define IDLE_MASK                       0x1F

/************************************************************************/
/*						Static Variables                               	*/
/************************************************************************/


uint8 u8_ModuleMode;



/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/



/*****************************************************************************
 * Description: Initialize I2C as Master
 * @param u8_Mode: Polling or interrupt
 *        u16_Baud rate :used for baud rate generator to generate the required
 *                      clock 
 *
 *****************************************************************************/
void  I2C_Master_Init(uint8 u8_Mode,uint32 u32_Baudrate)
{
    /* config the sda and scl as input pins*/
    DIO_init(GPIOC,BIT3|BIT4,INPUT);
    
    CLR_BIT(SSPSTAT,FULL_PORT);
    CLR_BIT(SSPCON2,FULL_PORT);
        
    /* choose the master mode */
    SET_BIT(SSPCON,I2C_MASTER_MODE);
    /* enable the module */
    SET_BIT(SSPCON,I2C_SERIAL_PORT_ENABLE);
    /* Setting Clock Speed */
    SSPADD = (_XTAL_FREQ/(4*u32_Baudrate))-1; 

    
    if(u8_Mode == I2C_INTERRUPT_MODE)
    {
        SET_BIT(PIE1,I2C_INT_EN);
    }

    u8_ModuleMode = u8_Mode;
}



/*****************************************************************************
 * Description: used for polling for the flags of the I2C to make sure that 
 *              the I2C module is not in progress
 * 
 *
 *****************************************************************************/
void I2C_Master_Wait()
{
    /*wait if the Transmit is in progress*/
    while ((SSPSTAT & TRANSMIT_STATE) ||  (SSPCON2 & IDLE_MASK)); 
}



/*****************************************************************************
 * Description: Initiate Start condition on SDA and SCL pins.
 * 
 *
 *****************************************************************************/
void I2C_Master_Start()
{
    if(u8_ModuleMode == I2C_POLLING_MODE)
    {
      I2C_Master_Wait();            
    }
    /* Initiate start condition */
    SET_BIT(SSPCON2,START_CONDITION_ENABLE);     
}


/*****************************************************************************
 * Description: Initiate Repeated Start condition on SDA and SCL pins
 * 
 *
 *****************************************************************************/
void I2C_Master_RepeatedStart()
{
    if(u8_ModuleMode == I2C_POLLING_MODE)
    {
      I2C_Master_Wait();            
    }
    /*Initiate repeated start condition*/
    SET_BIT(SSPCON2,REPEATED_START_CONDITION_ENABLE);
}


/*****************************************************************************
 * Description: Initiate Stop condition on SDA and SCL pins
 * 
 *
 *****************************************************************************/
void I2C_Master_Stop()
{
    if(u8_ModuleMode == I2C_POLLING_MODE)
    {
      I2C_Master_Wait();            
    }
    SET_BIT(SSPCON2,STOP_CONDITION_ENABLE);
}




/*****************************************************************************
 * Description: Initiate Acknowledge sequence on SDA and SCL pins
 * 
 *
 *****************************************************************************/
void I2C_Master_AckEN(uint8 u8_ACK_State)
{
    if(u8_ModuleMode == I2C_POLLING_MODE)
    {
      I2C_Master_Wait();            
    }
    
    
    if(u8_ACK_State == ACKNOWLEDGE)
    {
       CLR_BIT(SSPCON2,ACK_DATA);         
    }
    else
    {
       SET_BIT(SSPCON2,ACK_DATA);         
    }

    SET_BIT(SSPCON2,ACK_CONDITION_ENABLE);
}


/*****************************************************************************
 * Description: used for writing the data field 
 * @param u8_Data: data will be written in the data field
 * 
 *
 *****************************************************************************/
void I2C_Master_Write(uint8 u8_Data)
{
    if(u8_ModuleMode == I2C_POLLING_MODE)
    {
      I2C_Master_Wait();            
    }
    SSPBUF=u8_Data;
}


/*****************************************************************************
 * Description: used for reading the data field 
 * @param * u8_Data: pointer to place where data will be received in the data 
 *                  field 
 * 
 *
 *****************************************************************************/
void I2C_Master_Read(uint8 * pu8_Data)
{
    if(u8_ModuleMode == I2C_POLLING_MODE)
    {
        I2C_Master_Wait();
    }
    *pu8_Data=SSPBUF;
    
}




/*****************************************************************************
 * Description: used enabling the receive bit 
 * @param   
 *
 *****************************************************************************/
void I2C_Master_EnableRead()
{
    if(u8_ModuleMode == I2C_POLLING_MODE)
    {
        I2C_Master_Wait();
    }  
    SET_BIT(SSPCON2,I2C_MASTER_ENABLE_RECIEVE);       
}



/*****************************************************************************
 * Description: Polling for receiving ack from slave
 * 
 *
 *****************************************************************************/
void I2C_Master_WaitACK()
{
    /*wait for ack from slave*/
    while(SSPCON2 & ACK_FLAG);         
}