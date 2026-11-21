#include "stm32f10x.h"                  // Device header
#include "Delay.h"  
#include "stm32f10x.h"                  // Device header



/*1，RCC开启时钟
2.选择时基单元的时钟源（内部时钟模式、外部时钟模式1、2，
3.配置时基单元（用一个结构体就可以配置好了）
4.（使能更新中断）配置输出中断控制，允许更新中断输出到NVIC
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
5.配置NVIC，在NVIC中打开定时器中断的通道，并分配一个优先级
6.运行控制



*/


//void TIM_DeInit(TIM_TypeDef* TIMx);//恢复初始配置
//void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
//时基单元初始化（第三步）
//两个参数，第一个是选择定时器，第二个是结构体，包含了配置时基单元的一些参数

//这个用来初始化定时器


//void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
//把结构体变量赋一个默认值

/*void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
使能计数器的，对应第六步*/


/*void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
使能外设的中断输出*/




/*void TIM_InternalClockConfig(TIM_TypeDef* TIMx);

//这个是内部时钟

void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);
				   
这六个是选择时钟的函数*/



/*void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
单独写预分频值的*/

/*void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);
用来改变计数器的记数模式*/

//void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
//预装不预装TIMx_ARR

/*void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter);
给计数器写入一个值




void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload);
给自动重装器写入一个值



uint16_t TIM_GetCounter(TIM_TypeDef* TIMx);
获取当前计数器的值，这个的返回值就是当前计数器的值


uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
同上，只不过是预分频器的

FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);
用来获取标志位和清楚标志位的

*/



//1.配置RCC，把设计的外设的时钟打开
//2.配置GPIO口选择输入模式
//3,配置AFIO，连接到后面的EXTI
//4.配置EXTI，选择边沿触发方式，比如上升沿，下降沿，双边沿/中断响应，事件响应
//5.配置NVIC选择合适的优先级

//这个传感器是识别到黑线-无反射-返回低电平
//有反射-返回高电平

//GPIO_ReadInputDataBit()==1;
//高电平，没识别到

//先写好这几个放这

//GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
//GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9);
//GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10);
//GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);

//初始化四个传感器输入的引脚




#define R_Min GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define R_Max GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)
#define L_Min GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)
#define L_Max GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)
//通过宏定义更直观感受传感器对应端口
//A8-X1,A9-X2,A10-X3,A11-X4






//如果一直在while1里检查红外灯状态的话
//课程里说会占用cpu较多资源
//我打算写一个外部中断
//当遇到直角弯的时候优先执行这个外部中断


uint16_t Turn_R_Fast=0; 
uint16_t Turn_L_Fast=0; 
//这两个是触发中断后的改变的变量
//本来我是将转弯控制放到了中断函数里面
//但这样其实是不太正确的
//中断里面执行的东西要快，不要在中断里执行很长的动作
//其实这时候我已经放弃这个使用中断的想法了

//但后来我有了一个新的idea
//我可以在中断里面只执行改变一个变量的操作
//然后将转弯放在检测到该变量变化后执行的函数里面
//就能避免这个问题了

/**
  * @brief  初始化传感器，同时设置两个中断，
			用来应对直角弯的情况，触发右直转和左直转
  * @param  无
  * @retval 无
  * @note   并不是在中断函数里面执行转弯操作，
			而是触发中断后，改变一个变量然后这个变量去触发急转弯
  */

void Sensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9
								 |GPIO_Pin_11 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//上面是初始化端口
	
	
		//配置AFIO的中断选择器
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource10);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);
	//给 EXTI 中断线指定唯一的 GPIO 引脚
	//用的是GPIOA，所以是GPIO_PortSourceGPIA
	
	
	//4.配置EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line8|EXTI_Line9|EXTI_Line10|EXTI_Line11;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//一个中断模式，一个事件模式
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//函数注释写错了，应该是EXTITrigger_TypeDef
	//上升沿触发，下降沿触发，上升下降沿都触发‘			
	EXTI_Init(&EXTI_InitStructure);
	
	
	
	//5.配置NVIC
	//配置中断之前
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//先指定一下中断的分组
	//分组这个代码整个芯片只有一个，如果其他模块也有，那就都设置成一样的
	//或者把这个代码放在主函数的最开始，模块里就不用再分组了。
	
	
	//配置第一个中断通道，这个通道是用来右急转的
	//这里的8，9都是右边的传感器
	
	//再初始化一下NVIC
	NVIC_InitTypeDef NVIC_InitStructure_R;
	
	NVIC_InitStructure_R.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStructure_R.NVIC_IRQChannelCmd=ENABLE ;
	NVIC_InitStructure_R.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure_R.NVIC_IRQChannelSubPriority=3;
	
	
	
	NVIC_Init(&NVIC_InitStructure_R);


//配置第二个中断通道，这个通道是用来左急转的
	//这里的10，11都是右边的传感器
	
	//再初始化一下NVIC
	NVIC_InitTypeDef NVIC_InitStructure_L;
	
	NVIC_InitStructure_L.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure_L.NVIC_IRQChannelCmd=ENABLE ;
	NVIC_InitStructure_L.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure_L.NVIC_IRQChannelSubPriority=3;
	
	
	
	NVIC_Init(&NVIC_InitStructure_L);


}


//固定的中断函数
	void EXTI9_5_IRQHandler(void)
{
	
	Delay_us(20);
	//ms太长了，改成了us
	//b站弹幕里说的要消除抖动小车，还说会回来感谢他的
	
	// 检测A8、A9是否同时为0（都检测到黑线）
	if (R_Max==0)
	{
		
	Turn_R_Fast=1;
		
	}
	// 清除对应中断标志位
	if(EXTI_GetITStatus(EXTI_Line8)==SET) 
		EXTI_ClearITPendingBit(EXTI_Line8);
	if(EXTI_GetITStatus(EXTI_Line9)==SET) 
		EXTI_ClearITPendingBit(EXTI_Line9);
}

// 处理A10、A11（EXTI_Line10~11）
	void EXTI15_10_IRQHandler(void)
{

	Delay_us(20);
	
	//b站弹幕里说的要消除抖动小车，还说会回来感谢他的
	//消抖：while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0){Delay_us(20);}
	// 检测A10、A11是否同时为0（都检测到黑线）
	if (L_Max==0)
	{
		Turn_L_Fast  =1;   // 置位左急转标志
		
	}
	
	// 清除对应中断标志位
	if(EXTI_GetITStatus(EXTI_Line10) == SET) 
		EXTI_ClearITPendingBit(EXTI_Line10);
	if(EXTI_GetITStatus(EXTI_Line11) == SET) 
		EXTI_ClearITPendingBit(EXTI_Line11);
}





