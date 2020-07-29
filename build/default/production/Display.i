# 1 "Display.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Display.c" 2
# 12 "Display.c"
# 1 "./Display.h" 1
# 16 "./Display.h"
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
# 16 "./Display.h" 2

# 1 "./common_macros.h" 1
# 17 "./Display.h" 2
# 39 "./Display.h"
void Display_Init(void);







void Display_Update(void);
# 58 "./Display.h"
void Display_SetData(uint8 u8_DisplayData,uint8 u8_DisplayMode);







void Display_TurnOff(void);
# 12 "Display.c" 2

# 1 "./SSD.h" 1
# 45 "./SSD.h"
void SSD_Init(uint8 u8_SSD_ID);
# 55 "./SSD.h"
void SSD_Update(void);
# 67 "./SSD.h"
void SSD_SetValue(uint8 u8_SSD_ID,uint8 u8_SSD_Data);
# 80 "./SSD.h"
void SSD_SetState(uint8 u8_SSD_ID,uint8 u8_SSD_State);
# 90 "./SSD.h"
void SSD_GetState(uint8 u8_SSD_ID,uint8 * u8_SSD_State);
# 103 "./SSD.h"
void SSD_TurnOff(uint8 u8_SSD_ID);
# 13 "Display.c" 2
# 32 "Display.c"
static uint8 u8_Data=0;
static uint8 u8_Mode=0;
static uint8 u8_DisplayTickCounter=0;
static uint16 u16_DisplayBlinkCounter=0;
# 48 "Display.c"
void Display_Init(void)
{
    SSD_Init(0);
    SSD_Init(1);

    u16_DisplayBlinkCounter=0;
    u8_DisplayTickCounter=0;
    u8_Mode=0;
    u8_Data=0;

}







void Display_Update(void)
{
    u8_DisplayTickCounter += 20 ;


    if (u8_DisplayTickCounter != 40 )
    {
        return;
    }
    u8_DisplayTickCounter=0;

    switch(u8_Mode)
    {
        case 2 :
            SSD_SetState(0,1);
            SSD_SetState(1,1);

            SSD_SetValue(0,u8_Data%10);
            SSD_SetValue(1,u8_Data/10);

            u16_DisplayBlinkCounter = 0 ;
            break;

        case 1 :
            u16_DisplayBlinkCounter+= 40;

            if(u16_DisplayBlinkCounter >= 2000)
            {
                u16_DisplayBlinkCounter=0;
            }
            else if(u16_DisplayBlinkCounter > 1000)
            {
                SSD_SetState(0,0);
                SSD_SetState(1,0);
            }
            else
            {
                SSD_SetState(0,1);
                SSD_SetState(1,1);

                SSD_SetValue(0,u8_Data%10);
                SSD_SetValue(1,u8_Data/10);
            }
            break;


        case 0 :
            SSD_SetState(0,0);
            SSD_SetState(1,0);
            u16_DisplayBlinkCounter=0;
            break;

    }

}
# 130 "Display.c"
void Display_SetData(uint8 u8_DisplayData,uint8 u8_DisplayMode)
{
    u8_Data=u8_DisplayData;
    u8_Mode=u8_DisplayMode;
}
# 144 "Display.c"
void Display_TurnOff(void)
{
    SSD_TurnOff(0);
    SSD_TurnOff(1);
    u8_Mode=0;
}
