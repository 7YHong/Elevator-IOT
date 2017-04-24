#ifndef _USART_H
#define _USART_H

//如果想串口中断接收，请不要注释以下宏定义
#define USART1_RX_EN 0 //使能串口1接收
#define USART3_RX_EN 0 //使能串口3接收
#define USART_PC USART3 //与PC连接的串口

void Uprint(USART_TypeDef* USARTx,unsigned char * str);

#endif
