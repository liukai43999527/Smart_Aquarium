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
}

void Light_OFF(void)
{
	HAL_GPIO_WritePin(GPIOG,LED_Pin,GPIO_PIN_RESET);
}

void heater_ON(void)
{
	HAL_GPIO_WritePin(GPIOG,heater_Pin,GPIO_PIN_RESET);
}

void heater_OFF(void)
{
	HAL_GPIO_WritePin(GPIOG,heater_Pin,GPIO_PIN_SET);
}

void Pump_ON(void)
{
	HAL_GPIO_WritePin(GPIOG,pump_Pin,GPIO_PIN_RESET);
}

void Pump_OFF(void)
{
	HAL_GPIO_WritePin(GPIOG,pump_Pin,GPIO_PIN_SET);
}

