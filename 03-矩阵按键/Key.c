#include "KEY.h"

/**
  * @brief  矩阵键盘初始化
  * @param  无
  * @retval 无
  */

void KEY_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    /*
    开启GPIOB
    */

    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOB,
        ENABLE);

    /*
    行 PB8~PB11
    */

    GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_8 |
        GPIO_Pin_9 |
        GPIO_Pin_10 |
        GPIO_Pin_11;

    GPIO_InitStructure.GPIO_Mode =
        GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Speed =
        GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*
    列 PB12~PB15

    输入下拉
    */

    GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_12 |
        GPIO_Pin_13 |
        GPIO_Pin_14 |
        GPIO_Pin_15;

    GPIO_InitStructure.GPIO_Mode =
        GPIO_Mode_IPD;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*
    初始化所有行低
    */

    GPIO_ResetBits(GPIOB,
                   GPIO_Pin_8 |
                       GPIO_Pin_9 |
                       GPIO_Pin_10 |
                       GPIO_Pin_11);
}

/**
  * @brief  扫描按键（4x4矩阵键盘）
  * @param  无
  * @retval 按键编号（1~16），0表示无按键按下
  *         按键布局：
  *         1  2  3  4
  *         5  6  7  8
  *         9  10 11 12
  *         13 14 15 16
  */

u8 KEY_Scan(void)
{

    u8 key = 0;

    /*
    第一行拉高
    */

    GPIO_SetBits(GPIOB, GPIO_Pin_8);

    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1)
        key = 1;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 1)
        key = 2;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1)
        key = 3;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 1)
        key = 4;

    GPIO_ResetBits(GPIOB, GPIO_Pin_8);

    /*
    第二行拉高
    */

    GPIO_SetBits(GPIOB, GPIO_Pin_9);

    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1)
        key = 5;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 1)
        key = 6;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1)
        key = 7;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 1)
        key = 8;

    GPIO_ResetBits(GPIOB, GPIO_Pin_9);

    /*
    第三行拉高
    */

    GPIO_SetBits(GPIOB, GPIO_Pin_10);

    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1)
        key = 9;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 1)
        key = 10;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1)
        key = 11;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 1)
        key = 12;

    GPIO_ResetBits(GPIOB, GPIO_Pin_10);

    /*
    第四行拉高
    */

    GPIO_SetBits(GPIOB, GPIO_Pin_11);

    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1)
        key = 13;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 1)
        key = 14;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1)
        key = 15;

    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 1)
        key = 16;

    GPIO_ResetBits(GPIOB,
                   GPIO_Pin_8 |
                       GPIO_Pin_9 |
                       GPIO_Pin_10 |
                       GPIO_Pin_11);

    return key;
}