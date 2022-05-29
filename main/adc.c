#include "adc.h"

ADC_HandleTypeDef hadc1;

void initADC1(void)
{
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	// ADC PC5 -> ADC123_IN15 
	//------------------------------------------------------------------ 
	
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	// RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 								
	// RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 									
	// GPIOA->MODER |= GPIO_MODER_MODER1;  								
	// GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1; 								
	

	ADC_ChannelConfTypeDef sConfig = {0};



	__HAL_RCC_ADC1_CLK_ENABLE();
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	sConfig.Channel = ADC_CHANNEL_15;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}

uint16_t getADC(void)
{
	HAL_ADC_Start (&hadc1);
	while(HAL_ADC_PollForConversion(&hadc1,10000) != HAL_OK);
	// HAL_ADC_PollForConversion(&hadc1,10000);

	return HAL_ADC_GetValue(&hadc1);
}
