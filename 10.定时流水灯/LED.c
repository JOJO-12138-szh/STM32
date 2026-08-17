#include "LED.h"

/* LED灯配置定义 */
#define LED_RCC 	(RCC_APB2Periph_GPIOA)
#define LED_PORT    (GPIOA)
/* LED灯引脚定义 */
#define LED1_PIN	(GPIO_Pin_0)
#define LED2_PIN	(GPIO_Pin_1)
#define LED3_PIN	(GPIO_Pin_2)
#define LED4_PIN	(GPIO_Pin_3)
#define LED5_PIN	(GPIO_Pin_4)
#define LED6_PIN	(GPIO_Pin_5)
#define LED7_PIN	(GPIO_Pin_6)
#define LED8_PIN	(GPIO_Pin_7)
#define LED_ALL_PIN	   (LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN |LED5_PIN | LED6_PIN | LED7_PIN | LED8_PIN)

static uint8_t current_index = 0;
static uint8_t direction = 0;   // 0: 从右到左，1: 从左到右

void LED_Update(void)
{
    GPIO_SetBits(LED_PORT, LED_ALL_PIN);  // 全灭

    uint16_t pin = (GPIO_Pin_0 << current_index);
    GPIO_ResetBits(LED_PORT, pin);        // 点亮当前

    if (direction)  // 从左到右
    {
        current_index++;
        if (current_index >= 8) current_index = 0;
    }
    else            // 从右到左
    {
        if (current_index == 0) current_index = 7;
        else current_index--;
    }
}

// 提供外部访问方向标志的接口（如需要）
void LED_SetDirection(uint8_t dir) { direction = dir; }

uint8_t LED_GetDirection(void) { return direction; }

void LED_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructrue;  
	
	// 1、使能内部时钟信号

	// 使能时钟
	RCC_APB2PeriphClockCmd(LED_RCC, ENABLE);   
	
	// 2、初始化GPIOA
	
	// 配置GPIO初始化结构体
	
	// 引脚
	GPIO_InitStructrue.GPIO_Pin = LED_ALL_PIN ;   

	 // 输出推挽
	GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_PP;   

	// 输出速率
	GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;     
	
	// 初始化GPIOA
	GPIO_Init(LED_PORT, &GPIO_InitStructrue);   // 统一配置
	
	// 初始化灯（灭）
  GPIO_SetBits(LED_PORT,GPIO_InitStructrue.GPIO_Pin);	// 初始化这四个引脚全部为高电平
}	

void LED_1(void){

	uint16_t LEDS=LED1_PIN;

	while(LEDS!=GPIO_Pin_8)
		{
		

		GPIO_ResetBits(LED_PORT, LEDS);

		Delay_ms(500); 

		LEDS = LEDS << 1;

		}
	

}

void LED_2(void){

	uint16_t LEDS=LED8_PIN;

	while(LEDS!=LED1_PIN)
		{
		

		GPIO_ResetBits(LED_PORT, LEDS);

		Delay_ms(500);  

		LEDS = LEDS >> 1;

		}

	GPIO_ResetBits(LED_PORT, LEDS);

}

void LED_3(void){

	uint16_t LEDS=LED1_PIN;

	GPIO_ResetBits(LED_PORT, LEDS);

	while(LEDS!=GPIO_Pin_8)
		{

		GPIO_SetBits(LED_PORT, LEDS>>1);

		GPIO_ResetBits(LED_PORT, LEDS);

		Delay_ms(500); 

		LEDS = LEDS << 1;

		}
	

}

/**
  * @brief  LED灯控制
  * @param  LedNo：此处可以从LED1到LED8之间选择
  * @param	BitVal 从LED_OFF和LED_ON之间选择
  				LED_ON表示灯亮	LED_OFF表示灯灭
  * @retval 无
  */
void LED_Control(uint8_t LedNo, BitAction BitVal)
{
	switch(LedNo)
	{
		case LED1:	GPIO_WriteBit(LED_PORT, LED1_PIN, BitVal); break;
		case LED2:	GPIO_WriteBit(LED_PORT, LED2_PIN, BitVal); break;
		case LED3:	GPIO_WriteBit(LED_PORT, LED3_PIN, BitVal); break;
		case LED4:	GPIO_WriteBit(LED_PORT, LED4_PIN, BitVal); break;
		case LED5:	GPIO_WriteBit(LED_PORT, LED5_PIN, BitVal); break;
		case LED6:	GPIO_WriteBit(LED_PORT, LED6_PIN, BitVal); break;
		case LED7:	GPIO_WriteBit(LED_PORT, LED7_PIN, BitVal); break;
		case LED8:	GPIO_WriteBit(LED_PORT, LED8_PIN, BitVal); break;
		default: break;
	}
}



void LED_destroy(void){

	GPIO_SetBits(LED_PORT,LED_ALL_PIN);	

}


void DisplayBinary(uint8_t value)
{
    for (int i = 7; i >= 0; i--)   // 从最高位开始
    {
        if (value & (1 << i))
            LED_Control(8 - i, LED_ON);   // 注意：i=7 → LED1，i=0 → LED8
        else
            LED_Control(8 - i, LED_OFF);
    }
}





