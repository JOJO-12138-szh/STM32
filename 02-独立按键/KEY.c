#include "Key.h"
#define KEY_RCC     (RCC_APB2Periph_GPIOA)
// 按键引脚定义
#define KEY1_PIN   (GPIO_Pin_15)
#define KEY2_PIN   (GPIO_Pin_14)
#define KEY3_PIN   (GPIO_Pin_13)
#define KEY4_PIN   (GPIO_Pin_12)
#define KEY_PORT   (GPIOA)

// 按键按下检测（低电平有效）
#define KEY1_PRESSED  (GPIO_ReadInputDataBit(KEY_PORT, KEY1_PIN) == Bit_RESET)
#define KEY2_PRESSED  (GPIO_ReadInputDataBit(KEY_PORT, KEY2_PIN) == Bit_RESET)
#define KEY3_PRESSED  (GPIO_ReadInputDataBit(KEY_PORT, KEY3_PIN) == Bit_RESET)
#define KEY4_PRESSED  (GPIO_ReadInputDataBit(KEY_PORT, KEY4_PIN) == Bit_RESET)
// 按键初始化（包含禁用SWD/JTAG）
/**
  * @brief  按键初始化（包含禁用SWD/JTAG）
  * @param  无
  * @retval 无
  */
#include "Key.h"

void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = KEY1_PIN | KEY2_PIN | KEY3_PIN | KEY4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_PORT, &GPIO_InitStruct);
}

/**
  * @brief  获取指定按键状态
  * @param  key_num：1~4
  * @retval 1-按下，0-松开
  */
uint8_t KEY_GetState(uint8_t key_num)
{
    switch (key_num)
    {
        case 1: return KEY1_PRESSED ? 1 : 0;
        case 2: return KEY2_PRESSED ? 1 : 0;
        case 3: return KEY3_PRESSED ? 1 : 0;
        case 4: return KEY4_PRESSED ? 1 : 0;
        default: return 0;
    }
}

/**
  * @brief  一次性获取所有按键状态
  * @param  key1：KEY1状态指针
  * @param  key2：KEY2状态指针
  * @param  key3：KEY3状态指针
  * @param  key4：KEY4状态指针
  * @retval 无
  */
void KEY_GetAllState(uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *key4)
{
    if (key1) *key1 = KEY_GetState(1);
    if (key2) *key2 = KEY_GetState(2);
    if (key3) *key3 = KEY_GetState(3);
    if (key4) *key4 = KEY_GetState(4);
}