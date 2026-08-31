#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#define LED_PIN 12
// ==================== WiFi ====================
const char* WIFI_SSID = "vivo Y53s";
const char* WIFI_PASSWORD = "se2ivhpxnhypme6";

// ==================== MQTT ====================
const char* MQTT_SERVER = "192.168.169.109";
const int MQTT_PORT = 1883;

// WiFi
WiFiClient espClient;

// MQTT
PubSubClient mqttClient(espClient);


// ==================== WiFi连接 ====================
void WIFI_connect()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected!");

    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
}


// ==================== MQTT连接 ====================
void MQTT_connect()
{
    Serial.print("Connecting MQTT...");

    while (!mqttClient.connected())
    {
        if (mqttClient.connect("ESP32-001"))
        {
            Serial.println("connected!");

            mqttClient.subscribe("aquarium/sensor/temperature");
            mqttClient.subscribe("aquarium/sensor/light");
            mqttClient.subscribe("aquarium/sensor/water_level");

            mqttClient.subscribe("aquarium/control/pump");
            mqttClient.subscribe("aquarium/control/light");
            mqttClient.subscribe("aquarium/control/feeder");
            mqttClient.subscribe("aquarium/control/heater");

            /*
            mqttClient.subscribe("aquarium/status/pump");
            mqttClient.subscribe("aquarium/status/heater");
            mqttClient.subscribe("aquarium/status/light");
            mqttClient.subscribe("aquarium/status/feeder");
            */
            

        }
        else
        {
            Serial.print("failed, state=");
            Serial.println(mqttClient.state());

            delay(2000);
        }
    }
}


void MQTT_callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Topic: ");
    Serial.println(topic);

    // 把 MQTT 消息转换成 String
    String message = "";

    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    Serial.print("Message: ");
    Serial.println(message);


    // ==================== 灯 ====================
    if (strcmp(topic, "aquarium/control/light") == 0)
    {
        if (message == "ON")
        {
            digitalWrite(LED_PIN, HIGH);
            Serial.println("LED ON");
            
            mqttClient.publish( "aquarium/status/light", "LED ON");
            Serial.println("LED ON published!");

        }
        else if (message == "OFF")
        {
            digitalWrite(LED_PIN, LOW);
            Serial.println("LED OFF");
            mqttClient.publish( "aquarium/status/light", "LED OFF");
            Serial.println("LED OFF published!");
        }
    }


    // ==================== 水泵 ====================
    else if (strcmp(topic, "aquarium/control/pump") == 0)
    {
        if (message == "ON")
        {
            Serial.println("PUMP ON");
            // Pump_On();
        }
        else if (message == "OFF")
        {
            Serial.println("PUMP OFF");
            // Pump_Off();
        }
    }


    // ==================== 加热棒 ====================
    else if (strcmp(topic, "aquarium/control/heater") == 0)
    {
        if (message == "ON")
        {
            Serial.println("HEATER ON");
            // Heater_On();
        }
        else if (message == "OFF")
        {
            Serial.println("HEATER OFF");
            // Heater_Off();
        }
    }


    // ==================== 喂食器 ====================
    else if (strcmp(topic, "aquarium/control/feeder") == 0)
    {
        if (message == "FEED")
        {
            Serial.println("FEED");
            // Feeder_Run();
        }
    }


    
}

// ==================== setup ====================
void setup()
{
    Serial.begin(9600);

    WIFI_connect();

    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(MQTT_callback);
    MQTT_connect();
   
    pinMode(LED_PIN,OUTPUT);
    digitalWrite(LED_PIN, LOW);
}


// ==================== loop ====================
void loop()
{
    mqttClient.loop();

}