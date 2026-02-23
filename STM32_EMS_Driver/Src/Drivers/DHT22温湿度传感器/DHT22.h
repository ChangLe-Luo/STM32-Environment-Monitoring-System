#ifndef __DHT22_H
#define __DHT22_H

/***************根据自己需求更改****************/
#define	DHT22_DAT_Pin	                  GPIO_Pin_10 //DAT引脚修改 
#define	GPIOx	           	 			       GPIOA
#define RCC_APB2Periph_GPIOx	RCC_APB2Periph_GPIOA
/*********************END**********************/

void DHT22_Init(void);
uint8_t DHT22_Start(void);
void DHT22_Mode(uint8_t Mode);
uint8_t DHT22_ReadBit(void);
uint8_t DHT22_ReadByte(void);
void DHT22_ReadDate(float* Humidity,float* Temperature);

#endif
