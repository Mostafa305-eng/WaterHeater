# 1 "MainAppSW.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "MainAppSW.c" 2



# 1 "./MainAppSW.h" 1



void App_init();

void App_MainLoop();
# 4 "MainAppSW.c" 2

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
# 5 "MainAppSW.c" 2

# 1 "./TemperatureAvgReading.h" 1
# 34 "./TemperatureAvgReading.h"
extern void TemperatureAVGReading_init(void);







extern void TemperatureAVGReading_Update(void);
# 54 "./TemperatureAvgReading.h"
extern void TemperatureAVGReading_Read(uint8 *pu8_AVGtemperature);
# 6 "MainAppSW.c" 2

# 1 "./Display.h" 1
# 39 "./Display.h"
void Display_Init(void);







void Display_Update(void);
# 58 "./Display.h"
void Display_SetData(uint8 u8_DisplayData,uint8 u8_DisplayMode);







void Display_TurnOff(void);
# 7 "MainAppSW.c" 2

# 1 "./Cooler.h" 1
# 41 "./Cooler.h"
void Cooler_Init();
# 50 "./Cooler.h"
void Cooler_Turn(uint8 u8_State);
# 8 "MainAppSW.c" 2

# 1 "./Heater.h" 1
# 41 "./Heater.h"
void Heater_Init(void);
# 50 "./Heater.h"
void Heater_Turn(uint8 u8_State);
# 9 "MainAppSW.c" 2

# 1 "./led.h" 1
# 44 "./led.h"
void Led_Init(uint8 u8_LED_ID);







void Led_On(uint8 u8_led_ID);
# 61 "./led.h"
void Led_Off(uint8 u8_led_ID);
# 70 "./led.h"
void Led_Toggle(uint8 u8_led_ID);
# 10 "MainAppSW.c" 2

# 1 "./Timer.h" 1
# 54 "./Timer.h"
typedef struct str_Timer_cfg_t
{
 uint8 Timer_CH_NO;
 uint8 Timer_Mode;
 uint8 Timer_Polling_Or_Interrupt;
 uint8 Timer_Prescaler;
    Ptrfunc aptrf_INT;
}str_Timer_cfg_t;
# 79 "./Timer.h"
 void Timer_Init(str_Timer_cfg_t * st_Timer_cfg);
# 93 "./Timer.h"
void Timer_Start(uint8 u8_Timer_CH_NO, uint16 u16_Timer_Count);
# 105 "./Timer.h"
void Timer_Stop(uint8 u8_Timer_CH_NO);
# 118 "./Timer.h"
void Timer_GetStatus(uint8 u8_Timer_CH_NO, bool* Data);
# 130 "./Timer.h"
void Timer_ClrStatus(uint8 u8_Timer_CH_NO);
# 144 "./Timer.h"
void Timer_GetValue(uint8 u8_Timer_CH_NO, uint16* pu16_Data);
# 157 "./Timer.h"
void Timer_SetValue(uint8 u8_Timer_CH_NO, uint16 u16_Timer_Count);
# 172 "./Timer.h"
void Timer_GetTickTime(uint8 u8_Timer_CH_NO,uint8 * pu8_Time);
# 11 "MainAppSW.c" 2

# 1 "./Interrupts.h" 1
# 15 "./Interrupts.h"
# 1 "./Interrupt_Config.h" 1





# 1 "./Interrupts.h" 1
# 6 "./Interrupt_Config.h" 2
# 15 "./Interrupts.h" 2
# 34 "./Interrupts.h"
void INT_SetEnable(void);
# 47 "./Interrupts.h"
void INT_ClrEnable(void);
# 64 "./Interrupts.h"
void INT_SetCallBackFunc(uint8 u8_INT_Priority,volatile uint8 * pu8_Register,uint8 u8_MASK ,
                         Ptrfunc ptrf_CallBkFunc );
# 12 "MainAppSW.c" 2


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
# 14 "MainAppSW.c" 2

# 1 "./Config.h" 1
# 15 "./Config.h"
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF
# 15 "MainAppSW.c" 2

# 1 "./LM35.h" 1
# 39 "./LM35.h"
extern void LM_init(void);







extern void LM_Update(void);
# 59 "./LM35.h"
extern void LM_Read(uint8 *pu8_temperature);
# 16 "MainAppSW.c" 2

# 1 "./ExternalInterrupt.h" 1
# 34 "./ExternalInterrupt.h"
typedef struct ExternInt_Cfg_s{

 uint8 ExternInt_No;
 uint8 ExternInt_Event;
 void (*ExternInt_CBF_Ptr)(void);
}ExternInt_Cfg_s;
# 57 "./ExternalInterrupt.h"
void ExternInt_Init(ExternInt_Cfg_s * pstr_ExternIntCfg);
# 70 "./ExternalInterrupt.h"
void ExternInt_SetEvent(uint8 u8_InterruptEvent);
# 82 "./ExternalInterrupt.h"
void ExternInt_GetStatus(uint8 *pu8_Status);
# 93 "./ExternalInterrupt.h"
void ExternInt_Enable(uint8 u8_ExternInt_Type);
# 107 "./ExternalInterrupt.h"
void ExternInt_Disable(uint8 u8_ExternInt_Type);
# 17 "MainAppSW.c" 2

# 1 "./sleep.h" 1
# 43 "./sleep.h"
void CPU_SetSleep(uint8 u8_SleepMode);
# 54 "./sleep.h"
void CPU_SleepUpdate();
# 18 "MainAppSW.c" 2

