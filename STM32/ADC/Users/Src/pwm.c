#include "pwm.h"
void GPIOINIT_PWM()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_SetBits(GPIOB,GPIO_Pin_0);

}
void RCCINIT_PWM()
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}
void TIMEINIT_PWM()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	TIM_OCInitTypeDef TIM_OCInitStructure;//根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	//TIM3定时器初始化
	TIM_TimeBaseInitStructure.TIM_Period = 899;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseInitStructure);

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);	//改变指定管脚的映射

	//PWM初始化	  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
//	TIM_OCInitTypeDef TIM_OCInitStructure;//结构体定义也相当于定义变量，这个和定义u32是一样的，要放在最前面，否则会报警
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM输出使能
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	//注意此处初始化时TIM_OC2Init而不是TIM_OCInit，否则会出错。因为固件库的版本不一样。

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能或者失能TIMx在CCR2上的预装载寄存器
	
	TIM_Cmd(TIM3,ENABLE);//使能或者失能TIMx外设
}
