#include "stm32f10x.h"  // Device header
#include "AD.h"
#include "Delay.h"
#include <math.h>  // 包含数学函数声明
#include "LightSensor.h"

/**
  * @brief  根据MODE选择初始化对应io口的模式
  * @param	None
  * @retval	None
  */
void LightSensor_Init(void)
{
	#if MODE
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx,ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_x;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOx,&GPIO_InitStruct);
		
		AD_Init();
	}
	#else 
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx,ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//低电平有效，设置上拉输入防止误触
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_x;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOx,&GPIO_InitStruct);
	}
	#endif
}

/**
  * @brief	将接收到的空气质量转换成对应数值
  * @param  None
  * @retval 当MODE==1时，输出一个float类型的四位整数，小数点后两位（否则一个标志位，低电平有污染物）
  */
uint16_t LightSensor_GetData(void)
{
	#if MODE
	{
		uint16_t  tempData = 0;
	
		for (uint8_t i = 0; i < LightSensor_READ_TIMES; i++)
		{
			tempData += AD_GetValue(ADC_Channel_x);//求累加值
			Delay_ms(5);
		}
		tempData /= LightSensor_READ_TIMES;//对累加值求平均
		
		return tempData;
	}
	#else
	{
		uint8_t Temp = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin_x);//低电平表示亮
		return Temp;
	}
	#endif
}