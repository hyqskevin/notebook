#include "stm32f10x.h"
void delay(u32 i)
{
	while(i--);
}

void delayus(u32 i)
{
	u32 temp;
	SysTick->LOAD=9*i;		 //������װ��ֵ, 72MHZʱ
	SysTick->CTRL=0X01;		 //ʹ�ܣ����������޶����������ⲿʱ��Դ
	SysTick->VAL=0;		   	 //���������
	do
	{
		temp=SysTick->CTRL;		   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //�ȴ�ʱ�䵽��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}

void delayms(u32 i)
{
	u32 temp;
	SysTick->LOAD=9000*i;	  //������װ��ֵ, 72MHZʱ
	SysTick->CTRL=0X01;		//ʹ�ܣ����������޶����������ⲿʱ��Դ
	SysTick->VAL=0;			//���������
	do
	{
		temp=SysTick->CTRL;	   //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//�ȴ�ʱ�䵽��
	SysTick->CTRL=0;	//�رռ�����
	SysTick->VAL=0;		//��ռ�����
}


void GPIOINIT()
{
	//��GPIO�˿ڳ�ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

void RCCINIT()			//ϵͳʱ�ӳ�ʼ��
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

}

void NVICINIT()			//�ж�ģʽ������
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

		
}

void TIMINIT()				                    //TIM�ĳ�ʼ������
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

	TIM_TimeBaseInitStructure.TIM_Period = 2000; //����2000�Ļ��Ƕ�ʱ1s
	TIM_TimeBaseInitStructure.TIM_Prescaler = 35999;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_Cmd(TIM3,ENABLE);                       //ʹ�ܻ���ʧ��TIMx����
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );	//ʹ�ܻ���ʧ��ָ����TIM�ж�

			
}
int main()
{
	RCCINIT();	  //ϵͳʱ�ӵĳ�ʼ��
	GPIOINIT();   // �˿ڵĳ�ʼ��
	TIMINIT();	  // ��ʱ���ĳ�ʼ��
	NVICINIT();	  // �ж�ģʽ�ĳ�ʼ��	
	while(1);		
}
