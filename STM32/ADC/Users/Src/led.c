#include "led.h"
void GPIOINIT_LED()	  //端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Pin=led;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_SetBits(GPIOC,led); //led熄灭初始化	
}
void RCCINIT_LED() //系统初始化
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
}
