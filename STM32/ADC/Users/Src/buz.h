#ifndef _buz_H
#define _buz_H
#include "stm32f10x.h"
#include "systick.h"
#define buz GPIO_Pin_5	  //PB5
void GPIOINIT_BUZ(void);
void RCCINIT_BUZ(void);
void sound(void);

#endif
