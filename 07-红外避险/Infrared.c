#include "Infrared.h"

#define IR_RCC      RCC_APB2Periph_GPIOA
#define IR_PORT     GPIOA

#define IR_LEFT_PIN     GPIO_Pin_8
#define IR_RIGHT_PIN    GPIO_Pin_9
/**
  * @brief  红外传感器初始化
  * @param  无
  * @retval 无
  */
void IR_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(IR_RCC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = IR_LEFT_PIN | IR_RIGHT_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(IR_PORT, &GPIO_InitStructure);
}


/**
  * @brief  左侧红外障碍检测
  * @param  无
  * @retval 1：检测到障碍物，0：无障碍物
  */
uint8_t IR_LeftDetect(void)
{
    return (GPIO_ReadInputDataBit(IR_PORT,IR_LEFT_PIN)==Bit_RESET);
}


/**
  * @brief  右侧红外障碍检测
  * @param  无
  * @retval 1：检测到障碍物，0：无障碍物
  */
uint8_t IR_RightDetect(void)
{
    return (GPIO_ReadInputDataBit(IR_PORT,IR_RIGHT_PIN)==Bit_RESET);
}