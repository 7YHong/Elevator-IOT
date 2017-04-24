/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "includes.h"

#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif


void RepeatP13 (void *argument) {
	for (;;) {
		//repeatP13(1);
		PCout(13)=0;
		osDelay(10);
		PCout(13)=1;
		osDelay(20);
	}
}
void usart() {
	for(;;) {
		//Uprint(USART3,"AT\n");
		//Uprint(USART1,"AT\n");
		printf("AT\n");
		osDelay(8000);
	}
}

void SPITest() {
	u8 i;
	for(i=2; i<8; i++) {
		SPI_WriteData(i, (1<<i)-1);
	}
	i=1;
	while(1) {
		SPI_WriteData(8,i);
		i<<=1;
		if(i==0x00) i=1;
		osDelay(500);
	}
}

void keyscan() {
	short i=1,key=0;
	for(;;) {
		key=KeyScan();
		if(key>0) {
			//PCout(13)=i;
			//i=!i;
			SPI_WriteData(1,key);
			printf("key pressed:%d\n",key);
		}
		osDelay(100);
	}
}


void app_main() {
	SPI_WriteData(0x09, 0x00);       //译码方式：不译码
	SPI_WriteData(0x0A, 0x01);       //亮度
	SPI_WriteData(0x0B, 0x07);       //扫描界限；8个数码管显示
	SPI_WriteData(0x0C, 0x01);       //掉电模式：0；普通模式：1
	SPI_WriteData(0x0F, 0x00);       //显示测试：1；测试结束，正常显示：0

	//GPIO_Write(GPIOA,0xf0);

	osThreadNew(SPITest,NULL,NULL);
	osThreadNew(keyscan,NULL,NULL);
}

int main (void) {
	SystemCoreClockUpdate();

	GPIO_Configuration();
	USART_Configuration();
	NVIC_Configuration();
	SPI_Configuration();
	KEY_Init();

	osKernelInitialize();                 // Initialize CMSIS-RTOS
	osThreadNew(app_main, NULL, NULL);    // Create application main thread
	osKernelStart();                      // Start thread execution
	for (;;) {}
}

