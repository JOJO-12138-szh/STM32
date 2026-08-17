#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h" 


void LED_Init(void);
void LED_Control(uint8_t LedNo, BitAction BitVal);
void LED_Mode1_Forward(void);
void LED_Mode2_Backward(void);
void LED_Mode3_Single(void);

#endif /* __LED_H__ */
