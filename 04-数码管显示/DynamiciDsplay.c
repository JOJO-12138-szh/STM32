#include "DynamiciDsplay.h"
#include "stm32f10x.h"

// 引脚宏定义 
#define SEG_GPIO_PORT      GPIOA
#define SEG_PIN_ALL        (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | \
                            GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7)

#define ADDR_GPIO_PORT     GPIOB
#define ADDR_PIN_ALL       (GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5)
#define ADDR_PIN_A         GPIO_Pin_5
#define ADDR_PIN_B         GPIO_Pin_4
#define ADDR_PIN_C         GPIO_Pin_3

/**
  * @brief  数码管段码表（共阴极）
  *         0-9的七段编码
  */
static const uint8_t segCode[10] = {
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D,  // 6
    0x07,  // 7
    0x7F,  // 8
    0x6F   // 9
};

// 显示缓冲区（8位）
static uint8_t dispBuff[8] = {0};
static uint8_t currentBit = 0;

/**
  * @brief  动态数码管初始化
  * @param  无
  * @retval 无
  */
void DynamiciDsplay_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // 1. 使能 GPIOA 和 GPIOB 时钟，以及AFIO复位电路
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    // 2. 禁用 JTAG 以释放 PB3/PB4（保留 SWD）
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    // 3. 配置段引脚（PA0~PA7）为推挽输出
    GPIO_InitStruct.GPIO_Pin   = SEG_PIN_ALL;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SEG_GPIO_PORT, &GPIO_InitStruct);

    // 4. 配置地址引脚（PB3~PB5）为推挽输出
    GPIO_InitStruct.GPIO_Pin   = ADDR_PIN_ALL;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ADDR_GPIO_PORT, &GPIO_InitStruct);

    // 5. 初始关闭所有段和地址
    GPIO_ResetBits(SEG_GPIO_PORT, SEG_PIN_ALL);
    GPIO_ResetBits(ADDR_GPIO_PORT, ADDR_PIN_ALL);
}

/**
  * @brief  设置某一位显示的数字
  * @param  pos：位号（0~7，0为最左边）
  * @param  digit：数字（0~9）
  * @retval 无
  */
void DynamiciDsplay_SetDigit(uint8_t pos, uint8_t digit)
{
    if (pos > 7) pos = 7;
    if (digit > 9) digit = 9;
    dispBuff[pos] = digit;
}

/**
  * @brief  动态扫描刷新（需在定时中断中周期性调用）
  * @param  无
  * @retval 无
  */
void DynamiciDsplay_Refresh(void)
{
    // 所有变量放最开头
    uint8_t seg;
    uint8_t addr;

    seg = segCode[dispBuff[currentBit]];

    GPIO_Write(SEG_GPIO_PORT, (GPIO_ReadOutputData(SEG_GPIO_PORT) & ~SEG_PIN_ALL) | seg);

    addr = currentBit & 0x07;
    GPIO_ResetBits(ADDR_GPIO_PORT, ADDR_PIN_ALL);
    if(addr & (1<<0)) GPIO_SetBits(ADDR_GPIO_PORT, ADDR_PIN_A);
    if(addr & (1<<1)) GPIO_SetBits(ADDR_GPIO_PORT, ADDR_PIN_B);
    if(addr & (1<<2)) GPIO_SetBits(ADDR_GPIO_PORT, ADDR_PIN_C);

    currentBit = (currentBit + 1) & 0x07;
}
