
/******************************************************
FreeRTOS demo program.
Implementing 2 tasks, each blinking a LED.

STK500 setup:
  * PORTC connected to LEDS.

Henning Hargaard 13.2.2016
*******************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "uart.h"
#include <string.h>
#include "switch.h"
#include "semphr.h"
#include "queue.h"

void EnterBoot( void *pvParameters)
{
	
	while(1)
	{
		if(((switchStatus() >> 7)&0b1) == 1)
		{
			__asm("jmp 0x3c00");
			
		}
		vTaskDelay(1000);
	}
}

#define EX_PART 3

#if EX_PART == 2

void vLEDFlashTask1( void *pvParameters )
{
portTickType xLastWakeTime;
xLastWakeTime=xTaskGetTickCount();
  while(1)
  {
    toggleLED(0);
    vTaskDelayUntil(&xLastWakeTime,1000);
  }
}

void vLEDFlashTask2( void *pvParameters )
{
portTickType xLastWakeTime;
xLastWakeTime=xTaskGetTickCount();
  while(1)
  {
    toggleLED(1);
    vTaskDelayUntil(&xLastWakeTime,500);
  }
}



/*
void UARTcmdHandler( void *pvParameters)
{
	char buf[256];
	uint8_t ptr_ = 0;
	buf[0] = 0;
	InitUART(19200,8);
	
	
	while(1)
	{
		if(CharReady())
		{
			buf[ptr_] = ReadChar();
			if(buf[ptr_] == 0)
			{
				if(strcmp("boot", buf))
				{
					__asm("jmp 0x3c00");
				}
				
				ptr_ = 0;
			}
			else
			{
				ptr_++;
			}
		}
		else
		{
			vTaskDelay(10);
		}
		
	}
	
}
*/



// Ex part 2

xSemaphoreHandle xSem1 = NULL;

void SW0Wait(void *par)
{
	
	
	while(1)
	{
		if(switchStatus()&0b1 == 1)
		{
			xSemaphoreGive(xSem1);
		}
		vTaskDelay(100);
	}
}

void LED7on(void * par)
{
	while(1)
	{
		
		if(xSemaphoreTake(xSem1,99999))
		{
			turnOnLED(7);
			vTaskDelay(100);
			turnOffLED(7);
		}
	}
}

#elif EX_PART == 3

xSemaphoreHandle xSem1 = NULL;
uint8_t count = 0;
xQueueHandle xQueue1 = NULL;

void decement(void *par)
{
	
	while(1)
	{
		if(switchOn(0))
		{
			if(xSemaphoreTake(xSem1, 10000))
			{
				count++;
				xQueueSend(xQueue1,&count, 1000);
				xSemaphoreGive(xSem1);
				while(switchOn(0)){vTaskDelay(100);}
			}
			
		}
		vTaskDelay(100);
	}
}

void increment(void *par)
{
	
	while(1)
	{
		if(switchOn(1))
		{
			if(xSemaphoreTake(xSem1, 10000))
			{
				count--;
				xQueueSend(xQueue1,&count, 1000);
				xSemaphoreGive(xSem1);
				while(switchOn(1)){vTaskDelay(100);}
			}
		}
		vTaskDelay(100);
		
	}
}

void LEDDisplay(void *par)
{
	uint8_t itemBuffer = 0;
	writeAllLEDs(itemBuffer);
	while(1)
	{
		if(xQueueReceive(xQueue1, &itemBuffer, 1000))
		{
			writeAllLEDs(itemBuffer);
		}
	}
}


ISR(INT0_vect)
{
	uint8_t tmp = 0;
	//writeAllLEDs(0b1010101);
	xQueueSendToBackFromISR(xQueue1, &tmp,pdTRUE);
	count = 0;
}

#endif


int main(void)
{
	
	PORTA &= ~(1<<2);
	DDRD &= ~(1<<2);
	MCUCR |= 0b11;
	
	GICR |= (1<<6);    
	/*                                                                                                                                                                                                                               
	sei();
	*/
	
	//rit_setup_callback(one_sec_isr, 1000);
	
  initLEDport();
  initSwitchPort();
  InitUART(115200,8);
  
  
  xTaskCreate(EnterBoot, (signed char *) "BootKey", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
  
  #if EX_PART == 2
  vSemaphoreCreateBinary(xSem1);
  xTaskCreate( vLEDFlashTask1, ( signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
  xTaskCreate( vLEDFlashTask2, ( signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );	
  xTaskCreate(SW0Wait, (signed char *) "SW", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
  xTaskCreate(LED7on, (signed char *) "LED", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
  #elif EX_PART == 3
	vSemaphoreCreateBinary(xSem1);
	xQueue1=xQueueCreate(10, sizeof(uint8_t));
	xTaskCreate( decement, ( signed char * ) "dec", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( increment, ( signed char * ) "inc", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( LEDDisplay, ( signed char * ) "LEDD", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	
	
  #endif
  
  vTaskStartScheduler();
  while(1)
  {}
}

