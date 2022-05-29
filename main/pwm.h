#ifndef __PWM_H 
#define __PWM_H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"


void initPWM(void);
void setPWM(uint32_t ccr1,uint32_t ccr2,uint32_t ccr3,uint32_t ccr4);

#endif /* ifndef  */
