/*
 * debounce.h
 *
 *  Created on: Feb 7, 2023
 *      Author: Michal Klebokowski
 */

#ifndef SRC_DEBOUNCE_DEBOUNCE_H_
#define SRC_DEBOUNCE_DEBOUNCE_H_

//add wait before repeat
//fix push and hold being always executed before repeat

#define PULL_DOWN	GPIO_PIN_SET
#define PULL_UP		GPIO_PIN_RESET

typedef enum
{
	IDLE = 0,
	DEBOUNCE,
	PRESSED,
	HOLD,
	REPEAT,
	RELEASE
}BUTTON_STATE;

typedef struct {
	BUTTON_STATE 	State;
	GPIO_TypeDef* 	ButtonGPIOx;
	uint16_t		PressedValue;
	uint16_t 		ButtonPin;
	uint32_t 		DebounceTime;
	uint32_t		HoldTime;
	uint32_t		RepeatTime;
	uint32_t		LastTick;
	void(*ButtonPressedFun)(void);
	void(*ButtonHoldFun)(void);
	void(*ButtonRepeatFun)(void);
	void(*ButtonReleaseFun)(void);


}Button_t;					//Button typedef, make var for every used button

//
//INIT AND LOOP TASK
//
void Debounce_ButtonInit(Button_t* Key, GPIO_TypeDef* GPIOx, uint16_t ButtonPin, uint16_t Pull, uint32_t DebounceTime, uint32_t HoldTime, uint32_t RepeatTime); //init button
void Debounce_ButtonTask (Button_t* Key);									//button task for using in main loop

//
//CALLBACK REGISTER FUNCTIONS
//
void Debounce_RegisterCallbackPress(Button_t* Button ,void (*Fun)(void));	//register callback function for normal press
void Debounce_RegisterCallbackHold(Button_t* Button ,void (*Fun)(void));	//... for long press
void Debounce_RegisterCallbackRepeat(Button_t* Button ,void (*Fun)(void));	//... for long press repeat
void Debounce_RegisterCallbackRelease(Button_t* Key ,void (*Fun)(void));	//... for releasing button




#endif /* SRC_DEBOUNCE_DEBOUNCE_H_ */
