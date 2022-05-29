#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"

 
#define SYSTIM_KEEP_ALIVE			0
#define SYSTIM_TIMEOUT				1
void 		delay_ms(uint32_t ms);															
void 		delay_us(uint32_t ms);				

void initSYSTIM(void);
void deinitSYSTIM(void);
uint32_t getSYSTIM(void);
uint8_t chk4TimeoutSYSTIM(uint32_t btime, uint32_t period);

#endif 
