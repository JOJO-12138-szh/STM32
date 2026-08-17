#include "stm32f10x.h"
#include "LED.h"
#include "SysTick.h"

int main()
{
    LED_Init();
    
    while(1)
    {
        LED_Mode1_Forward();
        //Delay_ms(800);
        
        LED_Mode2_Backward();
        //Delay_ms(800);
        
        LED_Mode3_Single();
        //Delay_ms(800);
    }
}


