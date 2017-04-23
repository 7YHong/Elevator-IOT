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

void repeatP13(u8 time) {
	while(time--) {
		PCout(13)=!PCin(13);
		osDelay(300);
		PCout(13)=!PCin(13);
		osDelay(300);
	}
}

/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void app_main (void *argument) {
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
		Uprint(USART2,"AT+RST\n");
		//printf("AT+RST\n");
		osDelay(10000);
	}
}
void Hc595Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//=============================================================================
//SCK->B11 RCK->B10
//=============================================================================
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

 void SPITest(){
	u16 data=2;
	for(;;){
		if(data==0x20) data=2;
		PCout(13)=0;
		//SPI_RCK=0;
		while (SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);	// Wait the Tx buffer to be empty
		SPI_I2S_SendData(SPI2,~data);
		PCout(13)=1;
		//SPI_RCK=1;
		osDelay(5);		//在RCK产生一个脉冲
		PCout(13)=0;
		//SPI_RCK=0;
		osDelay(500);
		data<<=1;
	}
} 

int main (void) {
	SystemCoreClockUpdate();

	GPIO_Configuration();
	//USART_Configuration();
	//NVIC_Configuration();
	//SPI_Configuration();
	//Hc595Init();

	osKernelInitialize();                 // Initialize CMSIS-RTOS
	osThreadNew(app_main, NULL, NULL);    // Create application main thread
	//osThreadNew(usart, NULL, NULL);
	//osThreadNew(SPITest,NULL,NULL);
	osKernelStart();                      // Start thread execution
	for (;;) {}
}

