#include "Arduino.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "timers.h"                     // ARM.FreeRTOS::RTOS:Timers
#include "Mot.h" 
#include "Led.h" 
#include "event_groups.h" 
#include "Puls.h" 

#define MOT_VN 160
#define EV_MOT_START 1 << 0 //bit
#define EV_MOT_STOP  2 << 0 //bit

void TIM1_CH2_Init(int motTon);
void vTask_Motore(void * pvParameters);
void vTaskMotPA1(void * pvParameters);
void vTaskMotPA2(void * pvParameters);

EventGroupHandle_t xEventGroup;

//inizzializzazzione del motore sul timer 1 canale 2
void motInit(void){
	// configurazione del motore sul pin PE11
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	//GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOE->MODER &= ~GPIO_MODER_MODE11_Msk;
	GPIOE->MODER |= GPIO_MODER_MODE11_1;		 //  Output(01)
	//	
  GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL11_Msk;
  GPIOE->AFR[1] |= GPIO_AFRH_AFSEL11_0;	

	TIM1_CH2_Init(MOT_VN);
	
	xTaskCreate(vTask_Motore, /* Pointer to the function that implements the task.              */
		"Task 1 (Motore)",    /* Text name for the task.  This is to facilitate debugging only. */
		50,   /* Stack depth in words.                */
		NULL,  /* We are not using the task parameter. */
		1,     /* This task will run at priority 1.    */
		NULL); /* We are not using the task handle.    */
	xTaskCreate(vTaskMotPA1, /* Pointer to the function that implements the task.              */
		"Task 1 (vTaskMotPA1)",    /* Text name for the task.  This is to facilitate debugging only. */
		50,   /* Stack depth in words.                */
		NULL,  /* We are not using the task parameter. */
		1,     /* This task will run at priority 1.    */
		NULL); /* We are not using the task handle.    */
	xTaskCreate(vTaskMotPA2, /* Pointer to the function that implements the task.              */
		"Task 1 (vTaskMotPA2)",    /* Text name for the task.  This is to facilitate debugging only. */
		50,   /* Stack depth in words.                */
		NULL,  /* We are not using the task parameter. */
		1,     /* This task will run at priority 1.    */
		NULL); /* We are not using the task handle.    */
		
		motStop();
		xEventGroup=xEventGroupCreate();
		vTaskStartScheduler();
}

void motStop(void){
	RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
	//GPIOE->ODR |= GPIO_ODR_OD11;
	GPIOE->ODR &= ~GPIO_ODR_OD11;
  GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL11_Msk;
  GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL11_0;	

}
void motStart(void){
	//GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOE->MODER &= ~GPIO_MODER_MODE11_Msk;
	GPIOE->MODER |= GPIO_MODER_MODE11_1;		 //  Output(01)
	//	
  GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL11_Msk;
  GPIOE->AFR[1] |= GPIO_AFRH_AFSEL11_0;	
	
	//abilitazione registri timer
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
}

void vTask_Motore(void * pvParameters){
	const EventBits_t xBitsToWaitForStart = EV_MOT_START;
	while(1){
		xEventGroupWaitBits(xEventGroup,xBitsToWaitForStart,pdTRUE,pdTRUE,portMAX_DELAY);
		motStart();
	}
}

void vTaskMotPA1(void * pvParameters){
	while(1){
		while(!digitalRead(PA1));
		while(digitalRead(PA1)){;}
			xEventGroupSetBits(xEventGroup,EV_MOT_START);	
	}	
}
void vTaskMotPA2(void * pvParameters){
	while(1){
		while(!digitalRead(PA0));
		while(digitalRead(PA0)){;}
			xEventGroupSetBits(xEventGroup,EV_MOT_STOP);
	}	
}


//attivazione timer 1 canale 2
void TIM1_CH2_Init(int motTon){
	//abilitazione registri timer
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	//direzione UP
	TIM1->CR1 &= ~TIM_CR1_DIR;
	
	//impostazione prescaler
	TIM1->PSC =799;
	
	//impostazione periodo
	TIM1->ARR = 1000-1;
	
	//configurazione PWM mode per l'uscita del output 1
	TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
	TIM1->CCMR1 |=TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2M_2;
	
	//modifica di CCR1 in ogni istante con PE=0, ad ongli update event con PE=1
 //	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;
	TIM1->CCMR1 |= TIM_CCMR1_OC2PE;
	
	//Selezione polarità: 0 Attivo alto; 1 attivo basso
	TIM1->CCER &= ~TIM_CCER_CC2P;
	
	//Abilitazione canale 1 complementare
	TIM1->CCER |= TIM_CCER_CC2E;
	
	TIM1->BDTR |= TIM_BDTR_MOE;
//	//abilitazione OCN1
//	TIM4->BDTR |= TIM_BDTR_MOE;
	
	//valore confronto
	TIM1->CCR2 = motTon-1;
	
	//abilitazione timer1
	TIM1->CR1 |= TIM_CR1_CEN;
}

