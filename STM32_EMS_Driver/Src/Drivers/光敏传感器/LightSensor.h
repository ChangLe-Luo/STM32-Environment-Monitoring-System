#ifndef __LIGHTSENSOR_H
#define __LIGHTSENSOR_H

/***************根据自己需求更改****************/
#define LightSensor_READ_TIMES			          10    //传感器ADC循环读取次数（传感器采样率设置）
#define MODE	            	                   1	//模式选择	****模拟AO:	1	****数字DO:	0
#define	GPIO_Pin_x					      GPIO_Pin_1	//传感器输出IO口
#define ADC_Channel_x	               ADC_Channel_9
#define	GPIOx	           	 			       GPIOB
#define RCC_APB2Periph_GPIOx	RCC_APB2Periph_GPIOB
/*********************END**********************/

void LightSensor_Init(void);
uint16_t LightSensor_GetData(void);

#endif
