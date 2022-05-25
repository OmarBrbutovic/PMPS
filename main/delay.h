#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

 
void 		delay_ms(uint32_t ms);															
void 		delay_us(uint32_t ms);				
void 		delay_11ns(uint16_t ns);			

void 		initStopwatch(void);										// call this function to start time measurement
uint32_t	stopStopwatch(void);										// call this function to stop time measurement and 
																		// to receive elapsed time

#endif 
