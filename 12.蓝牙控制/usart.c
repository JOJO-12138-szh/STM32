#include "usart.h"
#include "LED.h"
#include "Car.h"
int flag_LY = 0;

/***************************************************************************************
 ** Usart1_Init: 串口1的初始化函数
 ** @baudrate: 波特率
 ** @Note: TX->PA9  RX->PA10
***************************************************************************************/
void Usart1_Init(u32 baudrate)
{
    GPIO_InitTypeDef g;
	USART_InitTypeDef u;
    NVIC_InitTypeDef n;
    /*
        1.串口GPIO配置
    */
    //1.1 使能GPIO分组时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    //1.2 初始化GPIO
    g.GPIO_Mode = GPIO_Mode_AF_PP;
    g.GPIO_Pin  = GPIO_Pin_9;
    g.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&g);

    g.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    g.GPIO_Pin  = GPIO_Pin_10;
    GPIO_Init(GPIOA,&g);

    /*
        2.USART配置
    */
    //2.1 使能USART分组时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    //2.2 初始化配置USART
    u.USART_BaudRate            =   baudrate;
    u.USART_HardwareFlowControl =   USART_HardwareFlowControl_None;
    u.USART_Mode                =   USART_Mode_Rx | USART_Mode_Tx;
    u.USART_Parity              =   USART_Parity_No;
    u.USART_StopBits            =   USART_StopBits_1;
    u.USART_WordLength          =   USART_WordLength_8b;
    USART_Init(USART1,&u);
    
    /*
        3.中断配置
    */
    //3.1 中断控制位使能
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

    //3.2 配置NVIC
    n.NVIC_IRQChannel       =   USART1_IRQn;
    n.NVIC_IRQChannelCmd    =   ENABLE;
    n.NVIC_IRQChannelPreemptionPriority = 2;
    n.NVIC_IRQChannelSubPriority        = 2;
    NVIC_Init(&n);

    /*
        4.开启串口
    */
    USART_Cmd(USART1,ENABLE);    
}

/***************************************************************************************
 ** Usart2_Init: 串口2的初始化函数
 ** @baudrate: 波特率
 ** @Note: TX->PA2  RX->PA3
***************************************************************************************/
void Usart2_Init(u32 baudrate)
{
	GPIO_InitTypeDef g;
    USART_InitTypeDef u;
    NVIC_InitTypeDef n;
    /*
        1.串口GPIO配置
    */
    //1.1 使能GPIO分组时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    //1.2 初始化GPIO

    g.GPIO_Mode = GPIO_Mode_AF_PP;
    g.GPIO_Pin  = GPIO_Pin_2;
    g.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&g);

    g.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    g.GPIO_Pin  = GPIO_Pin_3;
    GPIO_Init(GPIOA,&g);

    /*
        2.USART配置
    */
    //2.1 使能USART分组时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

    //2.2 初始化配置USART

    u.USART_BaudRate            =   baudrate;
    u.USART_HardwareFlowControl =   USART_HardwareFlowControl_None;
    u.USART_Mode                =   USART_Mode_Rx | USART_Mode_Tx;
    u.USART_Parity              =   USART_Parity_No;
    u.USART_StopBits            =   USART_StopBits_1;
    u.USART_WordLength          =   USART_WordLength_8b;
    USART_Init(USART2,&u);
    
    /*
        3.中断配置
    */
    //3.1 中断控制位使能
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

    //3.2 配置NVIC

    n.NVIC_IRQChannel       =   USART2_IRQn;
    n.NVIC_IRQChannelCmd    =   ENABLE;
    n.NVIC_IRQChannelPreemptionPriority = 2;
    n.NVIC_IRQChannelSubPriority        = 2;
    NVIC_Init(&n);

    /*
        4.开启串口
    */
    USART_Cmd(USART2,ENABLE);    
}

