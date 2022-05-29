#ifndef __ADC_H
#define __ADC_H 
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

void initADC1(void);
uint16_t getADC(void);

#endif 
