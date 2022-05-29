#include "delay.h"

TIM_HandleTypeDef TIM_HandleStruct;
TIM_HandleTypeDef TIM2_HandleStruct;

void delay_ms(uint32_t ms)
{/// delay in ms (1,2^16);
 /// TIM4 runs on APB1 @ 42MHz with multiplier 2 which makes it 84MHz
 /// since it takes some time to setup timer the actual delay will be ms + const!
 /// function error < 0.3288%
 
	__HAL_RCC_TIM4_CLK_ENABLE();

	TIM_Base_InitTypeDef TIM_Base_InitStruct;
	TIM_Base_InitStruct.Prescaler = 0x0054 - 0x001;
	TIM_Base_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct.Period = 0x03E8;
	TIM_Base_InitStruct.ClockDivision =	TIM_CLOCKDIVISION_DIV1;

	TIM_HandleStruct.Instance = TIM4;
	TIM_HandleStruct.Init = TIM_Base_InitStruct;

	HAL_TIM_Base_Init(&TIM_HandleStruct);
	HAL_TIM_Base_Start(&TIM_HandleStruct);
	while(ms > 0)
	{
		while(__HAL_TIM_GET_FLAG(&TIM_HandleStruct,TIM_FLAG_UPDATE) == 0x0000);
		__HAL_TIM_CLEAR_FLAG(&TIM_HandleStruct,TIM_FLAG_UPDATE);
		ms--;
	} 
	HAL_TIM_Base_Stop(&TIM_HandleStruct);
	__HAL_RCC_TIM4_CLK_DISABLE();
}

void delay_us(uint32_t us)
{/// delay in us (1,2^16);
 /// TIM4 runs on APB1 @ 42MHz with multiplier 2 which makes it 84MHz
 /// since it takes some time to setup timer the actual delay will be us + const!
 /// error < 0.1004%
    
	__HAL_RCC_TIM4_CLK_ENABLE();

	TIM_Base_InitTypeDef TIM_Base_InitStruct;
	TIM_Base_InitStruct.Prescaler = 0x0001 - 0x001;
	TIM_Base_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct.Period = 0x0054;
	TIM_Base_InitStruct.ClockDivision =	TIM_CLOCKDIVISION_DIV1;

	TIM_HandleStruct.Instance = TIM4;
	TIM_HandleStruct.Init = TIM_Base_InitStruct;

	HAL_TIM_Base_Init(&TIM_HandleStruct);
	HAL_TIM_Base_Start(&TIM_HandleStruct);

	while(us > 0)
	{
		while(__HAL_TIM_GET_FLAG(&TIM_HandleStruct,TIM_FLAG_UPDATE) == 0x0000);
		__HAL_TIM_CLEAR_FLAG(&TIM_HandleStruct,TIM_FLAG_UPDATE);
		us--;
	} 

	HAL_TIM_Base_Stop(&TIM_HandleStruct);
	__HAL_RCC_TIM4_CLK_DISABLE();
}
		
void initSYSTIM(void)
{
	__HAL_RCC_TIM2_CLK_ENABLE();

	TIM_Base_InitTypeDef TIM_Base_InitStruct;
	TIM_Base_InitStruct.Prescaler = 42000 - 0x001;							//84 Mhz
	TIM_Base_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct.Period = 0xFFFFFFFF;
	TIM_Base_InitStruct.ClockDivision =	TIM_CLOCKDIVISION_DIV1;

	TIM2_HandleStruct.Instance = TIM2;
	TIM2_HandleStruct.Init = TIM_Base_InitStruct;

	HAL_TIM_Base_Init(&TIM2_HandleStruct);
	HAL_TIM_Base_Start(&TIM2_HandleStruct);
}

void deinitSYSTIM(void)
{
	HAL_TIM_Base_Stop(&TIM_HandleStruct);
	__HAL_RCC_TIM4_CLK_DISABLE();
}

uint32_t getSYSTIM(void)
{
	// value in ms
	// return  (TIM2->CNT)/2;
	return  __HAL_TIM_GET_COUNTER(&TIM2_HandleStruct)/2;
}

uint8_t chk4TimeoutSYSTIM(uint32_t btime, uint32_t period)
{
	uint32_t time = __HAL_TIM_GET_COUNTER(&TIM2_HandleStruct)/2;
	if(time >= btime)
	{
		if((time - btime) >= period)
			return (SYSTIM_TIMEOUT);
		else
			return (SYSTIM_KEEP_ALIVE);
	}
	else
	{
		uint32_t utmp32 = 0xFFFFFFFF - btime;
		if((time + utmp32) >= period)
			return (SYSTIM_TIMEOUT);
		else
			return (SYSTIM_KEEP_ALIVE);
	}
}


