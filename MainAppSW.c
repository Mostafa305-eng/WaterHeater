/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/
#include"MainAppSW.h"
#include"PushButton.h"
#include"TemperatureAvgReading.h"
#include"Display.h"
#include"Cooler.h"
#include"Heater.h"
#include"led.h"
#include"Timer.h"
#include"Interrupts.h"
#include"Interrupt_Config.h"
#include "SSD.h"
#include "Config.h"
#include"LM35.h"
#include "ExternalInterrupt.h"
#include "sleep.h"
#include "EEPROM.h"


/************************************************************************/
/*						        defines                                */
/************************************************************************/

#define UP_BUTTON                   BTN_2
#define DOWN_BUTTON                 BTN_1
#define ON_OFF_BUTTON               BTN_0

#define HEATING_ELEMENT_LED         LED_0
#define LED_OFF                     0
#define LED_ON                      1
#define LED_BLINK                   2
#define LED_BLINK_TIME              1000

#define NO_OF_TICKS_FOR_20MS        5000
#define SETTING_MODE_TIME           5000

#define MAX_TEMPERATURE             75
#define MIN_TEMPERATURE             35

#define WATER_HEATER_ON             10
#define WATER_HEATER_OFF            11
#define WATER_HEATER_SETTING_MODE   12

#define MAIN_LOOP_RUNNING           15
#define MAIN_LOOP_STOPPPED          16

#define CPU_SLEEP                   20
#define CPU_NOT_SLEEP               25


#define TEMPERATURE_FLAG_ADDRESS    0x00
#define TEMPERATURE_ADDRESS         0x01

#define TEMPERATURE_SET             0xAA
#define TEMPERATURE_NOT_SET         0xFF


#define INIT_TEMPERATURE_SET        60


#define APP_PERIOD_MS               20
/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/

uint8 u8_WaterHeaterStatus=WATER_HEATER_OFF;
uint8 u8_MainLoopStatus=MAIN_LOOP_STOPPPED;
uint8 u8_APP_TickCounter=0;
uint8 u8_SetTemperature;

uint16  u16_SettingModeCounter=0;
uint8 u8_AVG_Temperature=0;
uint16 u16_LED_Counter=0;
uint8 u8_Heating_Element_Led_State=LED_OFF;


/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/




/************************************************************************/
/*                   CALLBACK FUNCTIONS OF APP  				        */
/************************************************************************/

static void Timer_Callbk()
{
    Timer_SetValue(TIMER_CH1,NO_OF_TICKS_FOR_20MS);
    u8_MainLoopStatus=MAIN_LOOP_RUNNING;
}




static void EXT_INT_Callbk()
{
    if(u8_WaterHeaterStatus == WATER_HEATER_OFF)
    {
        u8_WaterHeaterStatus = WATER_HEATER_ON;
        Timer_Start(TIMER_CH1,NO_OF_TICKS_FOR_20MS);
        CPU_SetSleep(CPU_NOT_SLEEP);   
   }
    else
    {
        u8_WaterHeaterStatus = WATER_HEATER_OFF;
    }
    
}


