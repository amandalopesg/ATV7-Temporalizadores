/*
 * hw.c
 *
 *  Created on: May 13, 2021
 *      Author: vjqju
 */

#include "main.h"
#include <stdint.h>
#include <stdbool.h>
#include "app.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

void HAL_GPIO_EXIT_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		app_switch_interrupt();
	}
}

bool hw_switch_state_get(void)
{
	GPIO_PinState switch_state = HAL_GPIO_ReadPin(USER_SW_GPIO_Port, USER_SW_Pin);

	if(switch_state == GPIO_PIN_SET)
		return true;
	else
		return false;
}

void hw_led_toggle()
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}

void hw_led_state_set(bool state)
{
	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;

	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin,led_state);

}

void hw_delay_ms(uint32_t time_ms)
{
	HAL_Delay(time_ms);

}

void hw_cpu_sleep(void)
{
	__WFI();
}

void hw_timer_start(void)
{
	uint16_t led_time = 250;

	if(led_time == 250)
		{
			__HAL_TIM_SET_AUTORELOAD(&htim1, 249);
			__HAL_TIM_SET_COUNTER(&htim1, 0);
			led_time = 500;
			return;
		}
		if(led_time == 500)
		{
			__HAL_TIM_SET_AUTORELOAD(&htim2, 499);
			__HAL_TIM_SET_COUNTER(&htim2, 0);
			led_time = 250;
			return;
		}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim1)
	{
		hw_led_toggle();
	}
	if(htim == &htim2)
	{
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		HAL_TIM_Base_Stop_IT(&htim2);

		hw_timer_start();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		HAL_TIM_Base_Start_IT(&htim2);
	}
}
