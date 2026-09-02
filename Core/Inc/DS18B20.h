#ifndef __DS18B20_H__
#define __DS18B20_H__
#include "main.h"

#define DS18B20_SKIP_ROM		0xCC	//跳过大门
#define DS18B20_CONVERT_T		0x44	//读取新的温度数据到暂存器
#define DS18B20_READ_SCRATCHPAD		0xBE

void DS18B20_ConvertT(void);
float DS18B20_Read_T(void);


#endif
