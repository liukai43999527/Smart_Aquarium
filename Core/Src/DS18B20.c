#include "DS18B20.h"
#include "OneWire.h"


void DS18B20_ConvertT(void)
{
	OneWire_Init();
	HAL_Delay(1000);
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

float DS18B20_Read_T(void)
{
	uint8_t TLSB,TMSB;
	int16_t Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB=OneWire_ReceiveByte();
	TMSB=OneWire_ReceiveByte();
	Temp=(TMSB<<8)|TLSB;//16位整数
	T=Temp/16.0;//八位整数，八位小数
	return T;

}

