#ifndef __AD_H
#define __AD_H

/***************根据自己需求更改****************/
#define ADCx							   ADC1
#define RCC_APB2Periph_ADCx	RCC_APB2Periph_ADC1
/*********************END**********************/

void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);

#endif
