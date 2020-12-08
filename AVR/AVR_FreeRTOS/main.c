#include <stdlib.h>
#include <string.h>
#include <avr/eeprom.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

#include "Serial.h"

static portTASK_FUNCTION( vLEDFlashTask, pvParameters );
static portTASK_FUNCTION( vUARTSendTask, pvParameters );

int main( void )
{
	//prvIncrementResetCount();

	/* Setup the LED's for output. */
	DDRB = 0xff;
  PORTB = 0xff;

  // Init USART1
  usart_init();

  xTaskCreate( vLEDFlashTask, "LEDx", 85, NULL, 1, ( TaskHandle_t * ) NULL );
  xTaskCreate( vUARTSendTask, "SERIAL", 85, NULL, 1, ( TaskHandle_t * ) NULL );
  xTaskCreate( vUARTSendTask, "SERIAL", 85, NULL, 1, ( TaskHandle_t * ) NULL );
  xTaskCreate( vUARTSendTask, "SERIAL", 85, NULL, 1, ( TaskHandle_t * ) NULL );
  xTaskCreate( vUARTSendTask, "SERIAL", 85, NULL, 1, ( TaskHandle_t * ) NULL );



	/* Create the standard demo tasks. */
	// vStartIntegerMathTasks( tskIDLE_PRIORITY );
	// vAltStartComTestTasks( mainCOM_TEST_PRIORITY, mainCOM_TEST_BAUD_RATE, mainCOM_TEST_LED );
	// vStartPolledQueueTasks( mainQUEUE_POLL_PRIORITY );
	// vStartRegTestTasks();
	//
	// /* Create the tasks defined within this file. */
	// xTaskCreate( vErrorChecks, "Check", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
	//
	// /* Create the co-routines that flash the LED's. */
	//vStartFlashCoRoutines( mainNUM_FLASH_COROUTINES );
	//
	// /* In this port, to use preemptive scheduler define configUSE_PREEMPTION
	// as 1 in portmacro.h.  To use the cooperative scheduler define
	// configUSE_PREEMPTION as 0. */
	vTaskStartScheduler();
	//xPortStartScheduler();

	//while(1);

	return 0;
}

static portTASK_FUNCTION( vLEDFlashTask, pvParameters )
{
TickType_t xLastFlashTime;


	/* We need to initialise xLastFlashTime prior to the first call to
	vTaskDelayUntil(). */
	xLastFlashTime = xTaskGetTickCount();

	for(;;)
	{
		/* Delay for half the flash period then turn the LED on. */
		vTaskDelayUntil( &xLastFlashTime, 33 );
		PORTB ^= (1 << 7);

		/* Delay for half the flash period then turn the LED off. */
		vTaskDelayUntil( &xLastFlashTime, 33 );
		PORTB ^= (1 << 7);
	}
} /*lint !e715 !e818 !e830 Function definition must be standard for task creation. */

uint8_t t_offset = 0;
char c = 'A';

static portTASK_FUNCTION( vUARTSendTask, pvParameters )
{
  TickType_t xLastFlashTime;
  char TaskC = c;

  t_offset += 33;
  c++;

  for(;;)
  {
    vTaskDelayUntil( &xLastFlashTime, t_offset);
    usart_putch(TaskC);
  }

}
