#include "includes.h"

char RxBuffer[64];
short RxCounter;

char RxBuffer1[64];
short RxCounter1;

char * const Rprefix="接收到数据：";

// 重定向printf到WIFI
int fputc(int ch, FILE *f) {
	//USART_PC->SR;  //USART_GetFlagStatus(USART1, USART_FLAG_TC) 解决第一个字符发送失败的问题
	USART_SendData(USART_WIFI, (unsigned char) ch);// USART1 可以换成 USART2 等
	while (!(USART_WIFI->SR & USART_FLAG_TXE));
	return (ch);
}
// 以上为重定向printf

void PCprint(char * str){
	while(*str) {
		USART_SendData(USART_PC, *str++);
		//等待传输结束
		while(USART_GetFlagStatus(USART_PC, USART_FLAG_TXE) == RESET);
	}
}

//同时发送字符串到WIFI和PC，不会自动添加换行符
void Uprint(char * str) {
	printf("%s",str);
#if(USART_DEBUG==1)		//如果是调试模式，还会把消息发给PC
	PCprint(str);
#endif
}
//以上为字符串发送程序

//连接PC
void USART1_IRQHandler(void) {
	char res;
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET) {
		res=USART_ReceiveData(USART1);
		/*if(res==0xA|| res==0xD) {
			RxBuffer1[RxCounter1]=0;
			if(RxCounter1<1) {
				RxCounter1=0;
				return;
			}
			RxCounter1=0;

			Uprint(RxBuffer1);
			Uprint("\r\n");
			printf("camp \"AT\" result=%d\n",strcmp("AT\0",RxBuffer1));
			//printf("%s\r\n",RxBuffer1);
			return;
		}
		RxBuffer1[RxCounter1++]=res;*/
		USART_SendData(USART_WIFI, res);
		//等待传输结束
		while(USART_GetFlagStatus(USART_WIFI, USART_FLAG_TXE) == RESET);
	}
}

//连接WIFI
void USART3_IRQHandler(void) {
	char res;
	if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET) {
		res=USART_ReceiveData(USART3);
		if(res==0xA|| res==0xD) {
			RxBuffer[RxCounter]=0;
			if(RxCounter==0) return;
			RxCounter=0;
			//PCprint("receive from wifi:");
			PCprint(RxBuffer);
			//printf("receive from wifi:%s",);
			//printf("camp \"OK\" result=%d\n",strcmp("OK\0",RxBuffer));
			//printf("camp \"WIFI GOT IP\" result=%d\n",strcmp("WIFI GOT IP\0",RxBuffer));
			//printf("receive:");
			//puts(RxBuffer);
			handleTcp(RxBuffer);
			/*
			printf("OK");
			printf("%s",RxBuffer);
			printf("\"OK\"\'s length is %d\n",strlen("OK"));
			printf("RxBuffer's length is %d\n",strlen(RxBuffer));
			*/
			return;
		}
		RxBuffer[RxCounter++]=res;
		
		/*USART_SendData(USART_PC, res);
		//等待传输结束
		while(USART_GetFlagStatus(USART_PC, USART_FLAG_TXE) == RESET);*/
	}
}
