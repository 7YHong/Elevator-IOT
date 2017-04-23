#include "includes.h"

void GPIO_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
//=============================================================================
//LED -> PC13
//=============================================================================
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}

void USART_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,ENABLE);
	/*
	*  USART1_TX -> PA9 , USART1_RX ->	PA10
	*  USART2_TX -> PA2 , USART2_RX ->	PA3
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
	USART_Init(USART2, &USART_InitStructure);

#if( USART1_RX_EN ==1)   //如果使能了串口1接收
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
#endif
#if( USART2_RX_EN ==1)   //如果使能了串口2接收
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ClearFlag(USART2,USART_FLAG_TC);
#endif

	USART_Cmd(USART1, ENABLE);
	USART_Cmd(USART2, ENABLE);
}

void NVIC_Configuration(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
#if( USART1_RX_EN ==1)   //如果使能了接收
	//配置串口中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                                     //选择中断分组2

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                              		//选择串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                           //抢占式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                                  //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                     //使能中断
	NVIC_Init(&NVIC_InitStructure);
#endif
#if( USART2_RX_EN ==1)   //如果使能了接收
	//配置串口中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                                     //选择中断分组2

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;                              		//选择串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                           //抢占式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                                  //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                     //使能中断
	NVIC_Init(&NVIC_InitStructure);
#endif
}

void SPI_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef    SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,    ENABLE );
	
	/*
	//	SPI_SCK -> PB13	SPI_MOSI->PB15
	*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  SPI_RCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL =  SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);

	SPI_Cmd(SPI2, ENABLE);
	//将RCK置为低电平
	GPIO_ResetBits(GPIOB,SPI_RCK_PIN);
}