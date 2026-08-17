#ifndef __INFRARED_H
#define __INFRARED_H

#include "stm32f10x.h"


void IR_Init(void);

uint8_t IR_LeftDetect(void);
uint8_t IR_RightDetect(void);

#endif