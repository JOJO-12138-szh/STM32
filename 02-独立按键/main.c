#include "stm32f10x.h"
#include "LED.h"
#include "Key.h"
/**
  * @brief  简单延时（用于消抖）解决闪烁问题。
  * @param  count：延时计数值
  * @retval 无
  */
void Delay(uint32_t count)
{
    while (count--);
}
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    uint8_t key1, key2, key3, key4;
    
    KEY_Init();
    LED_Init();
    
    while (1)
    {
        KEY_GetAllState(&key1, &key2, &key3, &key4);
        LED_Update(key1, key2, key3, key4);
        Delay(10000);
    }
}