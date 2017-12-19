#ifndef _key_H
#define _key_H

#include "stm32f10x.h"
#define k_left GPIO_Pin_2
#define k_down GPIO_Pin_3
#define k_right GPIO_Pin_4
#define key_up GPIO_Pin_0
void GPIOINIT_KEY(void);
void RCCINIT_KEY(void);



#endif
