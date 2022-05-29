#ifndef __USART2_H_
#define __USART2_H_

#include <stdio.h>
#include <stdarg.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "misc.h"


#define USART_9600					0x00001117
#define USART_115200				0x0000016C


void initUSART2(uint32_t baudrate);
void putcharUSART2(uint8_t data);
void printUSART2(char * str, ... );
void sprintUSART2(uint8_t * str);

#endif 