/***************************************************************************************
 ** Usart3_Init: 串口3的初始化函数
 ** @baudrate: 波特率
 ** @Note: TX->PB10  RX->PB11
***************************************************************************************/
void Usart3_Init(u32 baudrate)
{
	GPIO_InitTypeDef g;
    USART_InitTypeDef u;
    NVIC_InitTypeDef n;
    /*
        1.串口GPIO配置
    */
    //1.1 使能GPIO分组时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    //1.2 初始化GPIO

    g.GPIO_Mode = GPIO_Mode_AF_PP;
    g.GPIO_Pin  = GPIO_Pin_10;
    g.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&g);

    g.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    g.GPIO_Pin  = GPIO_Pin_11;
    GPIO_Init(GPIOB,&g);

    /*
        2.USART配置
    */
    //2.1 使能USART分组时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

    //2.2 初始化配置USART

    u.USART_BaudRate            =   baudrate;
    u.USART_HardwareFlowControl =   USART_HardwareFlowControl_None;
    u.USART_Mode                =   USART_Mode_Rx | USART_Mode_Tx;
    u.USART_Parity              =   USART_Parity_No;
    u.USART_StopBits            =   USART_StopBits_1;
    u.USART_WordLength          =   USART_WordLength_8b;
    USART_Init(USART3,&u);
    
    /*
        3.中断配置
    */
    //3.1 中断控制位使能
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);

    //3.2 配置NVIC

    n.NVIC_IRQChannel       =   USART3_IRQn;
    n.NVIC_IRQChannelCmd    =   ENABLE;
    n.NVIC_IRQChannelPreemptionPriority = 2;
    n.NVIC_IRQChannelSubPriority        = 2;
    NVIC_Init(&n);

    /*
        4.开启串口
    */
    USART_Cmd(USART3,ENABLE);    
}

/***************************************************************************************
 ** USART_SendDatas: 通过串口将数据连续发送过去
 ** @USARTx: 通过哪个串口将数据发送出去
 ** @SendBuf: 将要发送出去的数据
 ** @len: 要发送出去的字节数
***************************************************************************************/
void USART_SendDatas(USART_TypeDef *USARTx,unsigned char *SendBuf,uint8_t len)
{
    int i;
    for(i = 0;i < len;i++)
    {
        while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET)
            ;
        USART_SendData(USARTx,SendBuf[i]);
    }
}

/***************************************************************************************
 ** USART1_IRQHandler: 串口1的中断服务函数
***************************************************************************************/
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)//RXNE事件产生
    {
        //去读取数据
        unsigned char buf = USART_ReceiveData(USART1);
        if(buf == '0')
        {
            LED_Control(LED1,LED_ON);
        }
        else if(buf == '1')
        {
            LED_Control(LED1,LED_OFF);
        }
        else
        {
            //...
        }
        
        //清除中断标志
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}

#if 1
/***************************************************************************************
 ** USART2_IRQHandler: 串口2的中断服务函数
***************************************************************************************/
void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)//RXNE事件产生
    {
        //去读取数据
        unsigned char buf = USART_ReceiveData(USART2);
        if(buf == 0x01)
        {
            flag_LY = 1;
        }
        else if(buf == 0x02)
        {
            flag_LY = 2;
        }
        else
        {
            //...
        }
     
        //清除中断标志
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }
}
#endif

#if 1
/***************************************************************************************
 ** USART3_IRQHandler: 串口3的中断服务函数
***************************************************************************************/
void USART3_IRQHandler(void)
{
    unsigned char cmd;

    if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
    {
        cmd = USART_ReceiveData(USART3);

        switch(cmd)
        {
            case 0x00: Car_Stop(); break;
            case 0x01: Car_GoStraight(); break;
            case 0x02: Car_GoBack(); break;
            case 0x03: Car_LeftMove(); break;
            case 0x04: Car_RightMove(); break;
            case 0x05: Car_TurnLeft(); break;
            case 0x06: Car_TurnRight(); break;
            case 0x07: Car_ForwardLeft(); break;
            case 0x08: Car_ForwardRight(); break;
            case 0x09: Car_BackwardLeft(); break;
            case 0x0A: Car_BackwardRight(); break;
            case 0x0B: Car_PivotFrontLeft(); break;
            case 0x0C: Car_PivotFrontRight(); break;
            case 0x0D: Car_PivotRearLeft(); break;
            case 0x0E: Car_PivotRearRight(); break;
            default:   Car_Stop(); break;
        }

        USART_ClearITPendingBit(USART3,USART_IT_RXNE);
    }
}
#endif


/***************************************************************************************
 ** fputc: printf重定向到串口1
***************************************************************************************/
int fputc(int c,FILE *stream)
{
    USART_SendData(USART1,c & 0xFF);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
    return 0;
}

