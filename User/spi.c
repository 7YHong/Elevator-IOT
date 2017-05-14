#include "includes.h"


void SPI_WriteData(u8 adress,u8 data){
	SPI_RCK=0;
	while (SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2,adress);
	osDelay(1);
	while (SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2,data);
	osDelay(1);
	SPI_RCK=1;
}
	