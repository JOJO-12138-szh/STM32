#include "DynamiciDsplay.h"
#include "SysTick.h"
#include "stm32f10x.h"

int main(void)
{
    u8 i;  // 把变量挪到大括号后面第一行！
    DynamiciDsplay_Init();

    for ( i = 0; i < 8; i++) {
        DynamiciDsplay_SetDigit(i, (i + 1) % 10);
    }

    while (1) {
        DynamiciDsplay_Refresh();
        delay_ms(200);
    }
}
