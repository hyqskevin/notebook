#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dac.h"
#include "misc.h"
#include "stdio.h"

void RCCINIT(void)		 //ϵͳ��ʱ�ӳ�ʼ��
{
    SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
}

void GPIOINIT(void)			 //�˿ڵĳ�ʼ������
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;//ģ��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);//�����
}

void NVICINIT(void)			 //�ж�ģʽ�ĳ�ʼ������
{
  NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void USARTINIT(void)			//���ڵĳ�ʼ������
{
  USART_InitTypeDef  USART_InitStructure;

	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(USART1,&USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
}

void DACINIT(void)			 //DAC��ʼ������
{
   DAC_InitTypeDef DAC_InitStructure;

   DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;//��ʹ�ó�������
   DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�����ǲ�
   //���� ��ֵ����
   DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
   //�رջ���
   DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable;

   DAC_Init(DAC_Channel_1,&DAC_InitStructure);//��ʼ��DACͨ��1

   DAC_Cmd(DAC_Channel_1,ENABLE);//ʹ��DAC1

   DAC_SetChannel1Data(DAC_Align_12b_R,0);//12λ �Ҷ��� д0����
}

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}


void delayms(u16 nms)
{
     //ע�� delay_ms�������뷶Χ��1-1864
	 //���������ʱΪ1.8��

	 u32 temp;
	 SysTick->LOAD = 5000*nms;
	 SysTick->VAL=0X00;//��ռ�����
	 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	 do
	 {
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 SysTick->CTRL=0x00; //�رռ�����
	 SysTick->VAL =0X00; //��ռ�����
}

int main()
{
	u8 i;
	float da;
	RCCINIT();
	GPIOINIT();
	NVICINIT();
	USARTINIT();
	DACINIT();
	while(1)
	{
		da=0;
		for(i=0;i<=10;i++)	
		{
			da=i*400;
			DAC_SetChannel1Data(DAC_Align_12b_R,da);//12λ �Ҷ��� PA4 �˿����
			
			printf("da=%fv\n",3.3*da/4096);
			delayms(1000);//���5�����һ����ѹ
		}
	}	
}
