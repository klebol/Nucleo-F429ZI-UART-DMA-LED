/*
 * command_parser.h
 *
 *  Created on: Feb 10, 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_

#include "string.h"
#include "stdlib.h"
#include "main.h"
#include "LedDriver.h"
#include "RingBuffer.h"
#include "usart.h"

extern LedDiode_t Led1;	//added main global variables leds for visibility, quick solution but there are better ones
extern LedDiode_t Led2;
extern LedDiode_t Led3;


#define ENDLINE '\n'

typedef struct{
	uint32_t D1freq;
	uint32_t D2freq;
	uint32_t D3freq;
}DiodeBlinkFreq;

void Parser_TakeLine(RBuffer_t *RBuff, uint8_t *Destination);
void Parser_Parse(uint8_t* Command);

void Parser_LedBlinkRoutine(void);

#endif /* INC_COMMAND_PARSER_H_ */
