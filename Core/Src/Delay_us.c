#include "Delay_us.h"

extern TIM_HandleTypeDef htim6;


void Delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim6, 0);

    while (__HAL_TIM_GET_COUNTER(&htim6) < us);
}
