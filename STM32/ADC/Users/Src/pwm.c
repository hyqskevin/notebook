#include "pwm.h"
void GPIOINIT_PWM()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
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

	TIM_OCInitTypeDef TIM_OCInitStructure;//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	//TIM3��ʱ����ʼ��
	TIM_TimeBaseInitStructure.TIM_Period = 899;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseInitStructure);

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);	//�ı�ָ���ܽŵ�ӳ��

	//PWM��ʼ��	  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
//	TIM_OCInitTypeDef TIM_OCInitStructure;//�ṹ�嶨��Ҳ�൱�ڶ������������Ͷ���u32��һ���ģ�Ҫ������ǰ�棬����ᱨ��
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM���ʹ��
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	//ע��˴���ʼ��ʱTIM_OC2Init������TIM_OCInit������������Ϊ�̼���İ汾��һ����

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܻ���ʧ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM3,ENABLE);//ʹ�ܻ���ʧ��TIMx����
}
