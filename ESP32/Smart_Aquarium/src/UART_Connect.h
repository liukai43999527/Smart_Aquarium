#ifndef __UART_CONNECT__H__
#define __UART_CONNECT__H__

#include <Arduino.h>

#define RX_Pin 17
#define TX_Pin 18

extern uart_t*uart_1;

void UART_Init_setup();
void UART_SendString(const char *data);
String UART_ReceiveString();

#endif