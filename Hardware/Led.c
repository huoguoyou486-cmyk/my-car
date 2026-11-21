#include "stm32f10x.h"                  // Device header



/*@brief  点亮led，指示电机工作状态
  * @param  无
  * @retval 无
  * @note   无

*/




void LED_Init_zhishideng(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE );
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
	GPIO_SetBits (GPIOA ,GPIO_Pin_7);
}

void LED_On(void)
{
	GPIO_ResetBits (GPIOA ,GPIO_Pin_7 );
	
}


void LED_Off(void)
{
	GPIO_SetBits (GPIOA ,GPIO_Pin_7 );
	
}






