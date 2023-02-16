/*
 * debounce.c
 *
 *  Created on: Feb 7, 2023
 *      Author: Michal Klebokowski
 */
#include "stm32f4xx_hal.h"
#include "debounce.h"
#include "main.h"

//
//INIT FUNCTION
//

void Debounce_ButtonInit(Button_t* Key, GPIO_TypeDef* GPIOx, uint16_t ButtonPin, uint16_t Pull, uint32_t DebounceTime, uint32_t HoldTime, uint32_t RepeatTime)
{
	Key->State = IDLE;
	Key->ButtonGPIOx = GPIOx;
	Key->ButtonPin = ButtonPin;
	Key->PressedValue = Pull;
	Key->DebounceTime = DebounceTime;
	Key->HoldTime = HoldTime;
	Key->RepeatTime = RepeatTime;
}

//
//CALLBACKS REGISTER FUNCTIONS
//

void Debounce_RegisterCallbackPress(Button_t* Key ,void (*Fun)(void))		//Register callback funciotn for pressed button
{
	Key->ButtonPressedFun = Fun;
}

void Debounce_RegisterCallbackHold(Button_t* Key ,void (*Fun)(void))		//Register callback funciotn for hold button
{
	Key->ButtonHoldFun = Fun;
}

void Debounce_RegisterCallbackRepeat(Button_t* Key ,void (*Fun)(void))		//Register callback funciotn for long pressed button
{
	Key->ButtonRepeatFun = Fun;
}

void Debounce_RegisterCallbackRelease(Button_t* Key ,void (*Fun)(void))		//Register callback funciotn for released button
{
	Key->ButtonReleaseFun = Fun;
}


//
//STATE MACHINE ROUTINES
//
void ButtonIdleRoutine (Button_t* Key)
{
	if(Key->PressedValue == HAL_GPIO_ReadPin(Key->ButtonGPIOx, Key->ButtonPin)) //check button
	{
		Key->LastTick = HAL_GetTick();											//save tick
		Key->State = DEBOUNCE;
	}
}

void ButtonDebounceRoutine (Button_t* Key)
{
	if((HAL_GetTick() - Key->LastTick) > Key->DebounceTime)						//if debounce time has passed
	{
		if(Key->PressedValue == HAL_GPIO_ReadPin(Key->ButtonGPIOx, Key->ButtonPin))	//check if button is still pressed
		{
			Key->State = PRESSED;												//if it is, then is pressed
			if(Key->ButtonPressedFun != NULL)									//execute callback function
			{
				Key->ButtonPressedFun();
			}
		}
		else																//go to idle if it was bouncing
		{
			Key->State = RELEASE;
		}
	}
}

void ButtonPressedRoutine (Button_t* Key)
{
	if(Key->PressedValue != HAL_GPIO_ReadPin(Key->ButtonGPIOx, Key->ButtonPin))
	{

		Key->State = RELEASE;
	}
	else
	{
		Key->LastTick = HAL_GetTick();
		Key->State = HOLD;
	}
}

void ButtonHoldRoutine (Button_t* Key)
{
	if(Key->PressedValue == HAL_GPIO_ReadPin(Key->ButtonGPIOx, Key->ButtonPin))
	{
		if((HAL_GetTick() - Key->LastTick) > Key->HoldTime)
		{
			if(Key->ButtonHoldFun != NULL)
			{
				Key->ButtonHoldFun();
				Key->LastTick = HAL_GetTick();
			}

			Key->State = REPEAT;
			Key->LastTick = HAL_GetTick();
		}
	}
	else
	{
		Key->State = RELEASE;
	}
}

void ButtonRepeatRoutine (Button_t* Key)
{
	if(Key->PressedValue == HAL_GPIO_ReadPin(Key->ButtonGPIOx, Key->ButtonPin))
	{
		if((HAL_GetTick() - Key->LastTick) > Key->RepeatTime)
		{
			if(Key->ButtonRepeatFun != NULL)
			{
				Key->ButtonRepeatFun();
				Key->LastTick = HAL_GetTick();
			}
		}
	}
	else
	{
		Key->State = RELEASE;
	}
}

void ButtonReleaseRoutine (Button_t* Key)
{
	if(Key->ButtonReleaseFun != NULL)
	{
		Key->ButtonReleaseFun();
	}
	Key->State = IDLE;

}


//
//STATE MACHINE FOR BUTTONS - TO USE IN MAIN LOOP
//

void Debounce_ButtonTask (Button_t* Key)
{
	switch(Key->State)
	{
	case IDLE:
		ButtonIdleRoutine(Key);
		break;

	case DEBOUNCE:
		ButtonDebounceRoutine(Key);
		break;

	case PRESSED:
		ButtonPressedRoutine(Key);
		break;

	case HOLD:
		ButtonHoldRoutine(Key);
		break;

	case REPEAT:
		ButtonRepeatRoutine(Key);
		break;

	case RELEASE:
		ButtonReleaseRoutine(Key);
		break;
	}
}
