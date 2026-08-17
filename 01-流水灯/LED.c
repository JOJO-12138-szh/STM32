#include "LED.h"
#include "SysTick.h"

#define LED1    1
#define LED2    2
#define LED3    3
#define LED4    4
#define LED5    5
#define LED6    6
#define LED7    7
#define LED8    8

/* LED灯状态定义 */
#define LED_ON   Bit_RESET   // 低电平点亮
#define LED_OFF  Bit_SET     // 高电平熄灭

/* LED灯配置定义 */
#define LED_RCC     (RCC_APB2Periph_GPIOA)
#define LED_PORT    (GPIOA)

#define LED1_PIN GPIO_Pin_0 
#define LED2_PIN GPIO_Pin_1 
#define LED3_PIN GPIO_Pin_2 
#define LED4_PIN GPIO_Pin_3 
#define LED5_PIN GPIO_Pin_4 
#define LED6_PIN GPIO_Pin_5 
#define LED7_PIN GPIO_Pin_6 
#define LED8_PIN GPIO_Pin_7 

#define LED_PIN_ALL  (LED1_PIN  | LED2_PIN  | LED3_PIN  | LED4_PIN  | \
                       LED5_PIN  | LED6_PIN  | LED7_PIN  | LED8_PIN)					  
#define LED_COUNT 8

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    

    GPIO_InitStructure.GPIO_Pin = LED_PIN_ALL ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_SetBits(GPIOA, LED_PIN_ALL);
}
/**
  * @brief  LED灯控制
  * @param  LedNo：LED1~LED8
  * @param  BitVal：LED_ON（亮）或 LED_OFF（灭）
  * @retval 无
  */
void LED_Control(uint8_t LedNo, BitAction BitVal)
{
    switch (LedNo)
    {
        case LED1: GPIO_WriteBit(LED_PORT, LED1_PIN, BitVal); break;
        case LED2: GPIO_WriteBit(LED_PORT, LED2_PIN, BitVal); break;
        case LED3: GPIO_WriteBit(LED_PORT, LED3_PIN, BitVal); break;
        case LED4: GPIO_WriteBit(LED_PORT, LED4_PIN, BitVal); break;
        case LED5: GPIO_WriteBit(LED_PORT, LED5_PIN, BitVal); break;
        case LED6: GPIO_WriteBit(LED_PORT, LED6_PIN, BitVal); break;
        case LED7: GPIO_WriteBit(LED_PORT, LED7_PIN, BitVal); break;
        case LED8: GPIO_WriteBit(LED_PORT, LED8_PIN, BitVal); break;
        default: break;
    }
}
/**
  * @brief  流水灯模式1：从前往后依次亮起，不断累积（LED1→LED2→...→LED8）
  * @param  无
  * @retval 无
  */

void LED_Mode1_Forward(void)
{
    uint8_t i;
    
    // 先全部熄灭
    for (i = LED1; i <= LED8; i++)
    {
        LED_Control(i, LED_OFF);
    }
    Delay_ms(200);
    
    // 从LED1到LED8逐个点亮，不断累积
    for (i = LED1; i <= LED8; i++)
    {
        LED_Control(i, LED_ON);   // 点亮当前LED
        Delay_ms(200);
    }
}

/**
  * @brief  流水灯模式2：从后往前依次亮起，不断累积（LED8→LED7→...→LED1）
  * @param  无
  * @retval 无
  */
void LED_Mode2_Backward(void)
{
    uint8_t i;
    
    // 先全部熄灭
    for (i = LED1; i <= LED8; i++)
    {
        LED_Control(i, LED_OFF);
    }
    Delay_ms(200);
    
    // 从LED8到LED1逐个点亮，不断累积
    for (i = LED8; i >= LED1; i--)
    {
        LED_Control(i, LED_ON);   // 点亮当前LED
        Delay_ms(200);
    }
}

/**
  * @brief  流水灯模式3：从前往后逐个亮起，每次只亮一个（LED1→LED2→...→LED8）
  * @param  无
  * @retval 无
  */
void LED_Mode3_Single(void)
{
    uint8_t i;
    uint8_t j;
    
    // 先全部熄灭
    for (i = LED1; i <= LED8; i++)
    {
        LED_Control(i, LED_OFF);
    }
    Delay_ms(200);
    
    // 每次只点亮一个LED
    for (i = LED1; i <= LED8; i++)
    {
        // 全部熄灭
        for (j = LED1; j <= LED8; j++)
        {
            LED_Control(j, LED_OFF);
        }
        
        // 点亮当前LED
        LED_Control(i, LED_ON);
        Delay_ms(200);
    }
}