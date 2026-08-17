#include "stm32f10x.h"
#include "SysTick.h"


#include "LED.h"
#include "Timer.h"

// 计时
static uint8_t TIM_CNT=0;

// 计时器
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		// 写你的实现逻辑
		TIM_CNT++;
		
		// 亮灯
		LED_Control(TIM_CNT,LED_ON);
		
		// 重置·
		if(TIM_CNT == 9)
		{
			TIM_CNT=0;
			LED_destroy();
		}
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

int main(void)
{
	
	LED_Init();
	
	Timer_Init();
	
	while(1)
	{
		
	}
    

	
		
}