# 1 "./EEPROM.h" 1
# 23 "./EEPROM.h"
void EEPROM_Init();
# 32 "./EEPROM.h"
void EEPROM_Write(uint8 u8_Address,uint8 u8_Data);
# 42 "./EEPROM.h"
void EEPROM_Read(uint8 u8_Address,uint8 * pu8_Data);
# 19 "MainAppSW.c" 2
# 68 "MainAppSW.c"
uint8 u8_WaterHeaterStatus=11;
uint8 u8_MainLoopStatus=16;
uint8 u8_APP_TickCounter=0;
uint8 u8_SetTemperature;
uint8 u8_DisplayMode=2;
uint16 u16_SettingModeCounter=0;
uint8 u8_AVG_Temperature=0;
uint16 u16_LED_Counter=0;
uint8 u8_Heating_Element_Led_State=0;
# 90 "MainAppSW.c"
static void Timer_Callbk()
{
    Timer_SetValue(1,5000);
    u8_MainLoopStatus=15;
}




static void EXT_INT_Callbk()
{
    if(u8_WaterHeaterStatus == 11)
    {
        u8_WaterHeaterStatus = 10;
        Timer_Start(1,5000);
        CPU_SetSleep(25);
   }
    else
    {
        u8_WaterHeaterStatus = 11;
    }

}







static void Heater_Cooler_action(void)
{
    if(u8_AVG_Temperature < (u8_SetTemperature-5))
    {
        Heater_Turn(0xFF);
        Cooler_Turn(0);
        u8_Heating_Element_Led_State=2;
    }
    else if (u8_AVG_Temperature > (u8_SetTemperature+5))
    {
        Heater_Turn(0);
        Cooler_Turn(0xFF);
        u8_Heating_Element_Led_State=1;
    }
}



static void LED_ACTION(void)
{
    u16_LED_Counter += 20;
    if((u8_Heating_Element_Led_State == 2) && (u16_LED_Counter == 1000) )
    {
        Led_Toggle(0);
        u16_LED_Counter=0;
    }
    else if(u8_Heating_Element_Led_State == 1)
    {
        Led_On(0);
        u16_LED_Counter=0;
    }
    else if(u8_Heating_Element_Led_State == 0)
    {
        Led_Off(0);
        u16_LED_Counter=0;
    }

}


void App_init()
{
    u8_WaterHeaterStatus=11;
    u8_MainLoopStatus=16;


    pushButton_Init(2);
    pushButton_Init(1);

    ExternInt_Cfg_s zft={
        0,
        2,
        EXT_INT_Callbk,
    };

    ExternInt_Init(& zft);
    ExternInt_Enable(0);

    TemperatureAVGReading_init();

    Display_Init();

    Cooler_Init();
    Heater_Init();
    Led_Init(0);


    str_Timer_cfg_t MyTimer={1,0,1,6,Timer_Callbk};
    Timer_Init(&MyTimer);

    u8_SetTemperature=60;
    uint8 temp;
    EEPROM_Init();
    EEPROM_Read(0x00,& temp);

    if(temp != 0xAA)
    {
        EEPROM_Write(0x00,0xAA);
        EEPROM_Write(0x01,60);
    }
    else
    {
        EEPROM_Read(0x01,&u8_SetTemperature);
    }

    INT_SetEnable();


    CPU_SetSleep(20);
}


static void App_Update(void)
{

    u8_APP_TickCounter += 20;

    if (u8_APP_TickCounter != 20){
        return;
    }


    u8_APP_TickCounter=0;



    uint8 u8_BtnUpStatus=0;
    uint8 u8_BtnDownStatus=0;
    uint8 u8_CurrentTemperature;



    pushButton_GetStatus(2,&u8_BtnUpStatus);
    pushButton_GetStatus(1,&u8_BtnDownStatus);

    TemperatureAVGReading_Read(&u8_AVG_Temperature);

    LM_Read(&u8_CurrentTemperature);

    switch (u8_WaterHeaterStatus)
    {
        case 11 :
            Display_TurnOff();
            Cooler_Turn(0);
            Heater_Turn(0);
            u8_DisplayMode=2;
            u8_Heating_Element_Led_State = 0 ;
            Timer_Stop(1);
            CPU_SetSleep(20);
            break;

        case 10 :
            Display_SetData(u8_CurrentTemperature,2);
            Heater_Cooler_action();
            if(u8_BtnDownStatus == 0x11 || u8_BtnUpStatus == 0x11)
            {
                u8_WaterHeaterStatus = 12;
            }
            break;

        case 12:
            Heater_Cooler_action();
            u16_SettingModeCounter +=20;

            if(u8_BtnDownStatus == 0x11 )
            {
                if(u8_SetTemperature >35)
                {
                    u8_SetTemperature-=5;
                }
                u16_SettingModeCounter=0;
            }
            else if(u8_BtnUpStatus == 0x11 )
            {
                if(u8_SetTemperature <75)
                {
                    u8_SetTemperature+=5;
                }
                u16_SettingModeCounter=0;
            }
            Display_SetData(u8_SetTemperature,1);
            if(u16_SettingModeCounter>=5000)
            {
                u8_WaterHeaterStatus = 10;
                u16_SettingModeCounter=0;
                EEPROM_Write(0x01,u8_SetTemperature);
            }
            break;

        default:
            break;
    }


    LED_ACTION();

}





void App_MainLoop()
{
    while(1)
    {
        if(u8_MainLoopStatus == 15 )
        {
            SSD_Update();
            pushButton_Update();
            TemperatureAVGReading_Update();
            App_Update();
            Display_Update();
            u8_MainLoopStatus=16;
            CPU_SleepUpdate();
        }
    }
}
