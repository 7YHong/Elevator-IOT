#include "includes.h"

// 重定向printf
int fputc(int ch, FILE *f) {
	//USART_PC->SR;  //USART_GetFlagStatus(USART1, USART_FLAG_TC) 解决第一个字符发送失败的问题
	USART_SendData(USART_PC, (unsigned char) ch);// USART1 可以换成 USART2 等
	while (!(USART_PC->SR & USART_FLAG_TXE));
	return (ch);
}
// 以上为重定向printf
//字符串发送程序
void Uprint(USART_TypeDef* USARTx,unsigned char * str) {
	while(*str) {
		USART_SendData(USARTx, *str++);
		//等待传输结束
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	}
}
//以上为字符串发送程序

#if( USART1_RX_EN ==1)   //如果使能了串口2接收
void USART1_IRQHandler(void) {
	u8 res;
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET) {
		//将数据发送到PC
		res=USART_ReceiveData(USART1);
		USART_SendData(USART2,res);
	}
}
#endif

#if( USART2_RX_EN ==1)   //如果使能了串口2接收
void USART2_IRQHandler(void) {
	u8 res;
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET) {
		res=USART_ReceiveData(USART2);
		//将数据发送到PC
		USART_SendData(USART_PC,res);
	}
}
#endif
