#include "Track.h"
#include "Car.h"

#define TRACK_RCC           RCC_APB2Periph_GPIOA
#define TRACK_PORT          GPIOA

#define TRACK_LEFT_PIN      GPIO_Pin_8
#define TRACK_RIGHT_PIN     GPIO_Pin_9

/* 低电平检测到黑线 */
#define TRACK_BLACK         1
#define TRACK_WHITE         0

/* 转正补偿 */
#define TRACK_COMPENSATE    60000

typedef enum
{
    TRACK_FORWARD = 0,
    TRACK_LEFT,
    TRACK_RIGHT
}TRACK_STATE;

static TRACK_STATE TrackState = TRACK_FORWARD;

/********************软延时********************/
static void SoftDelay(uint32_t t)
{
    while(t--);
}

/********************左探头********************/
static uint8_t Track_ReadLeft(void)
{
    SoftDelay(200);

    if(GPIO_ReadInputDataBit(TRACK_PORT,TRACK_LEFT_PIN)==Bit_RESET)
    {
        SoftDelay(200);

        if(GPIO_ReadInputDataBit(TRACK_PORT,TRACK_LEFT_PIN)==Bit_RESET)
            return TRACK_BLACK;
    }

    return TRACK_WHITE;
}

/********************右探头********************/
static uint8_t Track_ReadRight(void)
{
    SoftDelay(200);

    if(GPIO_ReadInputDataBit(TRACK_PORT,TRACK_RIGHT_PIN)==Bit_RESET)
    {
        SoftDelay(200);

        if(GPIO_ReadInputDataBit(TRACK_PORT,TRACK_RIGHT_PIN)==Bit_RESET)
            return TRACK_BLACK;
    }

    return TRACK_WHITE;
}

/********************初始化********************/
void Track_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(TRACK_RCC,ENABLE);

    GPIO_InitStructure.GPIO_Pin=
        TRACK_LEFT_PIN|
        TRACK_RIGHT_PIN;

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;

    GPIO_Init(TRACK_PORT,&GPIO_InitStructure);

    TrackState=TRACK_FORWARD;
}

/********************循迹********************/
void Track_Run(void)
{
    uint8_t Left;
    uint8_t Right;

    Left=Track_ReadLeft();
    Right=Track_ReadRight();

    switch(TrackState)
    {

    /************正常前进************/
    case TRACK_FORWARD:

        Car_GoStraight();

        if((Left==TRACK_BLACK)&&(Right==TRACK_WHITE))
        {
            TrackState=TRACK_LEFT;
        }

        else if((Left==TRACK_WHITE)&&(Right==TRACK_BLACK))
        {
            TrackState=TRACK_RIGHT;
        }

        break;

    /************持续左转************/
    case TRACK_LEFT:

        Car_TurnLeft();

        Right=Track_ReadRight();

        if(Right==TRACK_BLACK)
        {
            SoftDelay(TRACK_COMPENSATE);

            Car_GoStraight();

            TrackState=TRACK_FORWARD;
        }

        break;

    /************持续右转************/
    case TRACK_RIGHT:

        Car_TurnRight();

        Left=Track_ReadLeft();

        if(Left==TRACK_BLACK)
        {
            SoftDelay(TRACK_COMPENSATE);

            Car_GoStraight();

            TrackState=TRACK_FORWARD;
        }

        break;
    }

}