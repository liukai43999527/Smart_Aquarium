#ifndef __MQTT_CONNECT_H__
#define __MQTT_CONNECT_H__

#include <PubSubClient.h>
#include <Arduino.h>
#include "wifi_Connect.h"
#include "OLED.h"
#define LED_PIN 12

void MQTT_Init_setup();
void MQTT_Init_loop();

void MQTT_connect();
void MQTT_callback(char* topic, byte* payload, unsigned int length);


#endif


