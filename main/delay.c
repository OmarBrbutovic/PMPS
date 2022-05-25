#include "delay.h"

void delay_ms(uint32_t ms)
{/// delay in ms (1,2^16);
 /// TIM4 runs on APB1 @ 42MHz with multiplier 2 which makes it 84MHz
 /// since it takes some time to setup timer the actual delay will be ms + const!
 /// function error < 0.3288%
 
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; 								// enable TIM4 
	TIM4->PSC = 0x0054 - 0x0001;										// set TIM4 counting prescaler to 42 (p406)
																		// 84MHz/84 = 1MHz -> count each 1us
	TIM4->ARR = 0x03E8;													// reload value set to 1000 us!
	TIM4->CR1 = 0x0084;													// ARPE On, CMS disable, Up counting
																		// UEV disable, TIM4 enable(p392)
	TIM4->CR2 = 0x0000;
	
	TIM4->EGR |= TIM_EGR_UG;											// update event, reload all config p363
	TIM4->CR1 |= TIM_CR1_CEN;											// start counter
	while(ms > 0)
	{
																		
		while((TIM4->SR & TIM_SR_UIF) == 0x0000);						// wait for update event
		
		TIM4->SR &= ~TIM_SR_UIF;										// clear the update event interrupt flag
		ms--;
	} 
	TIM4->CR1 &= ~TIM_CR1_CEN;											// stop counter 
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;								// disable TIM4 
}

void delay_us(uint32_t us)
{/// delay in us (1,2^16);
 /// TIM4 runs on APB1 @ 42MHz with multiplier 2 which makes it 84MHz
 /// since it takes some time to setup timer the actual delay will be us + const!
 /// error < 0.1004%
    
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; 								// enable TIM4 
	TIM4->PSC = 0x0001 - 0x0001;										// set TIM4 counting prescaler to 1 (p406)
																		// 84MHz/1 = 84MHz -> count each 1/84MHz
	TIM4->ARR = 0x0054;													// reload value set to 1 us!
	TIM4->CR1 = 0x0084;													// ARPE On, CMS disable, Up counting
																		// UEV disable, TIM4 enable(p392)
	TIM4->CR2 = 0x0000;
	
	TIM4->EGR |= TIM_EGR_UG;											// update event, reload all config p363
	TIM4->CR1 |= TIM_CR1_CEN;											// start counter
	while(us > 0)
	{
																		
		while((TIM4->SR & TIM_SR_UIF) == 0x0000);						// wait for update event
		
		TIM4->SR &= ~TIM_SR_UIF;										// clear the update event interrupt flag
		us--;
	} 
	TIM4->CR1 &= ~TIM_CR1_CEN;											// stop counter 
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;								// disable TIM4 
}
		
void delay_11ns(uint16_t ns)
{/// delay in us (1,2^16);
 /// TIM4 runs on APB1 @ 42MHz with multiplier 2 which makes it 84MHz
 /// since it takes some time to setup timer the actual delay will be us + const!
 /// error < 0.1004%
    
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; 								// enable TIM4 
	TIM4->PSC = 0x0001 - 0x0001;										// set TIM4 counting prescaler to 1 (p406)
																		// 84MHz/1 = 84MHz -> count each 1/84MHz
	TIM4->ARR = ns;														// reload value set to ns value!
	TIM4->CR1 = 0x0084;													// ARPE On, CMS disable, Up counting
																		// UEV disable, TIM4 enable(p392)
	TIM4->CR2 = 0x0000;
	
	TIM4->EGR |= TIM_EGR_UG;											// update event, reload all config p363
	TIM4->CR1 |= TIM_CR1_CEN;											// start counter
	
	while((TIM4->SR & TIM_SR_UIF) == 0x0000);							// wait for update event
		
	TIM4->SR &= ~TIM_SR_UIF;											// clear the update event interrupt flag
	
	TIM4->CR1 &= ~TIM_CR1_CEN;											// stop counter 
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;								// disable TIM4 
}	
				
void initStopwatch(void)
{/// setup and start TIM2 counter to measure elapsed time in us!
 /// TIM2 runs on APB1 @ 42MHz with multiplier 2 which makes it 84MHz
 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 								// enable TIM2 
	TIM2->PSC = 0x0054-0x0001;											// set TIM2 counting prescaler to 84 (p406)
																		// 84MHz/84 = 1MHz -> count each us
	TIM2->ARR = 0xFFFFFFFF;												// reload value set to 1.19304647083h!
	TIM2->CR1 = 0x0084;													// ARPE On, CMS disable, Up counting
																		// UEV disable, TIM2 enable(p392)
	TIM2->CR2 = 0x0000;
	TIM2->CNT = 0x00000000;												// clear the start value
	TIM2->EGR |= TIM_EGR_UG;											// update event, reload all config p363
	
	TIM2->CR1 |= TIM_CR1_CEN;											// start counting!
}

uint32_t stopStopwatch(void)
{/// stop TIM2 and return elapsed time!
	uint32_t _rval;
	
	TIM2->CR1 &= ~TIM_CR1_CEN;											// stop couting
	_rval = TIM2->CNT;
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;								// disable TIM2
	
	return _rval;
}


