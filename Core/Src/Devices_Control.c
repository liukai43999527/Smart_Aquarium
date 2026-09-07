#include "Devices_Control.h"

void Devices_Init(void)
{
	HAL_GPIO_WritePin(GPIOG,LED_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG,heater_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG,pump_Pin,GPIO_PIN_RESET);
}

void Light_ON(void)
{
	HAL_GPIO_WritePin(GPIOG,LED_Pin,GPIO_PIN_SET);
	Light_status="Light_ON";
}

void Light_OFF(void)
{
	HAL_GPIO_WritePin(GPIOG,LED_Pin,GPIO_PIN_RESET);
	Light_status="Light_OFF";
}

void Heater_ON(void)
{
	HAL_GPIO_WritePin(GPIOG,heater_Pin,GPIO_PIN_RESET);
	Heater_status="Heater_ON";
}

void Heater_OFF(void)
{
	HAL_GPIO_WritePin(GPIOG,heater_Pin,GPIO_PIN_SET);
	Heater_status="Heater_OFF";
}

void Pump_ON(void)
{
	HAL_GPIO_WritePin(GPIOG,pump_Pin,GPIO_PIN_RESET);
	Pump_status="Pump_ON";
}

void Pump_OFF(void)
{
	HAL_GPIO_WritePin(GPIOG,pump_Pin,GPIO_PIN_SET);
	Pump_status="Pump_OFF";
}
void Feed_ON(void)
{
	Feed_status="Feed_ON";
	Feed_status="Feed_OFF";
}
