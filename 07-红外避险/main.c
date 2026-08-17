#include "stm32f10x.h"
#include "Car.h"
#include "Infrared.h"

void Delay(uint32_t t)
{
    while(t--);
}

int main(void)
{
    Car_Init();
    IR_Init();

    while(1)
    {
        // 默认一直前进
        Car_GoStraight();

        // 左右都有障碍
        if(IR_LeftDetect() && IR_RightDetect())
        {
            Car_Stop();
            Delay(3000000);

            // 后退
            Car_GoBack();
            Delay(15000000);

            // 左平移绕开
            Car_LeftMove();
            Delay(18000000);

            // 继续前进
            Car_GoStraight();
            Delay(10000000);
        }

        // 左侧有障碍
        else if(IR_LeftDetect())
        {
            // 右平移
            Car_RightMove();
            Delay(12000000);

            // 恢复前进
            Car_GoStraight();
            Delay(8000000);
        }

        // 右侧有障碍
        else if(IR_RightDetect())
        {
            // 左平移
            Car_LeftMove();
            Delay(12000000);

            // 恢复前进
            Car_GoStraight();
            Delay(8000000);
        }
    }
}