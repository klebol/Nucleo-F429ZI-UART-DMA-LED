/*
 * LedDriver.h
 *
 *  Created on: 14 lut 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_LEDDRIVER_H_
#define INC_LEDDRIVER_H_

#define DIODE_ON 1
#define DIODE_OFF 0

#include "main.h"

typedef struct{
	uint8_t BlinkStatus;
	uint8_t LastLightStatus;
	uint8_t LightStatus;
	uint32_t BlinkDelay;
	uint32_t LastTick;
	GPIO_TypeDef* LedGPIO;
	uint16_t LedPin;
}LedDiode_t;



void Led_Init(LedDiode_t* Diode, GPIO_TypeDef* GPIOx, uint16_t Pin);
void Led_Routine(LedDiode_t *Diode);
void Led_SetLightStatus(LedDiode_t* Diode, uint8_t Status);
void Led_SetBlinkStatus(LedDiode_t* Diode, uint8_t Status);
void Led_SetBlinkDelay(LedDiode_t* Diode, uint32_t Delay);
#endif /* INC_LEDDRIVER_H_ */
