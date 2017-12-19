#include "buz.h"
void GPIOINIT_BUZ()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=buz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void RCCINIT_BUZ()
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
}
void sound()
{
	u16 i=10;
	while(i<=10)
	{
		GPIO_SetBits(GPIOB,buz);
		delay_ms(10);
		GPIO_ResetBits(GPIOB,buz);
		delay_ms(10);
		i--;	
	}
}
