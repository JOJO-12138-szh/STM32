#include "key.h"

/* ────────────────── 宏定义：按键引脚 ────────────────── */
#define KEY_RCC         RCC_APB2Periph_GPIOA
#define KEY1_PORT       GPIOA
#define KEY1_PIN        GPIO_Pin_15
#define KEY2_PORT       GPIOA
#define KEY2_PIN        GPIO_Pin_14
#define KEY3_PORT       GPIOA
#define KEY3_PIN        GPIO_Pin_13
#define KEY4_PORT       GPIOA
#define KEY4_PIN        GPIO_Pin_12
#define KEY_ALL_PIN     (KEY1_PIN|KEY2_PIN|KEY3_PIN|KEY4_PIN)

// 全局流水灯方向标志，唯一定义处
uint8_t Led_Dir_Flag = 0;

/* ═══════════════════ 普通轮询按键初始化（保留你原有函数） ═══════════════════ */
void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // 使能GPIOA、AFIO时钟
    RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);
    
    // 禁用JTAG/SWD，释放PA13 PA14
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    
    // 上拉输入
    GPIO_InitStruct.GPIO_Pin = KEY_ALL_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY1_PORT, &GPIO_InitStruct);
}

/* ═══════════════════ 外部中断初始化函数（新增） ═══════════════════ */
void Key_EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    // 时钟使能
    RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    // 关闭下载口复用
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    // GPIO配置 上拉输入
    GPIO_InitStruct.GPIO_Pin = KEY_ALL_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY1_PORT, &GPIO_InitStruct);

    // AFIO中断线映射 PA12~15 -> EXTI12~15
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource13);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource14);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);

    // EXTI统一配置：下降沿触发中断
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;

    EXTI_InitStruct.EXTI_Line = EXTI_Line12;
    EXTI_Init(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = EXTI_Line13;
    EXTI_Init(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = EXTI_Line14;
    EXTI_Init(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = EXTI_Line15;
    EXTI_Init(&EXTI_InitStruct);

    // NVIC分组（全局只调用一次）
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // NVIC配置EXTI15_10中断通道
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);
}

/* ═══════════════════ 原有按键扫描函数保留 ═══════════════════ */
uint8_t Key_GetPressedMask(void)
{
    uint8_t m1 = 0, m2 = 0;

    if (GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN) == Bit_RESET) m1 |= KEY1_MASK;
    if (GPIO_ReadInputDataBit(KEY2_PORT, KEY2_PIN) == Bit_RESET) m1 |= KEY2_MASK;
    if (GPIO_ReadInputDataBit(KEY3_PORT, KEY3_PIN) == Bit_RESET) m1 |= KEY3_MASK;
    if (GPIO_ReadInputDataBit(KEY4_PORT, KEY4_PIN) == Bit_RESET) m1 |= KEY4_MASK;

    Delay_ms(10);

    if (GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN) == Bit_RESET) m2 |= KEY1_MASK;
    if (GPIO_ReadInputDataBit(KEY2_PORT, KEY2_PIN) == Bit_RESET) m2 |= KEY2_MASK;
    if (GPIO_ReadInputDataBit(KEY3_PORT, KEY3_PIN) == Bit_RESET) m2 |= KEY3_MASK;
    if (GPIO_ReadInputDataBit(KEY4_PORT, KEY4_PIN) == Bit_RESET) m2 |= KEY4_MASK;

    return (m1 == m2) ? m1 : 0;
}

/* ═══════════════════ 中断服务函数：任意按键按下翻转流水灯方向 ═══════════════════ */
void EXTI15_10_IRQHandler(void)
{
    // 判断是否是12/13/14/15中断线触发
    if(EXTI_GetITStatus(EXTI_Line12) || EXTI_GetITStatus(EXTI_Line13) ||
       EXTI_GetITStatus(EXTI_Line14) || EXTI_GetITStatus(EXTI_Line15))
    {
        Delay_ms(10); // 中断内软件消抖
        // 再次确认按键低电平
        if((GPIO_ReadInputData(GPIOA) & KEY_ALL_PIN) != KEY_ALL_PIN)
        {
            Led_Dir_Flag = !Led_Dir_Flag; // 切换流水灯方向
        }
        // 清除全部中断标志位
        EXTI_ClearITPendingBit(EXTI_Line12);
        EXTI_ClearITPendingBit(EXTI_Line13);
        EXTI_ClearITPendingBit(EXTI_Line14);
        EXTI_ClearITPendingBit(EXTI_Line15);
    }
}