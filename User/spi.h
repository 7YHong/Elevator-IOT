#ifndef _SPI_H
#define _SPI_H

#define SPI_RCK PBout(12)

void SPI_Configuration(void);
void SPI_WriteData(u8 adress,u8 data);

#endif
