#include "includes.h"

char RxBuffer[64];
short RxCounter;

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

#if( USART1_RX_EN ==1)   //如果使能了串口1接收
void USART1_IRQHandler(void) {
	char res;
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET) {
		//将数据发送到PC
		res=USART_ReceiveData(USART1);
		USART_SendData(USART1,res);
	}
}
#endif

#if( USART3_RX_EN ==1)   //如果使能了串口3接收
void USART3_IRQHandler(void) {
	char res;
	if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET) {
		res=USART_ReceiveData(USART3);
		if(res=='\n'|res==0xd){
			RxBuffer[RxCounter]=0;
			RxCounter=0;
			printf("OK");
			printf("%s",RxBuffer);
			printf("camp \"OK\" result=%d\n",strcmp("OK\0",RxBuffer));
			printf("\"OK\"\'s length is %d\n",strlen("OK"));
			printf("RxBuffer's length is %d\n",strlen(RxBuffer));
			return;
		}
		RxBuffer[RxCounter++]=res;
		//将数据发送到PC
		//USART_SendData(USART3,res);
	}
}
#endif
