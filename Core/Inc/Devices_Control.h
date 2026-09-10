#ifndef __DEVICES_CONTROL__
#define __DEVICES_CONTROL__

#include "main.h"

void Devices_Init(void);

void Light_ON(void);
void Light_OFF(void);
void Heater_ON(void);
void Heater_OFF(void);
void Pump_ON(void);
void Pump_OFF(void);
void Feed_ON(void);
void Feed_OFF(void);
void Fan_ON(void);
void Fan_OFF(void);

void PWM_SetDuty(long unsigned int duty);



#endif
