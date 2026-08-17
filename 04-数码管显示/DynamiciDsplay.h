#ifndef _DynamiciDsplay_H_
#define _DynamiciDsplay_H_

#include <stdint.h>

// 初始化函数
void DynamiciDsplay_Init(void);

// 设置位置以及显示的数字
void DynamiciDsplay_SetDigit(uint8_t pos, uint8_t digit);  // pos:0~7, digit:0~9

// 动态刷新
void DynamiciDsplay_Refresh(void);                        

#endif
