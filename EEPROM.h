#ifndef EEPROM_H
#define	EEPROM_H

/************************************************************************/
/*				 				INCLUDES						        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"


/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/



/*****************************************************************************
 * Description: init the module 
 * 
 *
 *****************************************************************************/
void EEPROM_Init();


/*****************************************************************************
 * Description: write data in eeprom
 * @param: uint8 u8_Address : the required address where the data will be written 
 *         uint8 u8_Data    :  the data will be written 
 *
 *****************************************************************************/
void EEPROM_Write(uint8 u8_Address,uint8 u8_Data);



/*****************************************************************************
 * Description: Read data from EEPROM
 * @param: u8_Address : the required address where the data will be read 
 *         pu8_Data    :  the data will be read 
 *
 *****************************************************************************/
void EEPROM_Read(uint8 u8_Address,uint8 * pu8_Data);

#endif	

