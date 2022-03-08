#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

#define SRV_SX 0
#define SRV_DX 1

void srvInit(void);
void setPosSrv(int srvTon);
void smistaBiancoSx(void);
void smistaNeroDx(void);
void vTask_Servo(void * pvParameters);

