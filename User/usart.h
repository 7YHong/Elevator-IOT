#ifndef _USART_H
#define _USART_H

//如果想串口中断接收，请不要注释以下宏定义
#define USART_WIFI USART3 //与PC连接的串口
#define USART_PC USART1 //与PC连接的串口
#define USART_DEBUG 1		//调试模式会将串口消息原样发送给电脑，还会把收到的消息发送到串口3

void PCprint(char * str);
void Uprint(char * str);

#endif
