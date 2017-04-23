#include "includes.h"

u8 DISP1;

void SPI_RCKPulse(){
	GPIO_SetBits(GPIOB,SPI_RCK_PIN);
	osDelay(5);
	GPIO_ResetBits(GPIOB,SPI_RCK_PIN);
}

