#ifndef _led_H
#define _led_H
#define led (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7) 
#include "stm32f10x.h"
void GPIOINIT_LED(void);
void RCCINIT_LED(void);

#endif
