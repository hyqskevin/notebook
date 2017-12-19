#include "time.h"
void RCCINIT_TIME()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}
void NVICINIT_TIME()
{
	
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);		
}
void TIMINIT_TIME()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

	TIM_TimeBaseInitStructure.TIM_Period = 2000;//如果等于2000的话是定时1s
	TIM_TimeBaseInitStructure.TIM_Prescaler = 35999;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_Cmd(TIM3,ENABLE); //使能或者失能TIMx外设
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );	//使能或者失能指定的TIM中断			
}
