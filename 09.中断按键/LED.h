#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"
#include "SysTick.h"

/* LED灯编号枚举 */
typedef enum
{ 
    LED1 = 1,
    LED2,
    LED3,
    LED4,
    LED5,
    LED6,
    LED7,
    LED8
}LED_No;

/* LED灯状态宏定义 */
#define LED_OFF     Bit_SET
#define LED_ON         Bit_RESET

void LED_Init(void);

void LED_1(void);

void LED_2(void);

void LED_3(void);

void LED_Running(void);  // 新增通用流水灯函数声明

void LED_Control(uint8_t LedNo, BitAction BitVal);

void LED_destroy(void);

void DisplayBinary(uint8_t value);






#endif /* __LED_H__ */