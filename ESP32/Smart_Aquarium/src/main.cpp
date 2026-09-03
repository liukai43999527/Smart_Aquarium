#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "wifi_Connect.h"
#include "MQTT_Connect.h"
#include "UART_Connect.h"
#include "OLED.h"
#define LED_PIN 12
String RX_data="";

// ==================== setup ====================
void setup()
{
    OLED_Init();
    WIFI_connect();
    MQTT_Init_setup();
    UART_Init_setup();

    pinMode(LED_PIN,OUTPUT);
    digitalWrite(LED_PIN, LOW);
}


// ==================== loop ====================
void loop()
{
    MQTT_Init_loop();
    
    UART_SendString("Pump:ON\n");
    delay(1000);
    UART_SendString("Get_Temperature\n");
    delay(1000);

    if( uartAvailable(uart_1)>0)
    {
        RX_data=UART_ReceiveString();
        OLED_ShowString(4,0,RX_data.c_str());
    }


}