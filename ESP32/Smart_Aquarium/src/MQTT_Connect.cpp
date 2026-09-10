#include "MQTT_Connect.h"
#include "Global.h"
#include "UART_Connect.h"
// ==================== MQTT ====================
const char* MQTT_SERVER = "192.168.121.110";
const int MQTT_PORT = 1883;


// WiFi
WiFiClient espClient;
// MQTT
PubSubClient mqttClient(espClient);

void MQTT_Init_setup()
{
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(MQTT_callback);
    MQTT_connect();

}

void MQTT_Init_loop()
{
      mqttClient.loop();
}


// ==================== MQTT连接 ====================
void MQTT_connect()
{
    OLED_ShowString(2,0,"Connecting MQTT...");
    int i=0;
    while (!mqttClient.connected())
    {
        if (mqttClient.connect("ESP32-001"))
        {
            OLED_ShowString(3,0,"connected!");
            mqttClient.subscribe("aquarium/sensor/temperature");
            mqttClient.subscribe("aquarium/sensor/light");
           // mqttClient.subscribe("aquarium/sensor/water_level");

            mqttClient.subscribe("aquarium/control/pump");
            mqttClient.subscribe("aquarium/control/light");
            mqttClient.subscribe("aquarium/control/feeder");
            mqttClient.subscribe("aquarium/control/heater");
      
            //mqttClient.subscribe("aquarium/status/pump");
            //mqttClient.subscribe("aquarium/status/heater");
            //mqttClient.subscribe("aquarium/status/light");
            //mqttClient.subscribe("aquarium/status/feeder");
        }
        else
        {
            OLED_ShowString(3,0,"failed");
            i++;
            if(i>2)
            {
                break;
            }
            delay(2000);
        }
    }
}



void MQTT_callback(char* topic, byte* payload, unsigned int length)
{
    //Serial.print("Topic: ");
    //Serial.println(topic);

    // 把 MQTT 消息转换成 String
    String message = "";

    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    //Serial.print("Message: ");
    //Serial.println(message);


    // ==================== 灯 ====================
    if (strcmp(topic, "aquarium/control/light") == 0)
    {
        if (message == "ON")
        {
            digitalWrite(LED_PIN, HIGH);
            UART_SendString("Light:ON#");     
            //mqttClient.publish( "aquarium/status/light", "LED ON");
        }
        else if (message == "OFF")
        {
            digitalWrite(LED_PIN, LOW);
            UART_SendString("Light:OFF#");     
           // mqttClient.publish( "aquarium/status/light", "LED OFF");
            //Serial.println("LED OFF published!");
        }
    }

    // ==================== 水泵 ====================
    else if (strcmp(topic, "aquarium/control/pump") == 0)
    {
        if (message == "ON")
        {
            UART_SendString("Pump:ON#");     
            // Pump_On();
        }
        else if (message == "OFF")
        {
             UART_SendString("Pump:OFF#");
            // Pump_Off();
        }
    }


    // ==================== 加热棒 ====================
    else if (strcmp(topic, "aquarium/control/heater") == 0)
    {
        if (message == "ON")
        {
            UART_SendString("Heater:ON#");
            // Heater_On();
        }
        else if (message == "OFF")
        {
            UART_SendString("Heater:OFF#");
            // Heater_Off();
        }
    }


    // ==================== 喂食器 ====================
    else if (strcmp(topic, "aquarium/control/feeder") == 0)
    {
        if (message == "FEED")
        {
            UART_SendString("Feed:ON#");
            // Feeder_Run();
        }
    }

 // ==================== 亮度 ====================
    else if (strcmp(topic, "aquarium/sensor/light") == 0)
    {
        if (message == "Light")
        {
            String Lig=(String)"Light:"+Light;
            MQTT_Publish("aquarium/sensor/light",Lig.c_str());
        }
    }

// ==================== 温度 ====================
    else if (strcmp(topic, "aquarium/sensor/temperature") == 0)
    {
        if (message == "Tep")
        {
            String Tep=(String)"Tep:"+Temperature;
           MQTT_Publish("aquarium/sensor/temperature",Tep.c_str());
        }
    }


}

void MQTT_Publish(const char*Toptic,const char*payload)
{
    mqttClient.publish(Toptic,payload);
    //mqttClient.publish("aquarium/status/light", "1020");
}


