#ifndef _hwjs_H
#define _hwjs_H
#include "stm32f10x.h"
#include "systick.h"
void EXTI_Configuration_HW(void);
void GPIOINIT_HW(void);
void RCCINIT_HW(void);
u8 HW_jssj(void);
void NVIC_Configuration_HW(void);
extern u32 hw_jsm;
extern u8  hw_jsbz;



#endif
