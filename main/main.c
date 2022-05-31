/*
PMPS-Automated-Hand-Sanitiser-Dispenser
Jasmina Piric
Omar Brbutovic

Connections:
PA2 - RX
PA3 - TX
PC5 - Water level sensor S
PD10 - Relay IN1
PD12 - HCSR-04 Trigger
PD13 - Echo
PE0 - LED Green
PE1 - LED Yellow
PE2 - LED Red

*/

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "delay.h"
#include "adc.h"
//#include "pwm.h"

/* Functions declarations */
void delay_ms_soft(uint32_t ms);
void Init();
void HCSR04();
void WaterLevel();
void isEmpty();


/* Variables */
volatile uint32_t counter;
uint32_t distance;

uint32_t adc_value;
uint32_t nivo;

uint8_t buttonState = 0;

// **************************************************************
int main(void)
{
	// Initialize all configured peripherals
	Init();

	printUSART2("-> System running... \n");
	while (1)
	{
		// ON/OFF toggle
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
		{
			printUSART2("Button pressed \n");
			buttonState = !buttonState;
			delay_ms_soft(100);
		}

		if (buttonState)
		{
			printUSART2("OFF \n");
			delay_ms_soft(1000);
		}
		else
		{
			HCSR04();
			WaterLevel();
		}
	}
}

// Function implementation **************************************************************
void delay_ms_soft(uint32_t ms)
{
	volatile uint32_t k = 10500 * ms;
	while (k--)
		;
}

void Init()
{
	// Reset of all peripherals, Initializes the Flash interface and the Systick.
	HAL_Init();
	initUSART2(921600);
	initADC1();
	// initSYSTIM();

	// initialize output PD12 Trigger HCSR-04
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	// initialize input PD13 Echo HCSR-04
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	// initialize output PD10 Relay
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	// initialize output for adc LED E0,E1,E2,E3
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	// push button on PA0
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void HCSR04()
{
	counter = 0;

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0x01);
	delay_us(10);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0x00);

	while (!HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13))
		;

	while (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13))
	{
		counter++;
	}

	distance = counter / 470;

	delay_ms(100);
	printUSART2("-> Distance [%d]  \n", distance);


	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 1);
}

void WaterLevel()
{
	adc_value = getADC();
	nivo = (adc_value * 3000) / 4095;
	printUSART2("-> ADC: Value V[%d]\n", nivo);

	if (nivo >= 2000)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 0x01);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, 0x00);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, 0x00);
		printUSART2("Green \n");
	}
	if (nivo < 1900 && nivo >= 1000)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 0x00);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, 0x01);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, 0x00);
		printUSART2("Yellow \n");
	}
	if (nivo < 900)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 0x00);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, 0x00);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, 0x01);
		printUSART2("RED \n");
		isEmpty();
	}
}

void isEmpty()
{
	while (nivo <= 300)
	{
		printUSART2("Do nothing is empty \n");
		delay_ms_soft(100);
		WaterLevel();
	}
}


