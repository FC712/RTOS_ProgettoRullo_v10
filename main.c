//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"                     // ARM.FreeRTOS::RTOS:Timers
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "Puls.h"
#include "Led.h"
#include "Arduino.h"
#include "Mot.h"
#include "SysClock.h"

int main(void){ 
	
	pllInit(0, 10, 0);
	SwInit();
	LedInit();
	motInit();
	

	vTaskStartScheduler();
}

