/*
 * LM35.h
 *
 * Created: 1/24/2020 2:23:33 PM
 *  Author: Mostafa Metwaly
 */ 


#ifndef LM35_H_
#define LM35_H_

/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/

#include "common_macros.h"
#include "std_types.h"


/******************************************************************************************
*                                                                                         *
*                                 PROTOTYPES                                              *
*																						  *
*																						  *
*******************************************************************************************/


/**************************************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function initializes the LM35 module.
 * 							
 **************************************************************************/
extern void LM_init(void);


/**************************************************************************************************
 * Description: Update the reading of lm35
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 ************************************************************************************************/
extern void LM_Update(void);



/**************************************************************************
 * Input: 
 * Output: pu8_temperature ==> value of reading
 * In/Out:			
 * Return: 		
 * Description: This function reads temperature from LM35 module.
 * 							
 **************************************************************************/
extern void LM_Read(uint8 *pu8_temperature);


#endif /* LM35_H_ */