#include "ConFig.h"
#include "EMS.h"
float AQ;
uint16_t Light;
float Humidity = 0;
float Temperature = 0;


void EMS_Init(void)
{
	AD_Init();
	Buzzer_Init();
	LightSensor_Init();
	OLED_Init();
	MQ135_Init();
	DHT22_Init();
	Servo_Init();
	Motor_Init();
	LEDOC_Init();
}

void EMS_Update(void)//定义全局变量存储数据
{
	
	AQ = MQ135_GetPPM();
	Light = LightSensor_GetData();
	DHT22_ReadDate(&Humidity,&Temperature);

}

void EMS_Response(void)
{
	switch(AQ_Degree())
	{
		case 1:
			Motor_Setspeed(-50);//空气质量不好就抽气//温度高就吹
			//Servo_Angle(90);//打开窗户
			Buzzer_ON();
			Delay_ms(200);
			Buzzer_OFF();
			Delay_ms(100);
			Buzzer_ON();
			Delay_ms(200);
			Buzzer_OFF();
			Delay_ms(100);
			break;
		case 2:
			Motor_Setspeed(-25);
			//Servo_Angle(45);
			Buzzer_ON();
			Delay_ms(200);
			Buzzer_OFF();
			Delay_ms(100);
			Buzzer_ON();
			Delay_ms(200);
			Buzzer_OFF();
			Delay_ms(100);
			break;
		case 3:
		case 4:
		case 5:
			Motor_Setspeed(0);
			Servo_Angle(0);
			break;
	}
	
	LEDOC_Light(((float)Light/3500*100)-50);
}

void EMS_Display(void)//通过转运的全局变量显示
{
	switch(AQ_Degree())
	{
		case 1:
			OLED_ShowString(2,5,"VeryBad ");
			break;
		case 2:
			OLED_ShowString(2,5,"Bad     ");
			break;
		case 3:
			OLED_ShowString(2,5,"Medium  ");
			break;
		case 4:
			OLED_ShowString(2,5,"Good    ");
			break;
		case 5:
			OLED_ShowString(2,5,"VeryGood");
			break;
	}
	switch(Light_Degree())
	{
		case 1:
			OLED_ShowString(1,7,"VeryDark ");
			break;
		case 2:
			OLED_ShowString(1,7,"Dark     ");
			break;
		case 3:
			OLED_ShowString(1,7,"Medium   ");
			break;
		case 4:
			OLED_ShowString(1,7,"Bright   ");
			break;
		case 5:
			OLED_ShowString(1,7,"VeryBright");
			break;
	}
	OLED_ShowNum(3,6,Temperature,3);
	OLED_ShowNum(3,10,(uint16_t)(Temperature*100)%100,2);
	OLED_ShowNum(4,6,Humidity,3);
	OLED_ShowNum(4,10,(uint16_t)(Humidity*100)%100,2);

}

uint8_t AQ_Degree(void)
{
	if(AQ > 30) return 1;            //很差 
	if(AQ <= 1000 && AQ > 100) return 2; //较差（开启行为）
	if(AQ <= 100 && AQ > 50) return 3;	//中等
	if(AQ <= 50 && AQ > 20) return 4;	//良好（关闭行为）
	if(AQ <= 20) return 5;				//很好
}

uint8_t Light_Degree(void)
{
	if(Light > 3500) return 1;                 //很差 
	if(Light <= 3500 && Light > 1500) return 2;  //较差（开启行为）
	if(Light <= 1500 && Light > 700) return 3;	//中等
	if(Light <= 700 && Light > 200) return 4;	//良好（关闭行为）
	if(Light <= 200) return 5;				    //很好
}