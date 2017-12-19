#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dac.h"
#include "misc.h"
#include "stdio.h"

void RCCINIT(void)		 //系统的时钟初始化
{
    SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
}

void GPIOINIT(void)			 //端口的初始化配置
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
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;//模拟量输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);//输出高
}

void NVICINIT(void)			 //中断模式的初始化配置
{
  NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void USARTINIT(void)			//串口的初始化配置
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

void DACINIT(void)			 //DAC初始化配置
{
   DAC_InitTypeDef DAC_InitStructure;

   DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;//不使用出发功能
   DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用三角波
   //屏蔽 幅值设置
   DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
   //关闭缓存
   DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable;

   DAC_Init(DAC_Channel_1,&DAC_InitStructure);//初始化DAC通道1

   DAC_Cmd(DAC_Channel_1,ENABLE);//使能DAC1

   DAC_SetChannel1Data(DAC_Align_12b_R,0);//12位 右对齐 写0数据
}

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}


void delayms(u16 nms)
{
     //注意 delay_ms函数输入范围是1-1864
	 //所以最大延时为1.8秒

	 u32 temp;
	 SysTick->LOAD = 5000*nms;
	 SysTick->VAL=0X00;//清空计数器
	 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	 do
	 {
	  temp=SysTick->CTRL;//读取当前倒计数值
	 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 SysTick->CTRL=0x00; //关闭计数器
	 SysTick->VAL =0X00; //清空计数器
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
			DAC_SetChannel1Data(DAC_Align_12b_R,da);//12位 右对齐 PA4 端口输出
			
			printf("da=%fv\n",3.3*da/4096);
			delayms(1000);//间隔5秒输出一个电压
		}
	}	
}
