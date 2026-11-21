#include "stm32f10x.h"                  // Device header
#include "PWM.h" 
	//先写电机初始化
	//这里其实初始化的是左侧电机部分
	

	
	/*@brief  初始化左侧电机
  * @param  无
  * @retval 无
  * @note   本工程中所有分左右侧的驱动，
			未标注那一侧默认为左侧

*/

	
	
void Motor_Init(void)
{
	PWM_Init ();
	//先初始化一下PWm
	//这里还要额外初始化控制方向的两个脚
	
		//这里a4a5链接an1和an2
	//bin1-b14    bin2-b15
	/*RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStructure_left;
	GPIO_InitStructure_left.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure_left.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure_left.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure_left);
	//上面这部分是a4a5
	
	*/
	
	//更改了一下，上面这些移到Motor_Right了，所以我先注释掉
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						
	
											
}

//接下来写速度函数


/*@brief  设置速度
  * @param  Speed，范围-100~100
			(这里相当于百分比，100满速）
  * @retval 无
  * @note   无

*/


void Motor_SetSpeed(int8_t Speed)
{
	//Speed属于-100到+100
	//用if处理正转反转
	if(Speed >=0)
	{
		
		//正转4是高电平
		

		GPIO_SetBits (GPIOA,GPIO_Pin_4);
		GPIO_ResetBits (GPIOA,GPIO_Pin_5);
		PWM_SetCompare3(Speed);
	}
	
	else 
	{
		//反转反之
		
		
		GPIO_ResetBits (GPIOA,GPIO_Pin_4);
		GPIO_SetBits (GPIOA,GPIO_Pin_5);
		PWM_SetCompare3(-Speed);
		//SetCompare3必须传正数，所以加一个负号
	}
	
}
