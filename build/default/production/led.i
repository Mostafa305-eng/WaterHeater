# 1 "led.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "led.c" 2
# 11 "led.c"
# 1 "./led.h" 1
# 15 "./led.h"
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
# 15 "./led.h" 2
# 44 "./led.h"
void Led_Init(uint8 u8_LED_ID);







void Led_On(uint8 u8_led_ID);
# 61 "./led.h"
void Led_Off(uint8 u8_led_ID);
# 70 "./led.h"
void Led_Toggle(uint8 u8_led_ID);
# 11 "led.c" 2

# 1 "./ledConfig.h" 1
# 11 "./ledConfig.h"
# 1 "./DIO.h" 1
# 16 "./DIO.h"
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
# 11 "./ledConfig.h" 2
# 12 "led.c" 2
# 29 "led.c"
void Led_Init(uint8 u8_LED_ID){
 switch(u8_LED_ID){
  case (0) :
            DIO_init((1),(0x80),0x00);
   break;
  case (1) :
            DIO_init((1),(0x40),0x00);
   break;
  case (2) :
            DIO_init((1),(0x20),0x00);
   break;
  case (3) :
            DIO_init((1),(0x10),0x00);
   break;
  default:
   break;
 }
}
# 56 "led.c"
void Led_On(uint8 u8_led_ID){
 switch(u8_led_ID){
  case (0) :
   DIO_Write((1), (0x80) , 0xFF);
   break;
  case (1) :
   DIO_Write((1), (0x40) , 0xFF);
   break;
  case (2) :
   DIO_Write((1), (0x20) , 0xFF);
   break;
  case (3) :
   DIO_Write((1), (0x10) , 0xFF);
   break;
 }
}
# 80 "led.c"
void Led_Off(uint8 u8_led_ID){
 switch(u8_led_ID){
  case (0) :
   DIO_Write((1), (0x80) , 0);
   break;
  case (1) :
   DIO_Write((1), (0x40) , 0);
   break;
  case (2) :
   DIO_Write((1), (0x20) , 0);
   break;
  case (3) :
   DIO_Write((1), (0x10) , 0);
   break;
 }
}







void Led_Toggle(uint8 u8_led_ID){
 switch(u8_led_ID){
  case (0) :
   DIO_Toggle((1), (0x80) );
   break;
  case (1) :
   DIO_Toggle((1), (0x40) );
   break;
  case (2) :
   DIO_Toggle((1), (0x20) );
   break;
  case (3) :
   DIO_Toggle((1), (0x10) );
   break;
 }
}