/************************************************************************/
/*				    STATIC FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


static void Heater_Cooler_action(void)
{
    if(u8_AVG_Temperature < (u8_SetTemperature-5))
    {
        Heater_Turn(HEATER_ON);
        Cooler_Turn(COOLER_OFF);
        u8_Heating_Element_Led_State=LED_BLINK;
    }
    else if (u8_AVG_Temperature > (u8_SetTemperature+5))
    {
        Heater_Turn(HEATER_OFF);
        Cooler_Turn(COOLER_ON);        
        u8_Heating_Element_Led_State=LED_ON;
    }
}

   

static void LED_ACTION(void)
{
    u16_LED_Counter += APP_PERIOD_MS;
    if((u8_Heating_Element_Led_State == LED_BLINK) && (u16_LED_Counter == LED_BLINK_TIME) )
    {
        Led_Toggle(HEATING_ELEMENT_LED);
        u16_LED_Counter=0;
    }
    else if(u8_Heating_Element_Led_State == LED_ON)
    {
        Led_On(HEATING_ELEMENT_LED);
        u16_LED_Counter=0;
    }
    else if(u8_Heating_Element_Led_State == LED_OFF)
    {
        Led_Off(HEATING_ELEMENT_LED);
        u16_LED_Counter=0;
    }
    
}

    
void App_init()
{
    u8_WaterHeaterStatus=WATER_HEATER_OFF;
    u8_MainLoopStatus=MAIN_LOOP_STOPPPED;
    
    
    pushButton_Init(UP_BUTTON);
    pushButton_Init(DOWN_BUTTON);

    ExternInt_Cfg_s PB_ext_Int={
        EXTERN_INT_RB0,
        FALLING_EDGE,
        EXT_INT_Callbk,
    };
    
    ExternInt_Init(& PB_ext_Int);
    ExternInt_Enable(EXTERN_INT_RB0);

    TemperatureAVGReading_init();
    
    Display_Init();
    
    Cooler_Init();
    Heater_Init();
    Led_Init(HEATING_ELEMENT_LED);
    
   
    str_Timer_cfg_t MyTimer={TIMER_CH1,TIMER_MODE,TIMER_INTERRUPT_MODE,TIMER_PRESCALER_32,Timer_Callbk};
    Timer_Init(&MyTimer);
     
    u8_SetTemperature=INIT_TEMPERATURE_SET;
    uint8 temp;
    EEPROM_Init();
    EEPROM_Read(TEMPERATURE_FLAG_ADDRESS,& temp);

    if(temp != TEMPERATURE_SET)
    {
        EEPROM_Write(TEMPERATURE_FLAG_ADDRESS,TEMPERATURE_SET);
        EEPROM_Write(TEMPERATURE_ADDRESS,INIT_TEMPERATURE_SET);  
    }
    else
    {
        EEPROM_Read(TEMPERATURE_ADDRESS,&u8_SetTemperature);  
    }
    
    INT_SetEnable();
    
    
    CPU_SetSleep(CPU_SLEEP);
}


static void App_Update(void)
{
    
    u8_APP_TickCounter += TICK_MS;

    if (u8_APP_TickCounter != APP_PERIOD_MS){
        return;
    }
    

    u8_APP_TickCounter=0;

    

    uint8 u8_BtnUpStatus=0;
    uint8 u8_BtnDownStatus=0;
    uint8 u8_CurrentTemperature;
    
    

    pushButton_GetStatus(UP_BUTTON,&u8_BtnUpStatus);
    pushButton_GetStatus(DOWN_BUTTON,&u8_BtnDownStatus);
    
    TemperatureAVGReading_Read(&u8_AVG_Temperature);
    
    LM_Read(&u8_CurrentTemperature);
        
    switch (u8_WaterHeaterStatus)
    {
        case WATER_HEATER_OFF :
            Display_TurnOff();
            Cooler_Turn(COOLER_OFF);
            Heater_Turn(HEATER_OFF);
            u8_Heating_Element_Led_State = LED_OFF ;
            Timer_Stop(TIMER_CH1);
            CPU_SetSleep(CPU_SLEEP);
            break;

        case WATER_HEATER_ON :
            Display_SetData(u8_CurrentTemperature,CONTINUOUS_DISPLAY);
            Heater_Cooler_action();
            if(u8_BtnDownStatus == PREPRESSED || u8_BtnUpStatus == PREPRESSED)
            {
                u8_WaterHeaterStatus = WATER_HEATER_SETTING_MODE;
            }
            break;

        case WATER_HEATER_SETTING_MODE:
            Heater_Cooler_action();
            u16_SettingModeCounter +=APP_PERIOD_MS;

            if(u8_BtnDownStatus == PREPRESSED  )
            {
                if(u8_SetTemperature >MIN_TEMPERATURE)
                {
                    u8_SetTemperature-=5;
                }
                u16_SettingModeCounter=0;
            }
            else if(u8_BtnUpStatus == PREPRESSED )
            {
                if(u8_SetTemperature <MAX_TEMPERATURE)
                {
                    u8_SetTemperature+=5;
                }
                u16_SettingModeCounter=0;
            }
            Display_SetData(u8_SetTemperature,BLINKING_DISPLAY);
            if(u16_SettingModeCounter>=SETTING_MODE_TIME)
            {
                u8_WaterHeaterStatus = WATER_HEATER_ON;
                u16_SettingModeCounter=0;
                EEPROM_Write(TEMPERATURE_ADDRESS,u8_SetTemperature); 
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
        if(u8_MainLoopStatus == MAIN_LOOP_RUNNING )
        {
            SSD_Update();
            pushButton_Update();
            TemperatureAVGReading_Update();
            App_Update();
            Display_Update();   
            u8_MainLoopStatus=MAIN_LOOP_STOPPPED;
            CPU_SleepUpdate();            
        }
    }
}

