#include "stm32f10x.h"                  // Device header
#include "AD.h"

void AD_Init(void)
{
	//开启ADC1&GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADCx,ENABLE);
	//开启ADCCLK时钟（核心时钟不共用避免噪声干扰）
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//初始化规则组通道//连续和扫描//数据对齐//单多ADC//外部触发
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//连续 转化 模式
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//无外部触发
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//ad单通道
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//扫描转化模式
	ADC_Init(ADCx,&ADC_InitStruct);
	//开启供电
	ADC_Cmd(ADCx,ENABLE);
	//校准
	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx) == SET);
	ADC_StartCalibration(ADCx);
	while(ADC_GetCalibrationStatus(ADCx) == SET);
}
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADCx,ADC_Channel,1,ADC_SampleTime_55Cycles5);//AD配置//选择通道//选择次序//采样时间
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);
	while(ADC_GetFlagStatus(ADCx,ADC_FLAG_EOC) == RESET);//此处不要设置成开始转化标志位
	return ADC_GetConversionValue(ADCx);
}