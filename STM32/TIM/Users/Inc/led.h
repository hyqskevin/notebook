#ifndef __LED_H_
#define __LED_H_

#include"stm32f10x.h"
/*************定义所使用的IO口**************/
#define RCC_LED 	RCC_APB2Periph_GPIOB	
#define GPIO_LED 	GPIOB
/**************8位LED的IO口定义************/
#define PIN_LED 	(GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12\
|GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)
/**************单独LED的IO口定义***********/
#define PIN_LED1 	GPIO_Pin_15

/**********打开IO时钟和初始化GPIO**********/
void LED_Init(void);
/**********设置八位LED的状态***************/
void LED_Sets(uint8_t data);
/**********LED打开或者关闭的函数 **********/
#define LED1(a) if(a)\
GPIO_WriteBit(GPIO_LED, PIN_LED1, Bit_SET);\
else GPIO_WriteBit(GPIO_LED, PIN_LED1, Bit_RESET);

#endif
