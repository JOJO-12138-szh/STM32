#include "LED.h"

void LED_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOA,
        ENABLE);

    GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_0 |
        GPIO_Pin_1 |
        GPIO_Pin_2 |
        GPIO_Pin_3 |
        GPIO_Pin_4 |
        GPIO_Pin_5 |
        GPIO_Pin_6 |
        GPIO_Pin_7;

    GPIO_InitStructure.GPIO_Mode =
        GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Speed =
        GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*
    关闭LED

    LED低电平亮
    */

    GPIO_SetBits(GPIOA,
                 GPIO_Pin_0 |
                     GPIO_Pin_1 |
                     GPIO_Pin_2 |
                     GPIO_Pin_3 |
                     GPIO_Pin_4 |
                     GPIO_Pin_5 |
                     GPIO_Pin_6 |
                     GPIO_Pin_7);
}

void LED_Show(u8 data)
{

    /*
    D1=bit7
    D2=bit6
    D3=bit5
    D4=bit4
    D5=bit3
    D6=bit2
    D7=bit1
    D8=bit0
    */

    GPIO_WriteBit(GPIOA,
                  GPIO_Pin_0,
                  (data & 0x80) ? Bit_RESET : Bit_SET);

    GPIO_WriteBit(GPIOA,
                  GPIO_Pin_1,
                  (data & 0x40) ? Bit_RESET : Bit_SET);

    GPIO_WriteBit(GPIOA,
                  GPIO_Pin_2,
                  (data & 0x20) ? Bit_RESET : Bit_SET);

    GPIO_WriteBit(GPIOA,
                  GPIO_Pin_3,
                  (data & 0x10) ? Bit_RESET : Bit_SET);

    GPIO_WriteBit(GPIOA,
                  GPIO_Pin_4,
                  (data & 0x08) ? Bit_RESET : Bit_SET);

    GPIO_WriteBit(GPIOA,
                  GPIO_Pin_5,
                  (data & 0x04) ? Bit_RESET : Bit_SET);

    GPIO_WriteBit(GPIOA,
                  GPIO_Pin_6,
                  (data & 0x02) ? Bit_RESET : Bit_SET);

    GPIO_WriteBit(GPIOA,
                  GPIO_Pin_7,
                  (data & 0x01) ? Bit_RESET : Bit_SET);
}