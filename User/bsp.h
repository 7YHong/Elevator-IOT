#ifndef _BSP_H
#define _BSP_H
#endif

//如果想串口中断接收，请不要注释以下宏定义
#define USART1_RX_EN 1 //使能串口1接收
#define USART2_RX_EN 1 //使能串口2接收
#define USART_PC USART1 //与PC连接的串口

void GPIO_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
