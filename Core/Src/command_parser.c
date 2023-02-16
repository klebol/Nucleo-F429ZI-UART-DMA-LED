/*
 * command_parser.c
 *
 *  Created on: Feb 10, 2023
 *      Author: Michal Klebokowski
 */

#include "command_parser.h"

uint32_t LD1_Freq = 1000;
uint32_t LD2_Freq = 1000;
uint32_t LD3_Freq = 1000;
uint8_t BlinkActive = 0xFF;



void Parser_TakeLine(RBuffer_t *RBuff, uint8_t *Destination)		//Returns command to variable taken from buffer
{
	uint8_t i = 0;
	uint8_t OneSign;
	do
	{
		RBuffer_Read(RBuff, &OneSign);
		if(OneSign == ENDLINE)
		{
			Destination[i] = 0;
		}
		else
		{
			Destination[i] = OneSign;
		}
		i++;
	}while(ENDLINE != OneSign);
}

//void Parser_ParseLED(void)
//{
//	char* ParsePointer = strtok(NULL,",");
//	if(strlen(ParsePointer) > 0)
//	{
//
//
//		switch(ParsePointer[0])
//		{
//		case '1':
//			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
//			break;
//
//		case '2':
//			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
//			break;
//
//		case '3':
//			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
//			break;
//		default:
//			HAL_UART_Transmit_IT(&huart3,(uint8_t*) "Invalid Number\n\r", sizeof("Invalid Number\n\r"));
//			break;
//		}
//	}
//}




void Parser_ParseLedToggle(uint8_t onoff)
{
	char* ParsePointer = strtok(NULL,",");		//look for "," token (place \0 instead, return pointer to separated parameter)

	if(NULL == ParsePointer)					//if returned pointer is NULL, return (end of string, no parameters)
	{
		return;
	}

	if(strcmp("1", ParsePointer) == 0)
	{
		Led_SetLightStatus(&Led1,onoff);
	}
	else if(strcmp("2", ParsePointer) == 0)
	{
		Led_SetLightStatus(&Led2,onoff);
	}
	else if(strcmp("3", ParsePointer) == 0)
	{
		Led_SetLightStatus(&Led3,onoff);
	}

	Parser_ParseLedToggle(onoff);
}

void Parser_BlinkSpeed(uint8_t LedNumber)
{
	char* ParsePointer = strtok(NULL,",");
	uint8_t Speed = atoi(ParsePointer);

	switch(LedNumber)
	{
	case 1:
		Led_SetBlinkDelay(&Led1, Speed);
		Led_SetBlinkStatus(&Led1, DIODE_ON);
		break;

	case 2:
		Led_SetBlinkDelay(&Led2, Speed);
		Led_SetBlinkStatus(&Led2, DIODE_ON);
		break;

	case 3:
		Led_SetBlinkDelay(&Led3, Speed);
		Led_SetBlinkStatus(&Led3, DIODE_ON);
		break;
	default:
		break;
	}



}

void Parser_ParseBlink()
{
	char* ParsePointer = strtok(NULL,",");
	if(strcmp("1", ParsePointer) == 0)
	{
		Parser_BlinkSpeed(1);
	}
	else if(strcmp("2", ParsePointer) == 0)
	{
		Parser_BlinkSpeed(2);
	}
	else if(strcmp("3", ParsePointer) == 0)
	{
		Parser_BlinkSpeed(3);
	}
}


void Parser_Parse(uint8_t* Command)					//look for commands, if proper command is found go to separate funcion to parse the paremeters
{
	char* ParsePointer = strtok((char*)Command,"=");

	if(strcmp("LEDON", ParsePointer) == 0)
	{
		Parser_ParseLedToggle(1);
	}
	else if(strcmp("LEDOFF", ParsePointer) == 0)
	{
		Parser_ParseLedToggle(0);
	}
	else if(strcmp("LEDBLINK", ParsePointer) == 0)
	{
		Parser_ParseBlink();
	}


}

//void Parser_LedBlinkRoutine(void)
//{
//	static uint8_t Init = 0;
//	static uint32_t LastTick1, LastTick2, LastTick3;
//	uint32_t ActualTick = HAL_GetTick();
//
//	if(Init == 0)
//	{
//		LastTick1 = HAL_GetTick();
//		LastTick2 = LastTick1;
//		LastTick3 = LastTick1;
//		Init = 1;
//	}
//
//	if( ((ActualTick - LastTick1) > LD1_Freq) && (BlinkActive & (1<<1)))
//	{
//		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
//		LastTick1 = ActualTick;
//	}
//	if( ((ActualTick - LastTick2) > LD2_Freq) && (BlinkActive & (1<<2)))
//	{
//		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
//		LastTick2 = ActualTick;
//	}
//	if( ((ActualTick - LastTick3) > LD3_Freq) && (BlinkActive & (1<<3)))
//	{
//		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
//		LastTick3 = ActualTick;
//	}
//}



//	if(0 == strcmp("LED_ON",(char*)Command))
//	{
//		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
//	}
//	else if(0 == strcmp("LED_OFF",(char*)Command))
//	{
//		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
//	}
//}
