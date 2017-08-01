#include "my_usart.h"

u8 TxBuffer[256];
u8 TxCounter=0;
u8 count=0; 

//串口2初始化
void usart2_init(u32 baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3
	  
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure); 
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);  
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);        
  USART_ClearFlag(USART2,USART_FLAG_TC);

  USART_Cmd(USART2, ENABLE);
	
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

//串口3初始化
void usart3_init(u32 baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10; //GPIOB11与GPIOB10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化GPIOB11，GPIOB10
	  
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure); 
	USART_ITConfig(USART3, USART_IT_TXE, DISABLE);  
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);        
  USART_ClearFlag(USART3,USART_FLAG_TC);

  USART_Cmd(USART3, ENABLE);
	
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

//串口2中断处理，接收传感器数据
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {   
    USART_SendData(USART2, TxBuffer[TxCounter++]); 
    if(TxCounter == count) 
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
		}
    USART_ClearITPendingBit(USART2, USART_IT_TXE); 
  }
	else if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
		CopeSerialData((unsigned char)USART2->DR);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
	USART_ClearITPendingBit(USART2,USART_IT_ORE);
}

//串口3中断处理
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  {   
    USART_SendData(USART3, TxBuffer[TxCounter++]); 
    if(TxCounter == count) 
		{
			USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
		}
    USART_ClearITPendingBit(USART3, USART_IT_TXE); 
  }
	else if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
		CopeSerialData1((unsigned char)USART3->DR);
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
  }
	USART_ClearITPendingBit(USART3,USART_IT_ORE);
}
	
