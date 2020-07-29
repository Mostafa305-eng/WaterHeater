# 1 "LM35.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "LM35.c" 2
# 14 "LM35.c"
# 1 "./common_macros.h" 1
# 14 "LM35.c" 2

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
# 15 "LM35.c" 2


# 1 "./LM35.h" 1
# 39 "./LM35.h"
extern void LM_init(void);







extern void LM_Update(void);
# 59 "./LM35.h"
extern void LM_Read(uint8 *pu8_temperature);
# 17 "LM35.c" 2

# 1 "./ADC.h" 1
# 88 "./ADC.h"
extern void ADC_init(uint8 u8_ADC_Channels_Config , uint8 u8_ADC_adjustResult , uint8 u8_ADC_Mode ,
                    uint8 u8_ADC_prescaler , Ptrfunc ptrf_ADC_cbk);
# 100 "./ADC.h"
extern void ADC_startConversion(uint8 u8_channel);
# 115 "./ADC.h"
extern void ADC_ReadResult(uint16 *ptru16_Result);
# 18 "LM35.c" 2

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
# 19 "LM35.c" 2

# 1 "./LM35_Config.h" 1
# 20 "LM35.c" 2
# 33 "LM35.c"
uint16 u16_ADCReading;







void LM_ReadingADC_CBK(void)
{
 ADC_ReadResult(&u16_ADCReading);
}
# 53 "LM35.c"
extern void LM_init(void)
{
    ADC_init((0x00),(0x80),(0x00),(0x02),((void *)0));






    DIO_Write(0,0x04,0xFF);




 u16_ADCReading=0;

}







extern void LM_Update(void)
{
        ADC_startConversion((0x10));
        ADC_ReadResult(&u16_ADCReading);
}
# 91 "LM35.c"
extern void LM_Read(uint8 *pu8_temperature)
{
 *pu8_temperature = (u16_ADCReading * 4.88/10);


}
