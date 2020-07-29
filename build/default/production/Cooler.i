# 1 "Cooler.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Cooler.c" 2
# 13 "Cooler.c"
# 1 "./Cooler.h" 1
# 17 "./Cooler.h"
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
# 17 "./Cooler.h" 2

# 1 "./common_macros.h" 1
# 18 "./Cooler.h" 2
# 41 "./Cooler.h"
void Cooler_Init();
# 50 "./Cooler.h"
void Cooler_Turn(uint8 u8_State);
# 13 "Cooler.c" 2

# 1 "./Cooler_Config.h" 1





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
# 6 "./Cooler_Config.h" 2
# 14 "Cooler.c" 2
# 30 "Cooler.c"
void Cooler_Init()
{
    DIO_init(2,0x04,0x00);
}







void Cooler_Turn(uint8 u8_State)
{
    DIO_Write(2,0x04,u8_State);
}
