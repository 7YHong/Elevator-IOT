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

	// ...
	for (;;) {
		repeatP13(1);
		osDelay(300);
	}
}
void usart() {
	for(;;) {
		Uprint(USART2,"AT+RST\n");
		//printf("AT+RST\n");
		osDelay(10000);
	}
}
int main (void) {
	SystemCoreClockUpdate();

	GPIO_Configuration();
	USART_Configuration();
	NVIC_Configuration();

	osKernelInitialize();                 // Initialize CMSIS-RTOS
	//osThreadNew(app_main, NULL, NULL);    // Create application main thread
	//osThreadNew(usart, NULL, NULL);
	osKernelStart();                      // Start thread execution
	for (;;) {}
}

