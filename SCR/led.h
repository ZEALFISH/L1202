#ifndef __LED_H__
#define __LED_H__

#define LED_ON 0
#define LED_OFF 1

#define WORK_LED_Pin	PB3
#define POWER_LED_Pin	PB6

#define SetWorkLedOn()				WORKS_LED_Pin = LED_ON
#define SetWorkLedOff()				WORKS_LED_Pin = LED_OFF

#define SetPowerLedOn()				POWER_PED_Pin = LED_ON
#define SetPowerLedOff()			POWER_PED_Pin = LED_OFF



#endif
