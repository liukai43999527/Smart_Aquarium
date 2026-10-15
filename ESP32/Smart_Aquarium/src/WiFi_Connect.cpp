#include "WiFi_Connect.h"
#include "OLED.h"

// ==================== WiFi ====================
const char* WIFI_SSID = "vivo Y53s";
const char* WIFI_PASSWORD = "se2ivhpxnhypme6";


// ==================== WiFi连接 ====================
void WIFI_connect()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    OLED_ShowString(0,0,"Connecting WiFi");
    int i=0;
    while (WiFi.status() != WL_CONNECTED)
    {
        i++;
        delay(500);
        if(i>=6)
        {
            OLED_ShowString(1,0,"WiFi connect fail!");
            return ;
        }
    }
    OLED_ShowString(1,0,"WiFi connected!");
    //Serial.println(WiFi.localIP());
}


