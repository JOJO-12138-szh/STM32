#include "stm32f10x.h"
#include "matrix_led.h"

int main(void)
{
    // 初始化点阵和 GPIO 端口
    Matrix_LED_Init();

    while(1)
    {
        // 动态扫描显示笑脸
        // 595 锁存和 ODR 切换速度很快，不断轮询即可实现稳定不闪烁的笑脸
        Matrix_LED_Refresh();
    }
}