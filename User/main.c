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


void RepeatP13 () {
	for (;;) {
		//repeatP13(1);
		PCout(13)=0;
		osDelay(800);
		PCout(13)=1;
		osDelay(800);
	}
}

void app_main() {
	resetWifi();
	for(;;){
		//Uprint("AT\r\n");
		//Uprint("");
		//osDelay(3000);
	}
}

int main (void) {
	SystemCoreClockUpdate();

	GPIO_Configuration();
	USART_Configuration();
	NVIC_Configuration();

	osKernelInitialize();                 // Initialize CMSIS-RTOS
	osThreadNew(RepeatP13, NULL, NULL);    // Create application main thread
	osThreadNew(app_main, NULL, NULL);    // Create application main thread
	osKernelStart();                      // Start thread execution
	for (;;) {}
}

