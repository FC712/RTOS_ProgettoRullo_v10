//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "timers.h"                     // ARM.FreeRTOS::RTOS:Timers
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "infrarossi.h"
#include "Arduino.h"
#include "led.h"
#include "eventGroupRullo.h"
#include "Ultrasuoni.h"

extern EventGroupHandle_t xEventGroupRullo;
 
//------------------------------------------------------------------------------------------
//=== Global Functions =====================================================================
//------------------------------------------------------------------------------------------
void irInit() {
  
	pinMode(IR_PIN,INPUT);
	xTaskCreate(vTaskRilevaColore, /* Pointer to the function that implements the task.              */
		"Task 1 (vTaskMotPA2)",    /* Text name for the task.  This is to facilitate debugging only. */
		50,   /* Stack depth in words.                */
		NULL,  /* We are not using the task parameter. */
		1,     /* This task will run at priority 1.    */
		NULL); /* We are not using the task handle.    */
}
//------------------------------------------------------------------------------------------
int irRead() {
  
  return digitalRead(IR_PIN);   
}
//------------------------------------------------------------------------------------------
//void vTaskRilevaColore(void * pvParameters){
//	const EventBits_t xBitsToWaitFor = EV_OBJECT_DETECTED;
//	while(1){
//		xEventGroupWaitBits(xEventGroupRullo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY);
//		if(irRead()==0) {
//			LedRossoOn();
//			LedVerdeOff();
//			xEventGroupSetBits(xEventGroupRullo,OBJECT_WHITE);
//		} else {
//			LedVerdeOn();
//			LedRossoOff();
//			xEventGroupSetBits(xEventGroupRullo,OBJECT_BLACK);
//		}
//	}
//}
void vTaskRilevaColore(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EV_OBJECT_DETECTED;
	int i,oggettoB=0;
	while(1){
		xEventGroupWaitBits(xEventGroupRullo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY);
		for(i=0;i<600;i++){
			if(irRead()==0) {
				oggettoB=oggettoB+1;	
			}
		}
		if(oggettoB==1){
			LedRossoOn();
      LedVerdeOff();
			xEventGroupSetBits(xEventGroupRullo,OBJECT_WHITE);
		}	
		else {
			LedVerdeOn();
			LedRossoOff();
			xEventGroupSetBits(xEventGroupRullo,OBJECT_BLACK);	
			
		}
 }
}
