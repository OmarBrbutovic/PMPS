#include "pwm.h"


TIM_HandleTypeDef TIM4_HandleStruct;
void initPWM(void)
{
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Initialize pin
	//-------------------------------------------------------------------------------
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Configure timer
	//-------------------------------------------------------------------------------
	__HAL_RCC_TIM4_CLK_ENABLE();

	TIM_Base_InitTypeDef TIM_Base_InitStruct;
	TIM_Base_InitStruct.Prescaler = 0x0054 - 0x001;
	TIM_Base_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct.Period = 0x03E8;
	TIM_Base_InitStruct.ClockDivision =	TIM_CLOCKDIVISION_DIV1;
	TIM_Base_InitStruct.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	TIM4_HandleStruct.Instance = TIM4;
	TIM4_HandleStruct.Init = TIM_Base_InitStruct;

	HAL_TIM_PWM_Init(&TIM4_HandleStruct);

	TIM_OC_InitTypeDef TIM_OC_InitStruct;
	TIM_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
	TIM_OC_InitStruct.Pulse = 500;
	TIM_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OC_InitStruct.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_2);
	HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_3);
	HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&TIM4_HandleStruct,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM4_HandleStruct,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&TIM4_HandleStruct,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&TIM4_HandleStruct,TIM_CHANNEL_4);


}
void setPWM(uint32_t ccr1,uint32_t ccr2,uint32_t ccr3,uint32_t ccr4)
{
	// TIM_OC_InitTypeDef TIM_OC_InitStruct;
	// TIM_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
	// TIM_OC_InitStruct.Pulse = ccr1;
	// TIM_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	// HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);
	// HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_2);
	// HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_3);
	// HAL_TIM_PWM_ConfigChannel(&TIM4_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_4);

	// TIM4->CCR1 = ccr1;
	// TIM4->CCR2 = ccr2;
	// TIM4->CCR3 = ccr3; 
	// TIM4->CCR4 = ccr4;
	__HAL_TIM_SET_COMPARE(&TIM4_HandleStruct,TIM_CHANNEL_1,ccr1);
	__HAL_TIM_SET_COMPARE(&TIM4_HandleStruct,TIM_CHANNEL_2,ccr2);
	__HAL_TIM_SET_COMPARE(&TIM4_HandleStruct,TIM_CHANNEL_3,ccr3);
	__HAL_TIM_SET_COMPARE(&TIM4_HandleStruct,TIM_CHANNEL_4,ccr4);
	// HAL_TIM_PWM_Start(&TIM4_HandleStruct,TIM_CHANNEL_1);
	// HAL_TIM_PWM_Start(&TIM4_HandleStruct,TIM_CHANNEL_2);
	// HAL_TIM_PWM_Start(&TIM4_HandleStruct,TIM_CHANNEL_3);
	// HAL_TIM_PWM_Start(&TIM4_HandleStruct,TIM_CHANNEL_4);


}


