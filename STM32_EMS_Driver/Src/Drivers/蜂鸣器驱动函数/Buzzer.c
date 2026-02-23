#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitSture;
	GPIO_InitSture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSture.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitSture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSture);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);//让其置于高电平（低电平触发）
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}
void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}
void Buzzer_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12) == 0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
}