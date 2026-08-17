#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"


void LED_Init(void);
void LED_Control(uint8_t led_num, uint8_t state);
void LED_Update(uint8_t key1, uint8_t key2, uint8_t key3, uint8_t key4);

#endif