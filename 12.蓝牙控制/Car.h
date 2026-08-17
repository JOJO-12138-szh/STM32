#ifndef __CAR_H
#define __CAR_H

#include "stm32f10x.h"


// 小车端口
#define CAR_RCC     RCC_APB2Periph_GPIOA
#define CAR_PORT    GPIOA


#define CAR_A1_PIN GPIO_Pin_0   // 左上后
#define CAR_A2_PIN GPIO_Pin_1   // 左上前

#define CAR_B1_PIN GPIO_Pin_2   // 右上后
#define CAR_B2_PIN GPIO_Pin_3   // 右上前

#define CAR_C1_PIN GPIO_Pin_4   // 左下后
#define CAR_C2_PIN GPIO_Pin_5   // 左下前

#define CAR_D1_PIN GPIO_Pin_6   // 右下后
#define CAR_D2_PIN GPIO_Pin_7   // 右下前


#define CAR_ALL_PIN 0x00FF



void Car_Init(void);

void Car_Stop(void);

void Car_GoStraight(void);

void Car_GoBack(void);

void Car_LeftMove(void);

void Car_RightMove(void);

void Car_TurnLeft(void);

void Car_TurnRight(void);

void Car_ForwardLeft(void);

void Car_ForwardRight(void);



void Car_BackwardLeft(void);

void Car_BackwardRight(void);

void Car_PivotFrontLeft(void);

void Car_PivotFrontRight(void);

void Car_PivotRearLeft(void);

void Car_PivotRearRight(void);


#endif