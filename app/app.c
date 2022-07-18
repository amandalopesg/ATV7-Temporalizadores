/* 
autora: Amanda Lopes Gonçalves
data: 17/07/2022

 
 */
#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "hw.h"

#define APP_DEBOUNCING_TIME_MS 50

volatile uint32_t led_time_ms = 100;
bool app_started = false;

void app_switch_interrupt(void)
{
	static uint32_t debouncing_time_ms = 0;

	if(!app_started)
		return;

	if((hw_tick_ms_get() - debouncing_time_ms) >= APP_DEBOUNCING_TIME_MS)
	{
		debouncing_time_ms = hw_tick_ms_get();
	}
}

void app_tick_1ms(void)
{
	if(!app_started)
		return;
}

void app_init(void)
{
	hw_timer_start();
	app_started = true;
}

void app_loop(void)
{
	hw_cpu_sleep();
}
