#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__
#include "main.h"

GPIO_PinState OneWire_Init(void);
void OneWire_SendByte(uint8_t Byte);
uint8_t OneWire_ReceiveByte(void);

#endif
