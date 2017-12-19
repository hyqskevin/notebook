#ifndef _exti3_H
#define _exti3_H
#include "stm32f10x.h"
#define k_down GPIO_Pin_3  //K2
void RCCINIT_EXTI3(void);
void GPIOINIT_EXTI3(void);
void EXTIINIT_EXTI3(void);
void NVICINIT_EXTI3(void);

#endif
