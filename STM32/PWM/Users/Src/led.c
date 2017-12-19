#include "led.h"
/****************************************************************************
* Function Name  : LED_Init
* Description    : Configures the used GPIO of LED .
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PIN_LED;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*打开LED使用的GPIO的时钟使能*/
	RCC_APB2PeriphClockCmd(RCC_LED, ENABLE);

	/*初始化相应的GPIO*/
	GPIO_Init(GPIO_LED, &GPIO_InitStructure);	 //初始化GPIO_LED

}
/****************************************************************************
* Function Name  : LED_Sets
* Description    : 设置LED的状态：因我们只是用了8位，而STM32一次得设置16位，所
*以先读取在写入。
* Input          : data 
* Output         : None
* Return         : None
****************************************************************************/

void LED_Sets(uint8_t data)
{
	uint16_t setValue;

	setValue = GPIO_ReadOutputData(GPIO_LED);
	setValue &= 0x00ff;//我们使用的是16位中的高8位					
	setValue |= (uint16_t)data << 8;

	GPIO_Write(GPIO_LED,setValue);
}
