#include "ConFig.h"

int main(void)
{	
	EMS_Init();
	OLED_ShowString(1,1,"Light:");
	OLED_ShowString(3,1,"Temp:000.0C");
	OLED_ShowString(4,1,"Humi:000.0%");
	OLED_ShowString(2,1,"AQI:");
	while (1)
	{
		EMS_Update();
		EMS_Response();
		EMS_Display();
		Delay_ms(2000);
	//1.更新数据
	//2.报警处理
    //3.显示更新	
	}
}		
