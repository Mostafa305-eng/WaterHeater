#ifndef PUSHBUTTON_H_INCLUDED
#define PUSHBUTTON_H_INCLUDED

/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "PB_Config.h"
#include "std_types.h"

/************************************************************************/
/*						        defines                                */
/************************************************************************/

#define	BTN_0	0
#define BTN_1	1
#define	BTN_2	2
#define BTN_3	3


#define RELEASED	0x10
#define PREPRESSED	0x11
#define PRESSED		0x12
#define	PRERELEASED	0x13

/************************************************************************/
/*				         FUNCTIONS PROTOTYPES	    			        */
/************************************************************************/


/*********************************************************************
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the defines
 *
 ************************************************************************/

void  pushButton_Init(uint8 u8_PushbuttonID);


/**************************************************************************************************
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 ************************************************************************************************/
void pushButton_Update(void);



/**************************************************************************************
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 *************************************************************************************/
void  pushButton_GetStatus(uint8 u8_BtnId,uint8 * pu8_BtnState);



#endif // PUSHBUTTON_H_INCLUDED
