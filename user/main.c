#include "stm32f10x.h"                  // Device header
#include"Delay.h"
#include"OLED.h"
#include"MOTOR.h"
#include"KEY.h"
#include"LED.h"
#include"PWM.h"
#include"PWM_Right.h"
#include"Motor_Right.h"
#include"Turn.h"
#include"Sensor.h"

/*ok，周二，第一天，组装完成了小车
现在我要先写一个能让车正常跑起来的代码
这部分主要用的课程里的电机驱动，然后我就是改了一下端口
具体更改如下
我决定加一个led，用来指示小车的状态
按下按钮，电机启动，led亮
pwma-b11
ain2-b10
ain1-b1

改端口失败了，问题不在这里
在按键

我准备加一个按键控制小车的开关
但是我不明白为什么调换按键位置会出现问题
可能我的引脚哪里有问题吧
所以我重新布置了了一下接线
恢复了默认的电机驱动接线

周三：
我本来是打算启动两个电机驱动模块，但是我发现


我想到两种驱动方式
1.检测到黑线停下来，然后转弯到没有黑线，继续前进
两侧轮子速度不一样，来进行方向改变
2.或者后轮一直驱动，前轮转弯来改变


ok,我现在要先写一个能够前进的函数，放在motor里面

后记：此时动作基本都写完了，但是传感器一直没到！

*/
#define R_Min GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define R_Max GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)
#define L_Min GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)
#define L_Max GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)


uint8_t On_Off = 0;//这个是用来控制小车的，详情见后面小车按键控制
uint8_t KeyNum;
int8_t Speed;
int8_t Speed_Right;

extern uint16_t Turn_R_Fast; 
extern uint16_t Turn_L_Fast; 
extern uint16_t A;
extern uint16_t B;

int main(void)
{
	Sensor_Init();
	Key_Init();
	OLED_Init();
	Motor_Init ();
	Motor_Init_Right();
//	
//	OLED_ShowString(1,1,"Speed:");
//	OLED_ShowString(2,1,"Speed_R:");
	
	LED_Init_zhishideng();
	//这个是用来指示电机状态的
	//KeyNum= Key_GetNum();	
   

		
		
		
//	
//	if(KeyNum ==1){

//			break ;
//	}
//		
//		if(KeyNum ==2){
//	
//			
//			Motor_SetSpeed_Right(0);
//				Motor_SetSpeed(0);
//		LED_Off();
//		Motor_SetSpeed (0);
//		Motor_SetSpeed_Right(0);
//	On_Off=0;
//		}
//		
//	if(On_Off ==1)
//	{
	while(1){
		
		
		OLED_ShowSignedNum(1,7, R_Min   ,3);
		OLED_ShowSignedNum(1,7, R_Max   ,3);
		OLED_ShowSignedNum(1,7, L_Max    ,3);
		OLED_ShowSignedNum(1,7, L_Min   ,3);
		
				Motor_SetSpeed_Right(-0);
				Motor_SetSpeed(-0);
	
		Turn ();

			
			if (Turn_R_Fast==1)
        {
            // 右急转
			
			Motor_SetSpeed_Right(50);
			Motor_SetSpeed(-50);
			
		      // 急转时间
							
			     		// 急转后恢复直行
        
			Turn_R_Fast = 0;     // 避免重复急转
        }
        // 2. 左急转：A10+A11同时低→执行原地左急转
        if (Turn_L_Fast == 1)
        {
       
          
       Motor_SetSpeed_Right(50);
			Motor_SetSpeed(-50);
		  
            Turn_L_Fast = 0;      // 避免重复急转
        }
			
		 if (A == 1)
        {
       
          
       Motor_SetSpeed_Right(100);
			Motor_SetSpeed(-100);
		  Delay_ms (220);
            A = 0;     
        }
		
		 if (B == 1)
        {
       
          
       Motor_SetSpeed_Right(-100);
			Motor_SetSpeed(100);
		  Delay_ms (220);
            B = 0;     
        }
			
//	
//		
//		
//		OLED_ShowSignedNum(1,7,Speed ,3);
//		OLED_ShowSignedNum(2,9,Speed_Right ,3);
	}
}
//	while(1){}

//}

/*KeyNum= Key_GetNum();

		if(KeyNum ==1)
		{
			LED_On();
			
			Speed +=20;
			if(Speed >100)
			{
				Speed =-100;
				
			}
			
		}
		
		if(KeyNum ==2)
		{
			LED_Off();
			
			Speed +=20;
			if(Speed >100)
			{
				Speed =-100;
				
			}
			
		}
		Motor_SetSpeed (Speed );
		OLED_ShowSignedNum(1,7,Speed ,3);
	LED_Off();

		*/

