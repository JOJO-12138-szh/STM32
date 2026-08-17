#include "stm32f10x.h"
#include "SysTick.h"
#include "LED.h"
#include "Serial.h"

int main(void)
{
    // 全局只配置一次NVIC分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // 外设初始化
    LED_Init();
    Serial_Init();
 
    while(1)
    {
        // 调用你封装的接收判断函数
        if(Serial_GetRxFlag() == 1)
        {
            // 获取串口收到的1字节数据
            uint8_t recv_byte = Serial_GetRxData();
            // 串口回显收到的数据
            Serial_Printf("Re: 0x%02X\r\n", recv_byte);
            // 调用你写好的二进制显示函数，自动按bit点亮LED
            DisplayBinary(recv_byte);
        }
    }
}