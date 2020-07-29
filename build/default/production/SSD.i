# 1 "SSD.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "SSD.c" 2
# 12 "SSD.c"
# 1 "./SSD.h" 1
# 17 "./SSD.h"
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
# 17 "./SSD.h" 2

# 1 "./common_macros.h" 1
# 18 "./SSD.h" 2
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
# 12 "SSD.c" 2

# 1 "./SSD_Config.h" 1







# 1 "./DIO.h" 1
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
# 8 "./SSD_Config.h" 2
# 13 "SSD.c" 2
# 30 "SSD.c"
typedef struct ST_SSD_t{
 uint8 u8_SSD_Data;
    uint8 u8_SSD_State;
}ST_SSD_t;





static ST_SSD_t astr_SSDs[]={ {0,0,},
                            {0,0},
                            {0,0},
                            {0,0},
                            } ;

static uint8 u8_SSD_Current=0;


static uint8 au8_SSD_DataMask[] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
};


 static uint8 u8_SSD_TickCounter = 0;
# 76 "SSD.c"
void SSD_Init(uint8 u8_SSD_ID)
{

    u8_SSD_Current=0;
    u8_SSD_TickCounter = 0;

    switch(u8_SSD_ID)
    {
        case 0 :
            DIO_init(0,0x20,0x00);
            break;
        case 1 :
            DIO_init(0,0x10,0x00);
            break;
        case 2 :
            DIO_init(0,0x08,0x00);
            break;
        case 3 :
            DIO_init(0,0x04,0x00);
            break;
        default :
            break;
    }
    DIO_init(3,0xFF,0x00);
}
# 110 "SSD.c"
void SSD_Update(void)
{


    u8_SSD_TickCounter += 20;

    if (u8_SSD_TickCounter != 20){
        return;
    }

    u8_SSD_TickCounter = 0 ;


    DIO_Write(0,0x20,0);
    DIO_Write(0,0x10,0);
    DIO_Write(0,0x08,0);
    DIO_Write(0,0x04,0);



    if(astr_SSDs[u8_SSD_Current].u8_SSD_State == 1 )
    {

        switch(u8_SSD_Current)
        {
            case 0 :

                DIO_PortWrite (3, au8_SSD_DataMask [ astr_SSDs[u8_SSD_Current].u8_SSD_Data ] );

                DIO_Write(0,0x20,0xFF);
                break;
            case 1 :

                DIO_PortWrite (3, au8_SSD_DataMask [ astr_SSDs[u8_SSD_Current].u8_SSD_Data ] );

                DIO_Write(0,0x10,0xFF);
                break;
            case 2 :

                DIO_PortWrite (3, au8_SSD_DataMask [ astr_SSDs[u8_SSD_Current].u8_SSD_Data ] );

                DIO_Write(0,0x08,0xFF);
                break;
            case 3 :

                DIO_PortWrite (3, au8_SSD_DataMask [ astr_SSDs[u8_SSD_Current].u8_SSD_Data ] );

                DIO_Write(0,0x04,0xFF);
                break;
            default :
                break;
        }
    }
    else
    {
        DIO_Write(3,0xFF,0);
    }


    if(u8_SSD_Current == 1)
    {
        u8_SSD_Current=0;
    }
    else
    {
        u8_SSD_Current++;
    }
# 198 "SSD.c"
}
# 211 "SSD.c"
void SSD_SetValue(uint8 u8_SSD_ID,uint8 u8_SSD_Data)
{
    switch(u8_SSD_ID)
    {
        case 0 :
            astr_SSDs[0].u8_SSD_Data = u8_SSD_Data ;
            break;
        case 1 :
            astr_SSDs[1].u8_SSD_Data = u8_SSD_Data;
            break;
        case 2 :
            astr_SSDs[2].u8_SSD_Data = u8_SSD_Data;
            break;
        case 3 :
            astr_SSDs[3].u8_SSD_Data = u8_SSD_Data;
            break;
        default :
            break;
    }
}
# 241 "SSD.c"
void SSD_SetState(uint8 u8_SSD_ID,uint8 u8_SSD_State)
{
    astr_SSDs[u8_SSD_ID].u8_SSD_State = u8_SSD_State;
}
# 256 "SSD.c"
void SSD_GetState(uint8 u8_SSD_ID,uint8 * u8_SSD_State)
{
    *u8_SSD_State = astr_SSDs[u8_SSD_ID].u8_SSD_State;
}
# 270 "SSD.c"
void SSD_TurnOff(uint8 u8_SSD_ID)
{
    DIO_Write(3,0xFF,0);
    switch(u8_SSD_ID)
    {
        case 0 :
            DIO_Write(0,0x20,0);
            astr_SSDs[0].u8_SSD_State = 0 ;
            break;
        case 1 :
            DIO_Write(0,0x10,0);
            astr_SSDs[1].u8_SSD_State = 0;
            break;
        case 2 :
            DIO_Write(0,0x08,0);
            astr_SSDs[2].u8_SSD_State = 0;
            break;
        case 3 :
            DIO_Write(0,0x04,0);
            astr_SSDs[3].u8_SSD_State = 0;
            break;
        default :
            break;
    }
}
