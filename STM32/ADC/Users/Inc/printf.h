#ifndef _printf_H
#define _printf_H
#include "stm32f10x.h"
#include "stdio.h"
int fputc(int ch,FILE *p);
void GPIOINIT_PRINTF(void);
void RCCINIT_PRINTF(void);
void NVICINIT_PRINTF(void);
void USARTINIT_PRINTF(void);


#endif
