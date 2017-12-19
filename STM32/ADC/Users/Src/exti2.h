#ifndef _exti2_H
#define _exti2_H
#include "stm32f10x.h"
#define k_left GPIO_Pin_2  //K1
void RCCINIT_EXTI2(void);
void GPIOINIT_EXTI2(void);
void EXTIINIT_EXTI2(void);
void NVICINIT_EXTI2(void);

#endif
