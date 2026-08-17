#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"



void KEY_Init(void);
uint8_t KEY_GetState(uint8_t key_num); 
void KEY_GetAllState(uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *key4);

#endif