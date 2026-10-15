#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

void OLED_Init(void);
void OLED_ShowString(uint8_t row, uint8_t col, const char *str);
void OLED_ShowDec(uint8_t row,uint8_t col,int num);
void OLED_ShowHex(uint8_t row,uint8_t col,int num);

#endif