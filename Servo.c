#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "timers.h"                     // ARM.FreeRTOS::RTOS:Timers
#include "Servo.h" 
#include "event_groups.h" 

#define SERVO_T 20000
#define SERVO_POS_FERMO 10000 //1550
#define SERVO_POS_MIN 1000 
#define SERVO_POS_MAX 2500

extern EventGroupHandle_t xEventGroupRullo;

void TIM5_CH2PWM_Init(int srvTon);
char srv_pos=0;
int srvTon;

//Funzione per l'inizializzazione del pin PA1 come AF
void srvInit(void){

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE1_1;
  GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL1_Msk;
  GPIOA->AFR[0] |= GPIO_AFRL_AFSEL1_1;	
}

// Funzione per l'inizializzazione del timer usato per generare il segnale PWM necessario per il funzionamento del motore 
void TIM5_CH2PWM_Init(int srvTon){
	//abilitazione registri timer
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM5EN;
	
	//direzione UP=0 down=1
	TIM5->CR1 &= ~TIM_CR1_DIR;
	
	//impostazione prescaler con clock=80Mhz
	TIM5->PSC =79;
	
	//impostazione periodo 20ms
	TIM5->ARR = 20000-1;
	
	//configurazione PWM mode per l'uscita del output 1
	TIM5->CCMR1 &= ~TIM_CCMR1_OC2M;
	TIM5->CCMR1 |=TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2M_2;
	
	//modifica di CCR1 in ogni istante con PE=0, ad ongli update event con PE=1
//	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;
	TIM5->CCMR1 |= TIM_CCMR1_OC2PE;
	
	//Selezione polarità: 0 Attivo alto; 1 attivo basso
	TIM5->CCER &= ~TIM_CCER_CC2P;
	
	//Abilitazione canale 1 complementare
	TIM5->CCER |= TIM_CCER_CC2E;
	
//	//abilitazione OCN1
//	TIM1->BDTR |= TIM_BDTR_MOE;
	
	//valore confronto
	TIM5->CCR2 = srvTon-1;
	
	//abilitazione timer1
	TIM5->CR1 |= TIM_CR1_CEN;
}

//task che gestisce lo smistamento dei pacchetti 
void vTask_Servo(void * pvParameters){
	TIM5_CH2PWM_Init(SERVO_POS_FERMO);
	while(1){
//		vTaskDelay(700);
//		if(srv_pos){
//			smistaBiancoSx();
//		}
//		else{
//			smistaNeroDx();
//		}
	}
}


/*funzione per smistare il pacco bianco a sinistra: posizioniamo l'asta del servo al centro, 
poi la spostiamo di -45° a destra e aspettiamo 700ms, successivamente spostiamo l'asta a 45° e aspettiamo 1,
5s prima di rimetterlo in posizione centrale*/
void smistaBiancoSx(void) {
	  srvTon=1700;
		setPosSrv(srvTon);
		vTaskDelay(700);
		srvTon=1300;
		setPosSrv(srvTon);
		vTaskDelay(1500);
		setPosSrv(SERVO_POS_FERMO);
}

/*funzione per smistare il pacco nero a destra: posizioniamo l'asta del servo al centro, 
poi la spostiamo di -45° a destra e aspettiamo 700ms, successivamente spostiamo l'asta a 45° e aspettiamo 1,
5s prima di rimetterlo in posizione centrale*/
void smistaNeroDx(void){
	  srvTon=1300;
		setPosSrv(srvTon);
		vTaskDelay(700);
		srvTon=1700;
		setPosSrv(srvTon);
		vTaskDelay(1500);
		setPosSrv(SERVO_POS_FERMO);
}
//funzione per settare la posizione del servomotore 
void setPosSrv(int srvTon){
	TIM5->CCR2 = srvTon-1;
}

