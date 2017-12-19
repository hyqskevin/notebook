#include "stm32f10x.h"
void delay(u32 i)
{
	while(i--);
}

void delayus(u32 i)
{
	u32 temp;
	SysTick->LOAD=9*i;		 //设置重装数值, 72MHZ时
	SysTick->CTRL=0X01;		 //使能，减到零是无动作，采用外部时钟源
	SysTick->VAL=0;		   	 //清零计数器
	do
	{
		temp=SysTick->CTRL;		   //读取当前倒计数值
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //等待时间到达
	SysTick->CTRL=0;	//关闭计数器
	SysTick->VAL=0;		//清空计数器
}

void delayms(u32 i)
{
	u32 temp;
	SysTick->LOAD=9000*i;	  //设置重装数值, 72MHZ时
	SysTick->CTRL=0X01;		//使能，减到零是无动作，采用外部时钟源
	SysTick->VAL=0;			//清零计数器
	do
	{
		temp=SysTick->CTRL;	   //读取当前倒计数值
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//等待时间到达
	SysTick->CTRL=0;	//关闭计数器
	SysTick->VAL=0;		//清空计数器
}


void GPIOINIT()
{
	//对GPIO端口初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

void RCCINIT()			//系统时钟初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

}

void NVICINIT()			//中断模式的配置
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

		
}

void TIMINIT()				                    //TIM的初始化配置
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

	TIM_TimeBaseInitStructure.TIM_Period = 2000; //等于2000的话是定时1s
	TIM_TimeBaseInitStructure.TIM_Prescaler = 35999;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_Cmd(TIM3,ENABLE);                       //使能或者失能TIMx外设
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );	//使能或者失能指定的TIM中断

			
}
int main()
{
	RCCINIT();	  //系统时钟的初始化
	GPIOINIT();   // 端口的初始化
	TIMINIT();	  // 定时器的初始化
	NVICINIT();	  // 中断模式的初始化	
	while(1);		
}
