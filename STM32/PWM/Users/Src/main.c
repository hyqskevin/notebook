#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "stm32f10x_rcc.h"

void GPIIOINIT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void RCCINIT()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}

void TIMINIT()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	TIM_OCInitTypeDef TIM_OCInitStructure;//根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	//TIM3定时器初始化
	TIM_TimeBaseInitStructure.TIM_Period = 0x000A;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0x0000;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, & TIM_TimeBaseInitStructure);

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,ENABLE);	//改变指定管脚的映射

	//PWM初始化	  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM输出使能
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	//注意此处初始化时TIM_OC2Init而不是TIM_OCInit，否则会出错。因为固件库的版本不一样。

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能或者失能TIMx在CCR2上的预装载寄存器
	
	TIM_Cmd(TIM3,ENABLE);//使能TIMx外设


}

void delay(u32 i)
{
	while(i--);
}
void delayus(u32 i)
{
	u32	temp;
	SysTick->LOAD=9*i;
	SysTick->CTRL=0X01;
	SysTick->VAL=0X00;
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&(!(temp&(1<<16))));
	SysTick->CTRL=0X00;
	SysTick->VAL=0X00;
}

void delayms(u32 i)
{
	u32	temp;
	SysTick->LOAD=9000*i;
	SysTick->CTRL=0X01;
	SysTick->VAL=0X00;
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&(!(temp&(1<<16))));
	SysTick->CTRL=0X00;
	SysTick->VAL=0X00;
}

int main()
{
	u8 fx=1;//方向
	u32 ti=0;
	RCCINIT();
	GPIIOINIT();
	TIMINIT();
	
	while(1)
	{
		delay(10);
		if(fx==1)		
		{
			ti++;
			if(ti>300)		
			{
				fx=0;
			}
		}
		else
		{
			ti--;
			if(ti==0)
			{
				fx=1;
			}
		}
		TIM_SetCompare2(TIM3, ti);//设置TIMx捕获比较2寄存器值	
	}	
}
