#ifndef __UART_CONNECT_H__
#define __UART_CONNECT_H__

#include "main.h"
#include <string.h>


extern volatile uint8_t UART_RX_Index;
extern volatile char UART_RX_Buffer[64];
extern volatile uint8_t UART_RX_Flag;
extern volatile char UART_Data[64];


void UART_StartReceive(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void UART_SendString(const char *data);
void UART_SendStatus(const char *status);
void UART_Send_Light_data(uint32_t data);
void UART_Send_Tep_data(float data);

#endif
