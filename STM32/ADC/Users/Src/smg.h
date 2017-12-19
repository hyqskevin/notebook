#ifndef _smg_H
#define _smg_H
#include "stm32f10x.h"
#include "systick.h"
#define tub1 GPIO_Pin_6	  //PF6~PF9
#define tub2 GPIO_Pin_7
#define tub3 GPIO_Pin_8
#define tub4 GPIO_Pin_9
#define smg_duan (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)//PC0~PC7 
extern u8 smgduan[16];//一定要加上外部变量说明关键字extern,否则变异出错


void GPIOINIT_SMG(void);
void RCCINIT_SMG(void);
void smg_display(void);
void time_smg_run(void);
extern u16 n;

#endif
