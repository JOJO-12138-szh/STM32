#include "stm32f10x.h"
#include "Car.h"
#include "Track.h"

int main(void)
{
    Car_Init();

    Track_Init();

    while(1)
    {
        Track_Run();
    }
}