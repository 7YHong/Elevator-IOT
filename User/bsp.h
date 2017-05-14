#ifndef _BSP_H
#define _BSP_H

typedef struct{
	GPIO_TypeDef* GPIOx;
	uint16_t Pin;
}PORT;

void GPIO_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
void SPI_Configuration(void);
void KEY_Init(void);
#endif