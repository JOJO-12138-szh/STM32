#include "Car.h"



void Car_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;


	RCC_APB2PeriphClockCmd(CAR_RCC,ENABLE);



	GPIO_InitStructure.GPIO_Mode =
	GPIO_Mode_Out_PP;


	GPIO_InitStructure.GPIO_Pin =
	CAR_ALL_PIN;


	GPIO_InitStructure.GPIO_Speed =
	GPIO_Speed_50MHz;


	GPIO_Init(CAR_PORT,&GPIO_InitStructure);



	// 默认停止
	GPIO_SetBits(CAR_PORT,CAR_ALL_PIN);

}




/*
停止
*/
void Car_Stop(void)
{

	GPIO_SetBits(GPIOA,0x00FF);

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
	GPIO_Pin_1|
	GPIO_Pin_3|
	GPIO_Pin_5|
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
	GPIO_Pin_0|
	GPIO_Pin_2|
	GPIO_Pin_4|
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
	GPIO_Pin_0|
	GPIO_Pin_3|
	GPIO_Pin_5|
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
	GPIO_Pin_1|
	GPIO_Pin_2|
	GPIO_Pin_4|
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
	GPIO_Pin_0|
	GPIO_Pin_3|
	GPIO_Pin_4|
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
	GPIO_Pin_1|
	GPIO_Pin_2|
	GPIO_Pin_5|
	GPIO_Pin_6);

}





/*
左前

左前：不转
右前：正转
左后：正转
右后：不转
*/
void Car_ForwardLeft(void)
{
    Car_Stop();

    GPIO_ResetBits(GPIOA,
        GPIO_Pin_3 |
        GPIO_Pin_5);
}




/*
右前

左前：正转
右前：不转
左后：不转
右后：正转
*/
void Car_ForwardRight(void)
{
    Car_Stop();

    GPIO_ResetBits(GPIOA,
        GPIO_Pin_1 |
        GPIO_Pin_7);
}




/*
左后

左前：反转
右前：不转
左后：不转
右后：反转
*/
void Car_BackwardLeft(void)
{
    Car_Stop();

    GPIO_ResetBits(GPIOA,
        GPIO_Pin_0 |
        GPIO_Pin_6);
}


/*
右后

左前：不转
右前：反转
左后：反转
右后：不转
*/
void Car_BackwardRight(void)
{
    Car_Stop();

    GPIO_ResetBits(GPIOA,
        GPIO_Pin_2 |
        GPIO_Pin_4);
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
	GPIO_Pin_4|
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
	GPIO_Pin_5|
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
	GPIO_Pin_0|
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
	GPIO_Pin_1|
	GPIO_Pin_2);

}