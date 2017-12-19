#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "stm32f10x_rcc.h"

void GPIIOINIT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
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

	TIM_OCInitTypeDef TIM_OCInitStructure;//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	//TIM3��ʱ����ʼ��
	TIM_TimeBaseInitStructure.TIM_Period = 0x000A;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0x0000;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, & TIM_TimeBaseInitStructure);

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,ENABLE);	//�ı�ָ���ܽŵ�ӳ��

	//PWM��ʼ��	  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM���ʹ��
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	//ע��˴���ʼ��ʱTIM_OC2Init������TIM_OCInit������������Ϊ�̼���İ汾��һ����

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܻ���ʧ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM3,ENABLE);//ʹ��TIMx����


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
	u8 fx=1;//����
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
		TIM_SetCompare2(TIM3, ti);//����TIMx����Ƚ�2�Ĵ���ֵ	
	}	
}
