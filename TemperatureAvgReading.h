#ifndef TEMPERATUREAVGREADING_H_
#define TEMPERATUREAVGREADING_H_


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
 * Description: This function initializes the module.
 * 							
 **************************************************************************/
extern void TemperatureAVGReading_init(void);


/**************************************************************************************************
 * Description: Update the reading of lm35
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 ************************************************************************************************/
extern void TemperatureAVGReading_Update(void);



/**************************************************************************
 * Input: 
 * Output: pu8_AVGtemperature ==> value of reading
 * In/Out:			
 * Return: 		
 * Description: This function reads AVG temperature from LM35 module.
 * 							
 **************************************************************************/
extern void TemperatureAVGReading_Read(uint8 *pu8_AVGtemperature);


#endif