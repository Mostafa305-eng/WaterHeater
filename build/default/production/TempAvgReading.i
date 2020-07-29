# 1 "TempAvgReading.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "TempAvgReading.c" 2
# 16 "TempAvgReading.c"
# 1 "./TemperatureAvgReading.h" 1
# 12 "./TemperatureAvgReading.h"
# 1 "./common_macros.h" 1
# 12 "./TemperatureAvgReading.h" 2

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
# 13 "./TemperatureAvgReading.h" 2
# 34 "./TemperatureAvgReading.h"
extern void TemperatureAVGReading_init(void);







extern void TemperatureAVGReading_Update(void);
# 54 "./TemperatureAvgReading.h"
extern void TemperatureAVGReading_Read(uint8 *pu8_AVGtemperature);
# 16 "TempAvgReading.c" 2

# 1 "./LM35.h" 1
# 39 "./LM35.h"
extern void LM_init(void);







extern void LM_Update(void);
# 59 "./LM35.h"
extern void LM_Read(uint8 *pu8_temperature);
# 17 "TempAvgReading.c" 2
# 34 "TempAvgReading.c"
uint8 au8_TemperatureSamples[10]={0,0,0,0,0,0,0,0,0,0};



uint8 u8_TR_TickCounter=0;
# 52 "TempAvgReading.c"
extern void TemperatureAVGReading_init(void)
{
    LM_init();
}
# 64 "TempAvgReading.c"
extern void TemperatureAVGReading_Update(void)
{
        u8_TR_TickCounter += 20;

    if (u8_TR_TickCounter != 100){
        return;
    }

    u8_TR_TickCounter = 0 ;


    uint8 u8_LMTemperature;
    uint8 u8_LoopCounter;

    LM_Update();
    LM_Read(&u8_LMTemperature);

    for(u8_LoopCounter=0;u8_LoopCounter < (10 -1);u8_LoopCounter++)
    {
        au8_TemperatureSamples[u8_LoopCounter] = au8_TemperatureSamples[(u8_LoopCounter+1)];
    }

    au8_TemperatureSamples[9]=u8_LMTemperature;


}
# 101 "TempAvgReading.c"
extern void TemperatureAVGReading_Read(uint8 *pu8_AVGtemperature)
{
    uint16 u16_CurrentAvgTemerature=0;
    uint8 u8_LoopCounter;
    for(u8_LoopCounter=0;u8_LoopCounter < (10);u8_LoopCounter++)
    {
        u16_CurrentAvgTemerature += au8_TemperatureSamples[u8_LoopCounter];
    }
    u16_CurrentAvgTemerature /= 10;

    *pu8_AVGtemperature=u16_CurrentAvgTemerature;
}
