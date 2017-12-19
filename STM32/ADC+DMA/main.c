
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include <stdio.h>

#define ADC1_DR_Address    ((uint32_t)0x4001244C)	 //ADC���ݼĴ����Ļ���ַ
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

USART_InitTypeDef USART_InitStructure;		  //���ڡ�ADC��DMA����

ADC_InitTypeDef ADC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;

__IO uint16_t ADCConvertedValue; // ע��ADCΪ12λģ��ת������ֻ��ADCConvertedValue�ĵ�12λ��Ч

void ADC_GPIO_Configuration(void)						  //ADC���ú���
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //PB1 ��Ϊģ��ͨ����������                         
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			     //�ܽ�1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			 //����ģʽ
  GPIO_Init(GPIOB, &GPIO_InitStructure);				 //GPIO��
}

static void Delay_ARMJISHU(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--);
}

void STM32_Shenzhou_COMInit(USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable UART clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  USART_Init(USART1, USART_InitStruct);	/* USART configuration */
  USART_Cmd(USART1, ENABLE);  /* Enable USART */
}

int main(void)
{
  u16 ADCConvertedValueLocal, Precent = 0, Voltage = 0;
  
  /* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled   */
  USART_InitStructure.USART_BaudRate = 115200;										  //���ڳ�ʼ������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  STM32_Shenzhou_COMInit(&USART_InitStructure);				    //ʹ��COM1
  
  /* ʹ��DMAʱ�� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	

  /* ʹ��ADC��GPIOCʱ��*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
  
  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);		  //����DMA1�ĵ�һͨ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;		  //DMA��Ӧ���������ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;   //�ڴ�洢����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;				  //DMA��ת��ģʽΪSRCģʽ����������Ƶ��ڴ�
  DMA_InitStructure.DMA_BufferSize = 1;		   //DMA�����С��1��
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//����һ�����ݺ��豸��ַ��ֹ����
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;	//�رս���һ�����ݺ�Ŀ���ڴ��ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //�����������ݿ��Ϊ16λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  //DMA�������ݳߴ磬HalfWord����Ϊ16λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   //ת��ģʽ��ѭ������ģʽ��
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA���ȼ���
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		  //M2Mģʽ����
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);          
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//������ת��ģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;		  //����ɨ��ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   //��������ת��ģʽ
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ADC�ⲿ���أ��ر�״̬
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   //���뷽ʽ,ADCΪ12λ�У��Ҷ��뷽ʽ
  ADC_InitStructure.ADC_NbrOfChannel = 1;	 //����ͨ������1��
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADCͨ���飬 ��9��ͨ�� ����˳��1��ת��ʱ��  */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_55Cycles5);

  /* ADC���ʹ�� */
  ADC_DMACmd(ADC1, ENABLE);	 
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);  //����ADC1

  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);	  //����У׼
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));  //�ȴ�����У׼���

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);		//��ʼУ׼
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));	   //�ȴ�У׼���
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//����ת����ʼ��ADCͨ��DMA��ʽ���ϵĸ���RAM����

  while (1)
  {
    ADCConvertedValueLocal = ADCConvertedValue;
    Precent = (ADCConvertedValueLocal*100/0x1000);	//����ٷֱ�
    Voltage = Precent*33;						  //3.3V�ĵ�ƽ�������Ч��ƽ

    printf("\r\n\n\n ARMJISHU.COM ADCConvertedValue is 0x%X, Precent is %d%%, Voltage is %d.%d%dV", 	 //������Ľ��д�ӡ
    ADCConvertedValueLocal, Precent, Voltage/1000, (Voltage%1000)/100, (Voltage%100)/10);
    Delay_ARMJISHU(8000000);
  }
}


PUTCHAR_PROTOTYPE
{
  USART_SendData(USART1, (uint8_t) ch);		  //����һ�ֽ�����

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}				//�ȴ��������

  return ch;
}

