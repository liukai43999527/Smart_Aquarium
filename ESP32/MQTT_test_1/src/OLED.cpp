#include "OLED.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 4
#define OLED_SCL 5

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void OLED_Init(void)
{
    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        while (1);
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.display();
}

void OLED_ShowString(uint8_t row, uint8_t col, const char *str)
{
    //display.clearDisplay();
    //清除当前位置的一行区域
    display.fillRect(col*6, row*8, 128, 8, SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(col * 6, row * 8);
    display.print(str);
    display.display();
}


//显示十进制数字
void OLED_ShowDec(uint8_t row,uint8_t col,int num)
{
    //清除当前位置的一行区域
    display.fillRect(col*6, row*8, 128, 8, SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(col*6,row*8);
    display.print(num,DEC);
    display.display();
}

//显示十六进制数字
void OLED_ShowHex(uint8_t row,uint8_t col,int num)
{
    //清除当前位置的一行区域
    display.fillRect(col*6, row*8, 128, 8, SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(col*6,row*8);
    display.print(num,HEX);
    display.display();
}











