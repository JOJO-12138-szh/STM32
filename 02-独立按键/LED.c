#include "LED.h"
// LED引脚定义
#define LED1_PIN   GPIO_Pin_0
#define LED2_PIN   GPIO_Pin_1
#define LED3_PIN   GPIO_Pin_2
#define LED4_PIN   GPIO_Pin_3
#define LED5_PIN   GPIO_Pin_4
#define LED_PORT   GPIOA

// LED控制宏（低电平点亮）
#define LED1_ON    GPIO_ResetBits(LED_PORT, LED1_PIN)   // Reset = 低电平 = 点亮
#define LED1_OFF   GPIO_SetBits(LED_PORT, LED1_PIN)     // Set = 高电平 = 熄灭
#define LED2_ON    GPIO_ResetBits(LED_PORT, LED2_PIN)
#define LED2_OFF   GPIO_SetBits(LED_PORT, LED2_PIN)
#define LED3_ON    GPIO_ResetBits(LED_PORT, LED3_PIN)
#define LED3_OFF   GPIO_SetBits(LED_PORT, LED3_PIN)
#define LED4_ON    GPIO_ResetBits(LED_PORT, LED4_PIN)
#define LED4_OFF   GPIO_SetBits(LED_PORT, LED4_PIN)
#define LED5_ON    GPIO_ResetBits(LED_PORT, LED5_PIN)
#define LED5_OFF   GPIO_SetBits(LED_PORT, LED5_PIN)

// 所有LED熄灭（全部输出高电平）
#define LED_ALL_OFF  GPIO_SetBits(LED_PORT, LED1_PIN | LED2_PIN | \
                                  LED3_PIN | LED4_PIN | LED5_PIN)


// LED初始化
/**
  * @brief  LED初始化
  * @param  无
  * @retval 无
  */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // 配置LED引脚为推挽输出
    GPIO_InitStruct.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN | LED5_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStruct);
    
    // 初始全部熄灭
    LED_ALL_OFF;
}

// 各LED独立控制函数
/**
  * @brief  LED灯控制
  * @param  LedNo：LED1~LED5
  * @param  BitVal：LED_ON（亮）或 LED_OFF（灭）
  * @retval 无
  */
void LED_Control(uint8_t led_num, uint8_t state)
{
    switch (led_num)
    {
        case 1: if (state) LED1_ON; else LED1_OFF; break;
        case 2: if (state) LED2_ON; else LED2_OFF; break;
        case 3: if (state) LED3_ON; else LED3_OFF; break;
        case 4: if (state) LED4_ON; else LED4_OFF; break;
        case 5: if (state) LED5_ON; else LED5_OFF; break;
        default: break;
    }
}

/**
  * @brief  根据按键状态更新所有LED
  * @param  key1：KEY1状态（1按下，0松开）
  * @param  key2：KEY2状态（1按下，0松开）
  * @param  key3：KEY3状态（1按下，0松开）
  * @param  key4：KEY4状态（1按下，0松开）
  * @retval 无
  * @note   功能：
  *          1. 4个按键分别控制LED1~LED4（按下亮，松开灭）
  *          2. 2个及以上按键按下时，LED5亮，否则灭
  *          3. 2个及以上按键按下时，LED1~LED4全部熄灭
  */
void LED_Update(uint8_t key1, uint8_t key2, uint8_t key3, uint8_t key4)
{
    uint8_t pressCount = 0;
    
    // 控制前4个LED
    LED_Control(1, key1);
    LED_Control(2, key2);
    LED_Control(3, key3);
    LED_Control(4, key4);
    
    // 统计按下的按键数量
    if (key1) pressCount++;
    if (key2) pressCount++;
    if (key3) pressCount++;
    if (key4) pressCount++;
    
    // 控制第5个LED：两个及以上按键按下时亮
    if (pressCount >= 2)
        LED5_ON;
    else
        LED5_OFF;
}