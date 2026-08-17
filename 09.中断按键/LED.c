#include "LED.h"
#include "SysTick.h"
#include "key.h"  // 一定要包含key.h，顺序无所谓但不能漏
/* LED灯配置定义 */
#define LED_RCC     (RCC_APB2Periph_GPIOA)
#define LED_PORT    (GPIOA)
/* LED灯引脚定义 */
#define LED1_PIN    (GPIO_Pin_0)
#define LED2_PIN    (GPIO_Pin_1)
#define LED3_PIN    (GPIO_Pin_2)
#define LED4_PIN    (GPIO_Pin_3)
#define LED5_PIN    (GPIO_Pin_4)
#define LED6_PIN    (GPIO_Pin_5)
#define LED7_PIN    (GPIO_Pin_6)
#define LED8_PIN    (GPIO_Pin_7)
#define LED_ALL_PIN       (LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN |LED5_PIN | LED6_PIN | LED7_PIN | LED8_PIN)
 


void LED_Init(void)
{
     GPIO_InitTypeDef GPIO_InitStructrue;  
    
    // 1、使能内部时钟信号

    // 使能时钟
    RCC_APB2PeriphClockCmd(LED_RCC, ENABLE);   
    
    // 2、初始化GPIOA
    
    // 配置GPIO初始化结构体
    
    // 引脚
    GPIO_InitStructrue.GPIO_Pin = LED_ALL_PIN ;   

     // 输出推挽
    GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_PP;   

    // 输出速率
    GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;     
    
    // 初始化GPIOA
    GPIO_Init(LED_PORT, &GPIO_InitStructrue);   // 统一配置
    
    // 初始化灯（灭）
  GPIO_SetBits(LED_PORT,GPIO_InitStructrue.GPIO_Pin);    // 初始化这四个引脚全部为高电平
}    

void LED_1(void){

    uint16_t LEDS=LED1_PIN;

    while(LEDS!=GPIO_Pin_8)
        {
        

        GPIO_ResetBits(LED_PORT, LEDS);

        Delay_ms(500); 

        LEDS = LEDS << 1;

        }
    

}

void LED_2(void){

    uint16_t LEDS=LED8_PIN;

    while(LEDS!=LED1_PIN)
        {
        

        GPIO_ResetBits(LED_PORT, LEDS);

        Delay_ms(500);  

        LEDS = LEDS >> 1;

        }

    GPIO_ResetBits(LED_PORT, LEDS);

}

void LED_3(void){

    uint16_t LEDS=LED1_PIN;

    GPIO_ResetBits(LED_PORT, LEDS);

    while(LEDS!=GPIO_Pin_8)
        {

        GPIO_SetBits(LED_PORT, LEDS>>1);

        GPIO_ResetBits(LED_PORT, LEDS);

        Delay_ms(500); 

        LEDS = LEDS << 1;

        }
    

}

/**
  * @brief  LED灯控制
  * @param  LedNo：此处可以从LED1到LED8之间选择
  * @param    BitVal 从LED_OFF和LED_ON之间选择
                  LED_ON表示灯亮    LED_OFF表示灯灭
  * @retval 无
  */
void LED_Control(uint8_t LedNo, BitAction BitVal)
{
    switch(LedNo)
    {
        case LED1:    GPIO_WriteBit(LED_PORT, LED1_PIN, BitVal); break;
        case LED2:    GPIO_WriteBit(LED_PORT, LED2_PIN, BitVal); break;
        case LED3:    GPIO_WriteBit(LED_PORT, LED3_PIN, BitVal); break;
        case LED4:    GPIO_WriteBit(LED_PORT, LED4_PIN, BitVal); break;
        case LED5:    GPIO_WriteBit(LED_PORT, LED5_PIN, BitVal); break;
        case LED6:    GPIO_WriteBit(LED_PORT, LED6_PIN, BitVal); break;
        case LED7:    GPIO_WriteBit(LED_PORT, LED7_PIN, BitVal); break;
        case LED8:    GPIO_WriteBit(LED_PORT, LED8_PIN, BitVal); break;
        default: break;
    }
}



void LED_destroy(void){

    GPIO_SetBits(LED_PORT,LED_ALL_PIN);    

}


void DisplayBinary(uint8_t value)
{
    uint8_t i;
    for (i = 7; i >= 0; i--)
    {
        if (value & (1 << i))
            LED_Control(8 - i, LED_ON);
        else
            LED_Control(8 - i, LED_OFF);
    }
}
// 新增通用流水灯函数
void LED_Running(void)
{
    uint16_t curLed = LED1_PIN;   // 当前亮灯引脚，初始LED1
    int8_t step = 1;             // 步进：1左移正向，-1右移反向

    while(1)
    {
        LED_destroy();
        GPIO_ResetBits(LED_PORT, curLed);  // 点亮当前灯
        Delay_ms(500);

        // 中断修改全局标志，切换步进方向
        if(Led_Dir_Flag == 0)
            step = 1;
        else
            step = -1;

        // 根据步进更新当前灯位置
        if(step == 1)
            curLed <<= 1;
        else
            curLed >>= 1;

        // 边界回弹，防止移出LED1~LED8范围
        if(curLed > LED8_PIN)
            curLed = LED8_PIN;
        if(curLed < LED1_PIN)
            curLed = LED1_PIN;
    }
}