#include "stm32f10x.h"
#include "Car.h"
#include "usart.h"

int main(void)
{
    // NVIC分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // 初始化小车
    Car_Init();

    // 初始化USART3(PB10 PB11)
    Usart3_Init(9600);

    // 默认停止
    Car_Stop();

    while(1)
    {

    }
}