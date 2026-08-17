#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"
#include "SysTick.h"

/* ────────────────── 宏定义：按键掩码 ────────────────── */
#define KEY1_MASK       0x01
#define KEY2_MASK       0x02
#define KEY3_MASK       0x04
#define KEY4_MASK       0x08

// 新增：流水灯方向标志，供LED.c、main.c调用
extern uint8_t Led_Dir_Flag;

/* ────────────────── 函数声明 ────────────────── */
void    Key_Init(void);             /* 普通扫描按键初始化 */
void    Key_EXTI_Init(void);        /* 新增：外部中断按键初始化 */
uint8_t Key_GetPressedMask(void);   /* 返回按键掩码，bit0~3 对应 KEY1~KEY4 */

#endif /* __KEY_H__ */