#ifndef __CAR_H
#define __CAR_H

#include "stm32f10x.h"

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