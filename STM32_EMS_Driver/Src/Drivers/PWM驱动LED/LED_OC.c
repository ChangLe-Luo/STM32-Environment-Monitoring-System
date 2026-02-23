#include "ConFig.h"

void LEDOC_Init(void)
{
	PWM_Init();
}

void LEDOC_Light(float Compare)
{
	PWM_SetCompare3(Compare);
}