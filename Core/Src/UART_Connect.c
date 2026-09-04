#include "UART_Connect.h"

volatile uint8_t UART_RX_Data;
volatile uint8_t UART_RX_Index = 0;
volatile char UART_RX_Buffer[64];
volatile uint8_t UART_RX_Flag = 0;



void UART_StartReceive(void)
{
	HAL_UART_Receive_IT(&huart1, &UART_RX_Data, 1);
}

//
/**
    Pump:ON
	Pump:OFF
	Heater:ON
	Heater:OFF
	Light:ON
	Light:OFF
	Feed

	Get_Temperature
	Get_Light

	Pump:status
	Heater:status
	Light:status
	Feed:status
 * */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)
	{
		if(UART_RX_Data == '\r')
		{
		            // 忽略回车
		}
		else if(UART_RX_Data=='#'||UART_RX_Data=='\n')
		{
			UART_RX_Buffer[UART_RX_Index]='\0';
			UART_RX_Index=0;
			UART_RX_Flag = 1;
		}
		else if(UART_RX_Index<sizeof(UART_RX_Buffer)-1)
		{
			UART_RX_Buffer[UART_RX_Index++]=UART_RX_Data;
		}


		 HAL_UART_Receive_IT(&huart1, &UART_RX_Data, 1);
	}
}

/*
	TEMP:26.5
	LIGHT:650

	Pump:ON
	Pump:OFF
	Heater:ON
	Heater:OFF
	Light:ON
	Light:OFF
	Feed


 */
void UART_SendString(const char*data)
{
	HAL_UART_Transmit(&huart1, data, strlen(data), 100);
}


