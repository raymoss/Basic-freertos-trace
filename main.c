/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
/* Hardware and starter kit includes. */
//#include "arm_comm.h"
#include "stm32f4_discovery.h"     /* need to change it as its board specific port */
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "usart_print.h"
#include "trcKernelPort.h"
traceLabel xTickTraceUserEvent;  //trace
//extern void vUDPCommandInterpreterTask( void *pvParameters );   //trace
//extern void vRegisterCLICommands( void );   //trace

void prvFlashingLedTask(void);
void prvUSARTTask(void);
void prvUSART(void *pvparameters);
void main(){
vTraceInitTraceData();     //trace
  xTickTraceUserEvent = xTraceOpenLabel( "tick" );
//vRegisterCLICommands();       //trace

usart_initialization(USART1);
STM_EVAL_LEDInit(LED3);
STM_EVAL_LEDOn(LED3);
prvFlashingLedTask();
prvUSARTTask();
usart_printf(USART1,"Starting task schedulling\r\n");
if(!uiTraceStart())
  usart_printf(USART1,"Error in starting the trace recorder . Continuing with the scheduler.....");
vTaskStartScheduler();
while(1);
}
void vApplicationTickHook( void )
{
	/* Write a user event to the trace log.
	Note tick events will not appear in the trace recording with regular period
	because this project runs in a Windows simulator, and does not therefore
	exhibit deterministic behaviour. */
	vTraceUserEvent( xTickTraceUserEvent );
}
void prvFlashingLed(void *pvParameters){
 // usart_printf(USART1,"FLASHLED: Starting Flashing Led task\r\n");
 
  for(;;){
    STM_EVAL_LEDToggle(LED3);
    usart_printf(USART1,"FLASHLED: Toggling Flashing Led task\r\n");
    vTaskDelay(1000);
  }
}

void prvFlashingLedTask(){
xTaskCreate(prvFlashingLed, "FlashLed",configMINIMAL_STACK_SIZE,(void *)NULL, tskIDLE_PRIORITY,(TaskHandle_t *)NULL);  
}
void prvUSARTTask(){
  TaskHandle_t xHandle = NULL;
  //void parameters = NULL;
  xTaskCreate(prvUSART, "UsartSend", configMINIMAL_STACK_SIZE,(void *)NULL, tskIDLE_PRIORITY,(TaskHandle_t *)NULL);  
     }

void prvUSART(void *pvParameters){
 
 
  while(1){
  usart_printf(USART1,"USART: My task is up\r\n");
  vTaskDelay(1000);
  }}