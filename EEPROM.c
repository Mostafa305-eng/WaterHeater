/*
 * File:   EEPROM.c
 * Author: mosta
 *
 * Created on July 11, 2020, 3:36 PM
 */

/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/
#include "I2C.h"
#include <pic16f877a.h>
#include "EEPROM.h"



/************************************************************************/
/*						        defines                                */
/************************************************************************/


#define EEPROM_ADDRESS_WRITE    0xA0
#define EEPROM_ADDRESS_READ     0xA1

#define BAUDREATE_100KHZ       100000




/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/




/*****************************************************************************
 * Description: init the module 
 * 
 *
 *****************************************************************************/
void EEPROM_Init()
{
    I2C_Master_Init(I2C_POLLING_MODE,BAUDREATE_100KHZ);                
}


/*****************************************************************************
 * Description: write data in eeprom
 * @param: uint8 u8_Address : the required address where the data will be written 
 *         uint8 u8_Data    :  the data will be written 
 *
 *****************************************************************************/
void EEPROM_Write(uint8 u8_Address,uint8 u8_Data)
{
    I2C_Master_Start();

    I2C_Master_Write(EEPROM_ADDRESS_WRITE);

    I2C_Master_Write(u8_Address);

    I2C_Master_Write(u8_Data);

    I2C_Master_Stop();         
    
}



/*****************************************************************************
 * Description: Read data from EEPROM
 * @param: u8_Address : the required address where the data will be read 
 *         pu8_Data    :  the data will be read 
 *
 *****************************************************************************/
void EEPROM_Read(uint8 u8_Address,uint8 * pu8_Data)
{
    I2C_Master_Start();    
    I2C_Master_Write(EEPROM_ADDRESS_WRITE);
    I2C_Master_WaitACK();
    I2C_Master_Write(u8_Address);
    I2C_Master_WaitACK();    
    I2C_Master_Stop();         
    
  

    I2C_Master_Start(); 
    I2C_Master_WaitACK();

    I2C_Master_Write(EEPROM_ADDRESS_READ);
    I2C_Master_WaitACK();


    I2C_Master_EnableRead();

    I2C_Master_Read(pu8_Data);


    I2C_Master_AckEN(NOT_ACKNOWLEDGE);

    I2C_Master_Stop(); 

         
}