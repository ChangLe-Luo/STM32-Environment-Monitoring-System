#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//初始化A4A5引脚
	GPIO_InitTypeDef GPIO_InitStrucyure;
	GPIO_InitStrucyure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStrucyure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStrucyure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrucyure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//配置定时器时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//配置GPIO口时钟
	
/*	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//配置AFIO口时钟，因为AFIO在中断优先级配置中能选择线路，这里用于引脚复用
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//TIM2_CH1信号从PA0重映射到PA15，所以使用部分重映射1（见文档8.3.8表2）
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//因为PA15已经默认被设置为了端口调试模式，所以要使PA15端口调试失能
	*/
	GPIO_InitTypeDef GPIO_InitStructure;//配置GPIO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//设置复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);//选择内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;//初始化内部时钟
	TIM_TimBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimBaseStructure.TIM_Period =  100 - 1 ;//ARR
	TIM_TimBaseStructure.TIM_Prescaler = 72 - 1 ;//PSC
	TIM_TimBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimBaseStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;//初始化输出比较器
	TIM_OCStructInit(&TIM_OCInitStructure);//结构体初始化（部分结构体参数是悬空状态，因为现在用的是中级计时器，部分结构体参数无用）
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择输出比较的模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//选择在计数器小于CCR时的输出电平
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//选择输出状态
	TIM_OCInitStructure.TIM_Pulse = 0;//CCR，此处暂时不用在这里配置
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);//使能TIM2
}
void Motor_Setspeed(int16_t Speed) //范围-100到+100
{
	if(Speed>=0)
	{
		GPIO_SetBits(GPIOA , GPIO_Pin_5);
		GPIO_ResetBits(GPIOA , GPIO_Pin_4);//操作正反只需要设置高低电平
		TIM_SetCompare2(TIM2,Speed);//传参
	}
	if(Speed<0)
	{
		GPIO_SetBits(GPIOA , GPIO_Pin_4);
		GPIO_ResetBits(GPIOA , GPIO_Pin_5);
		TIM_SetCompare2(TIM2,Speed);
	}
}