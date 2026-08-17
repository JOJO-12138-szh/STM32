#include "stm32f10x.h"
#include "LED.h"
#include "key.h"
#include "SysTick.h"

int main(void)
{
    
    LED_Init();
    Key_EXTI_Init();  // 初始化外部中断按键
    
    while(1)
    {
        LED_Running();
    }
}