#include "timer.h"

float a;
//定时器2初始化
void timer2_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; 
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM2,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//定时器3初始化
void timer3_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); 
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; 
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM3,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//定时器2中断处理
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) 
	{
		//printf("zzz\r\n");
		//do something
		if(pid_running)
		{
			pid_control_refresh();
			
		}
			
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  
}

//定时器3中断处理
//u16 flag=0;
void TIM3_IRQHandler(void)
{
	/*if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) 
	{
		if(flag==0)
		{
		  GPIO_ResetBits(GPIOE,GPIO_Pin_3);
			flag=1;
		}
		else if(flag==1)
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_3);
			flag=0;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update); */
}