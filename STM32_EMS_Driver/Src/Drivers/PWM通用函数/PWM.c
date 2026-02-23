#include "stm32f10x.h" 				// Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//配置定时器时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//配置GPIO口时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置GPIO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//设置复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
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
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//选择在计数器小于CCR时的输出电平
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//选择输出状态
	TIM_OCInitStructure.TIM_Pulse = 0;//CCR，此处暂时不用在这里配置
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);//使能TIM2
}
void PWM_SetCompare3(uint16_t Compare)//封装单独设置CCR的函数，同时在这里定义参数compare
{
	TIM_SetCompare3(TIM2,Compare);//单独设置CCR值的函数
}