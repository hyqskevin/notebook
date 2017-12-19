#include "hwjs.h"
u32 hw_jsm;
u8  hw_jsbz;
void EXTI_Configuration_HW(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;

	EXTI_ClearITPendingBit(EXTI_Line15);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource15); 

	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;

	EXTI_Init(&EXTI_InitStructure);
}
void NVIC_Configuration_HW(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void GPIOINIT_HW()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;//红外接收
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
}
void RCCINIT_HW()
{
	SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}
u8 HW_jssj(void)
{
	u8 t=0;

	while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)==1)//高电平
	{
		t++;
		delay_us(20);

		if(t>=250) return t;//超时溢出
	}

	return t;
}
