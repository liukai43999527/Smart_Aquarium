#include "OneWire.h"

GPIO_PinState OneWire_Init(void)
{
	GPIO_PinState ACKBit;
	HAL_GPIO_WritePin(GPIOA,OneWire_DQ_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,OneWire_DQ_Pin,GPIO_PIN_RESET);
	Delay_us(500);
	HAL_GPIO_WritePin(GPIOA,OneWire_DQ_Pin,GPIO_PIN_SET);
	Delay_us(70);
	ACKBit=HAL_GPIO_ReadPin(GPIOA,OneWire_DQ_Pin);
	Delay_us(400);
	return ACKBit;
}

void OneWire_SendBit(char Bit)
{
	HAL_GPIO_WritePin(GPIOA,OneWire_DQ_Pin,GPIO_PIN_RESET);
	Delay_us(10);
	if(Bit==0)
	{
		HAL_GPIO_WritePin(GPIOA,OneWire_DQ_Pin,GPIO_PIN_RESET);
	}else if(Bit==1)
	{
		HAL_GPIO_WritePin(GPIOA,OneWire_DQ_Pin,GPIO_PIN_SET);
	}
	Delay_us(50);
	HAL_GPIO_WritePin(GPIOA,OneWire_DQ_Pin,GPIO_PIN_SET);

}

uint8_t OneWire_ReceiveBit(void)
{
	uint8_t Bit;
	HAL_GPIO_WritePin(GPIOA,OneWire_DQ_Pin,GPIO_PIN_RESET);
	Delay_us(3);
	HAL_GPIO_WritePin(GPIOA,OneWire_DQ_Pin,GPIO_PIN_SET);
	Delay_us(10);
	Bit=HAL_GPIO_ReadPin(GPIOA,OneWire_DQ_Pin);
	Delay_us(50);
	return Bit;
}

void OneWire_SendByte(uint8_t Byte)
{
	for(int i=0;i<8;i++)
	{
		OneWire_SendBit((Byte >> i) & 0x01);
	}

}

uint8_t OneWire_ReceiveByte(void)
{
	uint8_t Byte=0x00;
	for(int i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit())
		{
			Byte|=0x01<<i;
		}

	}
	return Byte;
}


