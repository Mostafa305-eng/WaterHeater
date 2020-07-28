#ifndef I2C_H_
#define I2C_H_


/************************************************************************/
/*				 				INCLUDES						        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"


/************************************************************************/
/*								 DEFINES						        */
/************************************************************************/

#define I2C_POLLING_MODE                1
#define I2C_INTERRUPT_MODE              2

#define ACKNOWLEDGE                     1
#define NOT_ACKNOWLEDGE                 2


/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/




/*****************************************************************************
 * Description: Initialize I2C as Master
 * @param u8_Mode: Polling or interrupt
 *        u16_Baud rate :used for baud rate generator to generate the required
 *                      clock 
 *
 *****************************************************************************/
void  I2C_Master_Init(uint8 u8_Mode,uint32 u32_Baudrate);




/*****************************************************************************
 * Description: used for polling for the flags of the I2C to make sure that 
 *              the I2C module is not in progress
 * 
 *
 *****************************************************************************/
void I2C_Master_Wait();


/*****************************************************************************
 * Description: Initiate Start condition on SDA and SCL pins.
 * 
 *
 *****************************************************************************/
void I2C_Master_Start();



/*****************************************************************************
 * Description: Initiate Repeated Start condition on SDA and SCL pins
 * 
 *
 *****************************************************************************/
void I2C_Master_RepeatedStart();



/*****************************************************************************
 * Description: Initiate Stop condition on SDA and SCL pins
 * 
 *
 *****************************************************************************/
void I2C_Master_Stop();


/*****************************************************************************
 * Description: used for writing the data field 
 * @param u8_Data: data will be written in the data field
 * 
 *
 *****************************************************************************/
void I2C_Master_Write(uint8 u8_Data);


/*****************************************************************************
 * Description: used for reading the data field 
 * @param * u8_Data: pointer to place where data will be received in the data 
 *                  field 
 * 
 *
 *****************************************************************************/
void I2C_Master_Read(uint8 * pu8_Data);


/*****************************************************************************
 * Description: used for enabling the receive bit 
 *   
 *
 *****************************************************************************/
void I2C_Master_EnableRead();



/*****************************************************************************
 * Description: Initiate Acknowledge sequence on SDA and SCL pins
 * 
 * @param     : u8_ACK_State : holds the state which master will reply with
 *                             (ACKNOWLEDGE or NOT_ACKNOWLEDGE)
 *****************************************************************************/
void I2C_Master_AckEN(uint8 u8_ACK_State);



/*****************************************************************************
 * Description: Polling for receiving ack from slave
 * 
 *
 *****************************************************************************/
void I2C_Master_WaitACK();



#endif