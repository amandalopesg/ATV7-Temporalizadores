/* 
autora: Amanda Lopes Gonçalves
data: 17/07/2022

 
 */

#ifndef HW_H_
#define HW_H_
#include <stdbool.h>

bool hw_switch_state_get(void);
void hw_led_state_set(bool state);
void hw_delay_ms(uint32_t time_ms);
void hw_led_toggle(void);
void hw_cpu_sleep(void);
uint32_t hw_tick_ms_get(void);
void hw_timer_start(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif /* HW_H_ */
