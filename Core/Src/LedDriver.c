/*
 * LedDriver.c
 *
 *  Created on: 14 lut 2023
 *      Author: Michal Klebokowski
 */

#include "LedDriver.h"


//
//Private Functions
//

void Led_BlinkRoutine(LedDiode_t* Diode)
{
	uint32_t Tick = HAL_GetTick();
	if((Tick - Diode->LastTick) > Diode->BlinkDelay)
	{
		HAL_GPIO_TogglePin(Diode->LedGPIO, Diode->LedPin);
		Diode->LastTick = Tick;
	}

}

void Led_OnOff(LedDiode_t* Diode)
{
	HAL_GPIO_WritePin(Diode->LedGPIO, Diode->LedPin, Diode->LightStatus);
}

//
//Init Function
//
void Led_Init(LedDiode_t* Diode, GPIO_TypeDef* GPIOx, uint16_t Pin)
{
	Diode->LedGPIO = GPIOx;
	Diode->LedPin = Pin;
	Diode->LastTick = HAL_GetTick();
	Diode->LightStatus = DIODE_OFF;
	Diode->LastLightStatus = DIODE_OFF;
	Diode->BlinkStatus = DIODE_OFF;
	Diode->BlinkDelay = 1000;

}

//
//Main Loop Routine
//
void Led_Routine(LedDiode_t *Diode)
{
	if(Diode->BlinkStatus == DIODE_ON)
	{
		Led_BlinkRoutine(Diode);
	}
	else if(Diode->BlinkStatus == DIODE_OFF)
	{
		if(Diode->LightStatus != Diode->LastLightStatus)
		{
			Led_OnOff(Diode);
			Diode->LastLightStatus = Diode->LightStatus;
		}
	}
}


//
//Setting Status Functions
//


void Led_SetLightStatus(LedDiode_t* Diode, uint8_t Status)
{
	Diode->LightStatus = Status;
	Diode->BlinkStatus = DIODE_OFF;
}

void Led_SetBlinkStatus(LedDiode_t* Diode, uint8_t Status)
{
	Diode->BlinkStatus = Status;
}

void Led_SetBlinkDelay(LedDiode_t* Diode, uint32_t Delay)
{
	Diode->BlinkDelay = Delay;
}


