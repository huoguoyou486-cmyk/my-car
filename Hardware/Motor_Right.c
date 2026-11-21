#include "stm32f10x.h"                  // Device header
#include "PWM_Right.h" 


	/*@brief  初始化右侧电机
  * @param  无
  * @retval 无
  * @note   本工程中所有分左右侧的驱动，
			未标注那一侧默认为左侧

*/


void Motor_Init_Right(void)
{
	PWM_Init_Right();
	//先初始化一下PWm
	//这里还要额外初始化控制方向的两个脚
	
		//这里a4a5链接an1和an2
	//bin1-b14    bin2-b15
	

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStructure_right;
	GPIO_InitStructure_right.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure_right.GPIO_Pin=GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure_right.GPIO_Speed=GPIO_Speed_50MHz;
		
	GPIO_Init(GPIOB, &GPIO_InitStructure_right);	
}

//接下来写速度函数


/*@brief  设置速度
  * @param  Speed，范围-100~100
			(这里相当于百分比，100满速）
  * @retval 无
  * @note   无

*/


void Motor_SetSpeed_Right(int8_t Speed_Right)
{
	//Speed属于-100到+100
	//用if处理正转反转
	if(Speed_Right >=0)
	{
		
		//正传14是高电平
		
		GPIO_SetBits (GPIOB,GPIO_Pin_14);
		GPIO_ResetBits (GPIOB,GPIO_Pin_15);

	
		PWM_SetCompare1(Speed_Right);
	}
	
	else 
	{
		//反转反之
		
		GPIO_ResetBits (GPIOB,GPIO_Pin_14);
		GPIO_SetBits (GPIOB,GPIO_Pin_15);
		
		
		PWM_SetCompare1(-Speed_Right );
		//SetCompare3必须传正数，所以加一个负号
	}
	
}
