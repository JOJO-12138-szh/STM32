#include "matrix_led.h"

// 笑脸的列数据 (对应第一行到第八行，低电平有效点亮)
const uint8_t smile_cols[] = {0xC3, 0xBD, 0x5A, 0x7E, 0x5A, 0x66, 0xBD, 0xC3};
// 行选通数据 (595输出，高电平有效：ROW1 -> ROW8)
const uint8_t smile_rows[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

// 74HC595 引脚定义 (基于您的第一张和第二张图)
#define HC595_RCLK_PIN    GPIO_Pin_5   // PB5
#define HC595_SRCLK_PIN   GPIO_Pin_3   // PB3
#define HC595_SER_PIN     GPIO_Pin_4   // PB4
#define HC595_PORT        GPIOB

// 列控制端口 (PA0 ~ PA7)
#define MATRIX_COL_PORT   GPIOA

/**
  * @brief  初始化点阵相关的 GPIO 和 74HC595 引脚
  */
void Matrix_LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. 开启 GPIOA, GPIOB 和 AFIO 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    // 2. 禁用 JTAG，释放 PB3 和 PB4 
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    // 3. 初始化列控制引脚 (PA0 ~ PA7)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
                                  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MATRIX_COL_PORT, &GPIO_InitStructure);

    // 4. 初始化 74HC595 控制引脚 (PB3, PB4, PB5)
    GPIO_InitStructure.GPIO_Pin = HC595_RCLK_PIN | HC595_SRCLK_PIN | HC595_SER_PIN;
    GPIO_Init(HC595_PORT, &GPIO_InitStructure);

    // 将595引脚初始化为低电平
    GPIO_ResetBits(HC595_PORT, HC595_RCLK_PIN | HC595_SRCLK_PIN | HC595_SER_PIN);
}

/**
  * @brief  向 74HC595 写入一个字节
  */
static void HC595_WriteByte(uint8_t byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        // 先准备数据线 SER (从最高位 MSB 开始发送)
        if (byte & 0x80)
            GPIO_SetBits(HC595_PORT, HC595_SER_PIN);
        else
            GPIO_ResetBits(HC595_PORT, HC595_SER_PIN);
        
        byte <<= 1;

        // 产生上升沿将数据移入寄存器 (SRCLK)
        GPIO_ResetBits(HC595_PORT, HC595_SRCLK_PIN);
        GPIO_SetBits(HC595_PORT, HC595_SRCLK_PIN);
    }
    
    // 产生上升沿将数据锁存到输出引脚 (RCLK)
    GPIO_ResetBits(HC595_PORT, HC595_RCLK_PIN);
    GPIO_SetBits(HC595_PORT, HC595_RCLK_PIN);
}

/**
  * @brief  点阵动态扫描刷新函数 (需在 main 的主循环中不断调用)
  */
void Matrix_LED_Refresh(void)
{
    uint8_t i;
    volatile uint32_t delay;

    for (i = 0; i < 8; i++)
    {
        // 1. 消隐：先关闭所有列，防止切换行时产生拖影
        GPIO_Write(MATRIX_COL_PORT, (MATRIX_COL_PORT->ODR & 0xFF00) | 0xFF);

        // 2. 选通当前行
        HC595_WriteByte(smile_rows[i]);

        // 3. 送入当前行的列数据显示
        MATRIX_COL_PORT->ODR = (MATRIX_COL_PORT->ODR & 0xFF00) | smile_cols[i];

        // 4. 简易微秒级延时，留出显示时间
        delay = 200;
        while(delay--);
    }
}