# 1 "PushButton.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "PushButton.c" 2




# 1 "./PushButton.h" 1







# 1 "./PB_Config.h" 1







# 1 "./DIO.h" 1
# 15 "./DIO.h"
# 1 "./std_types.h" 1
# 17 "./std_types.h"
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long int uint32;

typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32;

typedef volatile uint8* const reg_type8;
typedef volatile uint16* const reg_type16;
typedef float float32;

typedef void(*Ptrfunc) (void) ;







typedef uint8 bool;
# 15 "./DIO.h" 2

# 1 "./common_macros.h" 1
# 16 "./DIO.h" 2
# 85 "./DIO.h"
void DIO_init(uint8 u8_port, uint8 u8_pins, uint8 u8_direction);
# 116 "./DIO.h"
void DIO_Write (uint8 u8_GPIO, uint8 u8_pins, uint8 u8_value);
# 147 "./DIO.h"
void DIO_Read (uint8 u8_GPIO,uint8 u8_pins, uint8 *pu8_data);
# 174 "./DIO.h"
void DIO_Toggle (uint8 u8_GPIO, uint8 u8_pins);
# 191 "./DIO.h"
void DIO_PortWrite (uint8 u8_GPIO, uint8 u8_value);
# 8 "./PB_Config.h" 2
# 8 "./PushButton.h" 2
# 38 "./PushButton.h"
void pushButton_Init(uint8 u8_PushbuttonID);







void pushButton_Update(void);
# 55 "./PushButton.h"
void pushButton_GetStatus(uint8 u8_BtnId,uint8 * pu8_BtnState);
# 5 "PushButton.c" 2





# 1 "./led.h" 1
# 44 "./led.h"
void Led_Init(uint8 u8_LED_ID);







void Led_On(uint8 u8_led_ID);
# 61 "./led.h"
void Led_Off(uint8 u8_led_ID);
# 70 "./led.h"
void Led_Toggle(uint8 u8_led_ID);
# 10 "PushButton.c" 2
# 30 "PushButton.c"
typedef enum EN_buttonInit_t{
 Init,
 NotInit
}EN_buttonInit_t;

typedef struct ST_buttons_t{
 uint8 buttonGpio;
 uint8 buttonBit;
 uint8 buttonStatus;
 EN_buttonInit_t buttonInit;
 uint8 samples[2];
}ST_buttons_t;





static ST_buttons_t STA_buttons[]={ {1,0x01,0x10,NotInit,{0xFF,0xFF}},
         {1,0x02,0x10,NotInit,{0xFF,0xFF}},
         {1,0x04,0x10,NotInit,{0xFF,0xFF}},
         {0,0x08,0x10,NotInit,{0xFF,0xFF}},
         } ;


 static uint8 u8_PB_TickCounter = 0;
# 70 "PushButton.c"
void pushButton_Init(uint8 u8_PushbuttonID){
    u8_PB_TickCounter = 0;
 switch(u8_PushbuttonID){
  case (0) :
            DIO_init(1,0x01,0xFF);
   STA_buttons[0].buttonInit=Init;
   break;
  case (1) :
   DIO_init(1,0x02,0xFF);
   STA_buttons[1].buttonInit=Init;
   break;
  case (2) :
   DIO_init(1,0x04,0xFF);
            STA_buttons[2].buttonInit=Init;
   break;
  case (3) :
   DIO_init(0,0x08,0xFF);
   STA_buttons[3].buttonInit=Init;
   break;
 }

}
# 100 "PushButton.c"
void pushButton_Update(void)
{
    u8_PB_TickCounter += 20;

    if (u8_PB_TickCounter!= 20){
        return;
    }

    u8_PB_TickCounter = 0 ;

 uint8 counter;


    for (counter=0;counter<(3);counter++)
    {
        if((STA_buttons+counter)->buttonInit==Init)
        {

        (STA_buttons+counter)->samples[0] = (STA_buttons+counter)->samples[1] ;


            DIO_Read((STA_buttons+counter)->buttonGpio,(STA_buttons+counter)->buttonBit
                    , &(STA_buttons+counter)->samples[1] );

            if ( (STA_buttons+counter)->samples[0] == (STA_buttons+counter)->samples[1] )
            {
                switch ((STA_buttons+counter)->buttonStatus)
                {
                    case 0x10 :
                        if((STA_buttons+counter)->samples[1] == 0 )
                        {
                            (STA_buttons+counter)->buttonStatus=0x11;
                        }
                        else
                        {

                        }
                        break;

                    case 0x13 :
                        if((STA_buttons+counter)->samples[1] == 0)
                        {
                            (STA_buttons+counter)->buttonStatus=0x11;
                        }
                        else
                        {
                            (STA_buttons+counter)->buttonStatus=0x10;
                        }
                        break;

                    case 0x11 :
                        if((STA_buttons+counter)->samples[1] == 0)
                                (STA_buttons+counter)->buttonStatus=0x12;
                        else
                                (STA_buttons+counter)->buttonStatus=0x13;
                        break;

                    case 0x12 :
                        if((STA_buttons+counter)->samples[1] == 0xFF)
                            (STA_buttons+counter)->buttonStatus=0x13;
                        break;
                }
            }
        }
    }
}







void pushButton_GetStatus(uint8 u8_BtnId,uint8 * pu8_BtnState)
{
 switch (u8_BtnId)
 {
  case 0:
   *pu8_BtnState = STA_buttons[0].buttonStatus;
   break;
  case 1:
   *pu8_BtnState = STA_buttons[1].buttonStatus;
   break;
  case 2:
   *pu8_BtnState = STA_buttons[2].buttonStatus;
   break;
  case 3:
   *pu8_BtnState = STA_buttons[3].buttonStatus;
   break;
 }
}
