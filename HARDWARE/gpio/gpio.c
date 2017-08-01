#include "stm32f4xx.h"
void gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(GPIOE,&GPIO_InitStructure); 
	GPIO_SetBits(GPIOE,GPIO_Pin_1);
	GPIO_ResetBits(GPIOE,GPIO_Pin_2);
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
	GPIO_SetBits(GPIOE,GPIO_Pin_0);
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);
}