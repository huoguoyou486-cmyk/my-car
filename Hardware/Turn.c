#include "stm32f10x.h"                  // Device header
#include "Motor.h"  
#include "Motor_Right.h" 
#include "Delay.h" 

uint16_t A=0;
uint16_t B=0;

//ok,这个是用来写转弯函数的，我打算分成两种转弯方式

//一种是慢速转弯，用来对应弯道
//一种是快速转弯，用来对应直角弯

//后更正：将急速转弯作为中断放到了Sensor.c里面
//正常转弯放到了turn.c里面


#define R_Min GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define R_Max GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)
#define L_Min GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)
#define L_Max GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)
//用宏定义简化，直观化
//R_Max就是最右边的那个探头，以此类推



/*@brief  设置转弯函数
  * @param  无
  * @retval 无
  * @note   无

*/


void Turn(void )
{
	
	//Motor_SetSpeed_Right(60);
			//	Motor_SetSpeed(60);
	
	
	//这里的代码比较直观，不再写注释了
	
	//这里是直行的情况
	
	
	
	
	
	
	if(L_Min==0&&L_Max==1&&R_Min==0&&R_Max==1)
	{
				Motor_SetSpeed_Right(-60);
				Motor_SetSpeed(-60);
		
		
	}
	
	//这个是右边的传感器识别到黑线了，要往右微调
	
	if(L_Min==1&&L_Max==1&&R_Min==0&&R_Max==1)
	{
				Motor_SetSpeed_Right(100);
				Motor_SetSpeed(-100);
			
	}
	
	if(L_Min==0&&L_Max==1&&R_Min==1&&R_Max==1)
	{
				Motor_SetSpeed_Right(-100);
				Motor_SetSpeed(100);
	
			
	}
	
		if(L_Min==1&&L_Max==1&&R_Min==1&&R_Max==0)
	{
				Motor_SetSpeed_Right(0);
				Motor_SetSpeed(-60);
		Delay_ms (100);
	}
	
	if(L_Min==1&&L_Max==0&&R_Min==1&&R_Max==1)
	{
		Motor_SetSpeed_Right(-60);
				Motor_SetSpeed(-60);
	
			
	}
	
	
		if(L_Min==0&&L_Max==0&&R_Min==0&&R_Max==1)
	{
				
	B=1;
	}
	
	
		if(L_Min==0&&L_Max==1&&R_Min==0&&R_Max==0)
	{
				
	A=1;
	}
	
	
	
//	if(L_Min==1&&L_Max==1&&R_Min==1&&R_Max==0)
//	{
//				Motor_SetSpeed_Right(-0);
//				Motor_SetSpeed(-100);

//	}
//	
//	if(L_Min==1&&L_Max==0&&R_Min==1&&R_Max==1)
//	{
//				Motor_SetSpeed_Right(-100);
//				Motor_SetSpeed(-0);
//		
//	
//	}
//	
	
}
