#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "wifi_Connect.h"
#include "MQTT_Connect.h"
#include "UART_Connect.h"
#include "OLED.h"
#define LED_PIN 12
String RX_data="";

String Pump_Status="OFF";
String Light_Status="OFF";
String Heater_Status="OFF";
String Feed_Status="OFF";

String Temperature="26";
String Light="1023";

hw_timer_t *timer_1 =NULL;
u32_t conuter_Timer_1=0;
volatile bool Publish_Flag = false;
void ARDUINO_ISR_ATTR Interrupt_Timer_1();
void decide_UART_1(void);
// ==================== setup ====================
void setup()
{
    OLED_Init();
    WIFI_connect();
    MQTT_Init_setup();
    UART_Init_setup();

    timer_1=timerBegin(0,80,true);
    timerAttachInterrupt(timer_1,Interrupt_Timer_1,true);
    timerAlarmWrite(timer_1,1000,true);
    timerAlarmEnable(timer_1);

    pinMode(LED_PIN,OUTPUT);
    digitalWrite(LED_PIN, LOW);
}


// ==================== loop ====================
void loop()
{
    MQTT_Init_loop();
    
    if(Publish_Flag)
    {
        Publish_Flag=false;
        digitalWrite(LED_PIN, HIGH);
        MQTT_Publish("aquarium/status/light",Light.c_str());
    }
   
    if( uartAvailable(uart_1)>0)
    {
       decide_UART_1();
    }

    OLED_ShowString(5,0,"Flag");
}



void ARDUINO_ISR_ATTR Interrupt_Timer_1()
{
    conuter_Timer_1++;
    if(conuter_Timer_1==500)
    {
        digitalWrite(LED_PIN, LOW);
    }
    if(conuter_Timer_1==1000)
    {
        conuter_Timer_1=0;
        Publish_Flag=true;
    }
}


void decide_UART_1(void)
{
    RX_data=UART_ReceiveString();
    if(RX_data=="Pump_ON")
    {
        OLED_ShowString(4,0,"Pump_ON");
        Pump_Status="ON";
    }
    if(RX_data=="Pump_OFF")
    {
        OLED_ShowString(4,0,"Pump_OFF");
        Pump_Status="OFF";
    }
    if(RX_data=="Heater_ON")
    {
        OLED_ShowString(4,0,"Heater_ON");
        Heater_Status="ON";
    }
    if(RX_data=="Heater_OFF")
    {
        OLED_ShowString(4,0,"Heater_OFF");
        Heater_Status="OFF";
    }
    if(RX_data=="Light_ON")
    {
        OLED_ShowString(4,0,"Light_ON");
        Light_Status="ON";
    }
    if(RX_data=="Light_OFF")
    {
        OLED_ShowString(4,0,"Light_OFF");
        Light_Status="OFF";
    }
    if(RX_data=="Feed_ON")
    {
        OLED_ShowString(4,0,"Feed_ON");
        Feed_Status="ON";
    }
    if(RX_data=="Feed_OFF")
    {
        OLED_ShowString(4,0,"Feed_OFF");
        Feed_Status="OFF";
    }
    if (RX_data.startsWith("TEMP:"))
    {
        Temperature = RX_data.substring(5);
        OLED_ShowString(4,0,Temperature.c_str());
    }
    if (RX_data.startsWith("LIGHT:"))
    {
        Light = RX_data.substring(6);
        OLED_ShowString(4,0,Light.c_str());
    }

}