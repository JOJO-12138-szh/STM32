#include "stm32f10x.h"

#include "LED.h"

#include "KEY.h"

void Delay(u32 t)
{
    while (t--)
        ;
}

int main(void)
{

    u8 key;

    LED_Init();

    KEY_Init();

    /*
    初始关闭LED
    */

    LED_Show(0);

    while (1)
    {

        key = KEY_Scan();

        if (key)
        {

            /*
            按键值二进制显示
            */

            LED_Show(key);

            Delay(300000);

            /*
            等待松手
            */

            while (KEY_Scan() != 0)
                ;
        }
    }
}