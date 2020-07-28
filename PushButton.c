/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "PushButton.h"
#include "PB_Config.h"
#include "DIO.h"


#include"led.h"

/************************************************************************/
/*						        defines                                */
/************************************************************************/

#define FIRST_SAMPLE        0
#define SECOND_SAMPLE       1
#define NUMBER_OF_SAMPLES   2

#define PRESSED_LEVEL       LOW
#define RELEASED_LEVEL      HIGH


#define PB_PERIOD_MS        20

/************************************************************************/
/*						Typedefs defines                               	*/
/************************************************************************/

typedef enum EN_buttonInit_t{
	Init,
	NotInit
}EN_buttonInit_t;

typedef struct ST_buttons_t{
	uint8 buttonGpio;
	uint8 buttonBit;
	uint8 buttonStatus;
	EN_buttonInit_t buttonInit;
	uint8 samples[NUMBER_OF_SAMPLES];
}ST_buttons_t;

/************************************************************************/
/*						Static Variables                               	*/
/************************************************************************/

static ST_buttons_t STA_buttons[]={ {BTN_0_GPIO,BTN_0_BIT,RELEASED,NotInit,{RELEASED_LEVEL,RELEASED_LEVEL}},
									{BTN_1_GPIO,BTN_1_BIT,RELEASED,NotInit,{RELEASED_LEVEL,RELEASED_LEVEL}},
									{BTN_2_GPIO,BTN_2_BIT,RELEASED,NotInit,{RELEASED_LEVEL,RELEASED_LEVEL}},
									{BTN_3_GPIO,BTN_3_BIT,RELEASED,NotInit,{RELEASED_LEVEL,RELEASED_LEVEL}},
									} ;


 static uint8 u8_PB_TickCounter = 0;

 
/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/



/*********************************************************************
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the defines
 *
 ************************************************************************/

void pushButton_Init(uint8 u8_PushbuttonID){
    u8_PB_TickCounter = 0;
	switch(u8_PushbuttonID){
		case (BTN_0) :
            DIO_init(BTN_0_GPIO,BTN_0_BIT,INPUT);
			STA_buttons[BTN_0].buttonInit=Init;
			break;
		case (BTN_1) :
			DIO_init(BTN_1_GPIO,BTN_1_BIT,INPUT);
			STA_buttons[BTN_1].buttonInit=Init;
			break;
		case (BTN_2) :
			DIO_init(BTN_2_GPIO,BTN_2_BIT,INPUT);
            STA_buttons[BTN_2].buttonInit=Init;
			break;
		case (BTN_3) :
			DIO_init(BTN_3_GPIO,BTN_3_BIT,INPUT);
			STA_buttons[BTN_3].buttonInit=Init;
			break;
	}

}



/**************************************************************************************************
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 ************************************************************************************************/
void pushButton_Update(void)
{
    u8_PB_TickCounter += TICK_MS;

    if (u8_PB_TickCounter!= PB_PERIOD_MS){
        return;
    }
 
    u8_PB_TickCounter = 0 ;
            
	uint8 counter;


    for (counter=0;counter<BTN_MAX_NUM;counter++)
    {
        if((STA_buttons+counter)->buttonInit==Init)
        {
        /* save the second simple in the old one to take new simple*/
        (STA_buttons+counter)->samples[FIRST_SAMPLE] = (STA_buttons+counter)->samples[SECOND_SAMPLE] ;
        
            /* take a new sample */
            DIO_Read((STA_buttons+counter)->buttonGpio,(STA_buttons+counter)->buttonBit
                    ,  &(STA_buttons+counter)->samples[SECOND_SAMPLE]  );

            if ( (STA_buttons+counter)->samples[FIRST_SAMPLE] == (STA_buttons+counter)->samples[SECOND_SAMPLE] )
            {
                switch ((STA_buttons+counter)->buttonStatus)
                {
                    case RELEASED :
                        if((STA_buttons+counter)->samples[SECOND_SAMPLE] == PRESSED_LEVEL )
                        {
                            (STA_buttons+counter)->buttonStatus=PREPRESSED;
                        }
                        else
                        {

                        }
                        break;

                    case PRERELEASED :
                        if((STA_buttons+counter)->samples[SECOND_SAMPLE] == PRESSED_LEVEL)
                        {
                            (STA_buttons+counter)->buttonStatus=PREPRESSED;
                        }
                        else
                        {
                            (STA_buttons+counter)->buttonStatus=RELEASED;
                        }
                        break;

                    case PREPRESSED :
                        if((STA_buttons+counter)->samples[SECOND_SAMPLE] == PRESSED_LEVEL)
                                (STA_buttons+counter)->buttonStatus=PRESSED;
                        else
                                (STA_buttons+counter)->buttonStatus=PRERELEASED;
                        break;

                    case PRESSED :
                        if((STA_buttons+counter)->samples[SECOND_SAMPLE] == RELEASED_LEVEL)
                            (STA_buttons+counter)->buttonStatus=PRERELEASED;
                        break;
                }
            }
        }
    }
}


/**************************************************************************************
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 *************************************************************************************/
void  pushButton_GetStatus(uint8 u8_BtnId,uint8 * pu8_BtnState)
{
	switch (u8_BtnId)
	{
		case BTN_0:
			*pu8_BtnState = STA_buttons[BTN_0].buttonStatus;
			break;
		case BTN_1:
			*pu8_BtnState = STA_buttons[BTN_1].buttonStatus;
			break;
		case BTN_2:
			*pu8_BtnState = STA_buttons[BTN_2].buttonStatus;
			break;
		case BTN_3:
			*pu8_BtnState = STA_buttons[BTN_3].buttonStatus;
			break;
	}
}








