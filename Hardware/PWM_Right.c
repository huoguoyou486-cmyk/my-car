#include "stm32f10x.h"                  // Device header





/*1.RCC开启时钟，把要用到TIM外设和GPIO的时钟打开
2.配置时基单元
3.配置输出比较单元
4.配置GPIO：把PWm对应的GPIO口，初始化为复用推挽输出的配置
			对应关系看引脚对应表
5.运行控制，启动计数器*/

/*void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
这四个是配置输出比较模块的


void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
给输出比较配默认值的

void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);
更改占空比*/

//这里是一个新的函数，用来控制右边的PWM




/*@brief  初始化PWM,输出波形，控制电机（右侧）
  * @param  无
  * @retval 无
  * @note   ARR=100-1;
			PSC预分频器36-1;
			tim3通道1

*/
void PWM_Init_Right(void )
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE );
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	

	TIM_InternalClockConfig(TIM3);	//将定时器 TIM2 的时钟源设置为内部时钟
	
	
	TIM_TimeBaseInitTypeDef TIN_TimeBaseInitStructure;
	//配置定时器 “时基参数” 的结构体
	
	
	TIN_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	//一般都选DIV1
	
	/*这个是分频的
	可以取
	#define TIM_CKD_DIV1                       ((uint16_t)0x0000)
#define TIM_CKD_DIV2                       ((uint16_t)0x0100)
#define TIM_CKD_DIV4                       ((uint16_t)0x0200)*/
	
	
	TIN_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	/*计数方式
	向上计数是从 0 计到自动重载值后归 0；向下计数是从自动重载值计到 0 后恢复原值；
	中央对齐是先向上计到自动重载值 - 1，再向下计到 1，交替循环。简单定时用向上计数；
	需反向计数场景选向下计数；要对称波形如电机控制，选中央对齐 。*/
	
	
	TIN_TimeBaseInitStructure.TIM_Period=100-1;
	//ARR自动重装器的值
	TIN_TimeBaseInitStructure.TIM_Prescaler=36-1;
	//PSC预分频器的值
	
	//这两个取值都要在0到65535之间
	
	
	TIN_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	//重复计数器的值，高级计时器才有，这里不需要，
	//所以直接给0
	
	
	TIM_TimeBaseInit(TIM3,&TIN_TimeBaseInitStructure);//初始化时基单元
	
	//配置输出比较单元
	
	TIM_OCInitTypeDef TIM_OCInitStructure;



	TIM_OCStructInit(&TIM_OCInitStructure);
//先给结构体成员都附上初始值，再改，不然有些可能现在没用到，后面用到出bug
	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	//就是这些东西
	//PPT那一页输出比较模式

	
	
TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	/*选高电平还是低电平
	*/
	
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	
	
	TIM_OCInitStructure.TIM_Pulse=0;
	//设置CCR寄存器值的
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	
	//最后一步，启动定时器
	TIM_Cmd (TIM3,ENABLE );
	

	
}


/*@brief  占空比设置函数，作用是动态修改 TIM3 通道 1的 PWM 占空比，
从而控制右侧电机的转速（我的右侧电机 PWM 是 TIM3_CH1）。
  * @param  无
  * @retval 无
  * @note   无
*/

void PWM_SetCompare1(uint8_t Compare){
		
		
	TIM_SetCompare1(TIM3, Compare);
		
		
}
