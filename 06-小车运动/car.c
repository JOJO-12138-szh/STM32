#include "Car.h"

// 小车端口
#define CAR_RCC RCC_APB2Periph_GPIOA
#define CAR_PORT GPIOA

#define CAR_A1_PIN GPIO_Pin_0 // 左上后
#define CAR_A2_PIN GPIO_Pin_1 // 左上前

#define CAR_B1_PIN GPIO_Pin_2 // 右上后
#define CAR_B2_PIN GPIO_Pin_3 // 右上前

#define CAR_C1_PIN GPIO_Pin_4 // 左下后
#define CAR_C2_PIN GPIO_Pin_5 // 左下前

#define CAR_D1_PIN GPIO_Pin_6 // 右下后
#define CAR_D2_PIN GPIO_Pin_7 // 右下前

#define CAR_ALL_PIN 0x00FF

/**
 * 初始化
 * Car_Init
 *
 *
 */
void Car_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(CAR_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode =
		GPIO_Mode_Out_PP;

	GPIO_InitStructure.GPIO_Pin =
		CAR_ALL_PIN;

	GPIO_InitStructure.GPIO_Speed =
		GPIO_Speed_50MHz;

	GPIO_Init(CAR_PORT, &GPIO_InitStructure);

	// 默认停止
	GPIO_SetBits(CAR_PORT, CAR_ALL_PIN);
}

/*
停止
*/
void Car_Stop(void)
{

	GPIO_SetBits(GPIOA, 0x00FF);
}

/*
前进

a2 b2 c2 d2

PA1 PA3 PA5 PA7
*/
void Car_GoStraight(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_1 |
					   GPIO_Pin_3 |
					   GPIO_Pin_5 |
					   GPIO_Pin_7);
}

/*
后退

a1 b1 c1 d1

PA0 PA2 PA4 PA6
*/
void Car_GoBack(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_0 |
					   GPIO_Pin_2 |
					   GPIO_Pin_4 |
					   GPIO_Pin_6);
}

/*
左平移

a1 b2 c2 d1

PA0 PA3 PA5 PA6
*/
void Car_LeftMove(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_0 |
					   GPIO_Pin_3 |
					   GPIO_Pin_5 |
					   GPIO_Pin_6);
}

/*
右平移

a2 b1 c1 d2

PA1 PA2 PA4 PA7
*/
void Car_RightMove(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_1 |
					   GPIO_Pin_2 |
					   GPIO_Pin_4 |
					   GPIO_Pin_7);
}

/*
原地左转

左轮后退
右轮前进


a1 b2 c1 d2

PA0 PA3 PA4 PA7
*/
void Car_TurnLeft(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_0 |
					   GPIO_Pin_3 |
					   GPIO_Pin_4 |
					   GPIO_Pin_7);
}

/*
原地右转

a2 b1 c2 d1

PA1 PA2 PA5 PA6
*/
void Car_TurnRight(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_1 |
					   GPIO_Pin_2 |
					   GPIO_Pin_5 |
					   GPIO_Pin_6);
}

/*
左前移

左前方向
右前方向

a2 b2

PA1 PA3
*/
void Car_ForwardLeft(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_1 |
					   GPIO_Pin_3);
}

/*
右前移


b2 d2

PA3 PA7
*/
void Car_ForwardRight(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_3 |
					   GPIO_Pin_7);
}

/*
左后移


a1 c1

PA0 PA4

*/
void Car_BackwardLeft(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_0 |
					   GPIO_Pin_4);
}

/*
右后移


b1 d1

PA2 PA6

*/
void Car_BackwardRight(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_2 |
					   GPIO_Pin_6);
}

/*
绕前轴中心左转


前轮停止
后轮旋转


c1 d2

*/
void Car_PivotFrontLeft(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_4 |
					   GPIO_Pin_7);
}

/*
绕前轴中心右转


c2 d1

*/
void Car_PivotFrontRight(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_5 |
					   GPIO_Pin_6);
}

/*
绕后轴中心左转


前轮旋转


a1 b2

*/
void Car_PivotRearLeft(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_0 |
					   GPIO_Pin_3);
}

/*
绕后轴中心右转


a2 b1

*/
void Car_PivotRearRight(void)
{

	Car_Stop();

	GPIO_ResetBits(GPIOA,
				   GPIO_Pin_1 |
					   GPIO_Pin_2);
}