#include "timer.h"
#include "stm32l4xx.h"                  // Device header
#define UNMILIONE 1000000

//PE8
void TIM1_CH1N_PWM(int Ton,int T){
	
	
	//abilitazione registri timer
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	//direzione UP
	TIM1->CR1 &= ~TIM_CR1_DIR;
	
	//impostazione prescaler
	TIM1->PSC =SystemCoreClock/UNMILIONE - 1;
	
	//impostazione periodo
	TIM1->ARR = T-1;
	
	//configurazione PWM mode per l'uscita del output 1
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM1->CCMR1 |=TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1M_2;
	
	//modifica di CCR1 in ogni istante con PE=0, ad ongli update event con PE=1
//	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
	
	//Selezione polarità: 0 Attivo alto; 1 attivo basso
	TIM1->CCER &= ~TIM_CCER_CC1NP;
	
	//Abilitazione canale 1 complementare
	TIM1->CCER |= TIM_CCER_CC1NE;
	
	//abilitazione OCN1
	TIM1->BDTR |= TIM_BDTR_MOE;
	
	//valore confronto
	TIM1->CCR1 = Ton-1;
	
	//abilitazione timer1
	TIM1->CR1 |= TIM_CR1_CEN;
}

//PE11
void TIM1_CH2_PWM(int servo_Ton){
	//abilitazione registri timer
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	//direzione UP
	TIM1->CR1 &= ~TIM_CR1_DIR;
	
	//impostazione prescaler
	TIM1->PSC =80 - 1;
	
	//impostazione periodo
	TIM1->ARR = 20000-1;
	
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
	TIM1->CCR2 = servo_Ton-1;
	
	//abilitazione timer1
	TIM1->CR1 |= TIM_CR1_CEN;
}


//PE13
void TIM1_CH3_PWM(int Ton,int T){
	//abilitazione registri timer
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	//direzione UP
	TIM1->CR1 &= ~TIM_CR1_DIR;
	
	//impostazione prescaler
	TIM1->PSC =SystemCoreClock/UNMILIONE - 1;
	
	//impostazione periodo
	TIM1->ARR = T-1;
	
	//configurazione PWM mode per l'uscita del output 1
	TIM1->CCMR2 &= ~TIM_CCMR2_OC3M;
	TIM1->CCMR2 |=TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3M_2;
	
	//modifica di CCR1 in ogni istante con PE=0, ad ongli update event con PE=1
//	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;
	TIM1->CCMR2 |= TIM_CCMR2_OC3PE;
	
	//Selezione polarità: 0 Attivo alto; 1 attivo basso
	TIM1->CCER &= ~TIM_CCER_CC3P;
	
	//Abilitazione canale 1 complementare
	TIM1->CCER |= TIM_CCER_CC3E;
	
	TIM1->BDTR |= TIM_BDTR_MOE;
//	//abilitazione OCN1
//	TIM4->BDTR |= TIM_BDTR_MOE;
	
	//valore confronto
	TIM1->CCR3 = Ton-1;
	
	//abilitazione timer1
	TIM1->CR1 |= TIM_CR1_CEN;
}


//PE14
void TIM1_CH4_PWM(int Ton,int T){
	//abilitazione registri timer
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	//direzione UP
	TIM1->CR1 &= ~TIM_CR1_DIR;
	
	//impostazione prescaler
	TIM1->PSC =800 - 1;
	
	//impostazione periodo
	TIM1->ARR = T-1;
	
	//configurazione PWM mode per l'uscita del output 1
	TIM1->CCMR2 &= ~TIM_CCMR2_OC4M;
	TIM1->CCMR2 |=TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4M_2;
	
	//modifica di CCR1 in ogni istante con PE=0, ad ongli update event con PE=1
//	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;
	TIM1->CCMR2 |= TIM_CCMR2_OC4PE;
	
	//Selezione polarità: 0 Attivo alto; 1 attivo basso
	TIM1->CCER &= ~TIM_CCER_CC4P;
	
	//Abilitazione canale 1 complementare
	TIM1->CCER |= TIM_CCER_CC4E;
	
	TIM1->BDTR |= TIM_BDTR_MOE;
//	//abilitazione OCN1
//	TIM4->BDTR |= TIM_BDTR_MOE;
	
	//valore confronto
	TIM1->CCR4 = Ton-1;
	
	//abilitazione timer1
	TIM1->CR1 |= TIM_CR1_CEN;
}


void TIM1_SetCCR1(int Ton){
	TIM1->CCR1 = Ton-1;
}



//PB3
void TIM2_CH2_PWM(servo_Ton){
	//abilitazione registri timer
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	
	//direzione UP
	TIM2->CR1 &= ~TIM_CR1_DIR;
	
	//impostazione prescaler
	TIM2->PSC = 80 - 1;
	
	//impostazione periodo
	TIM2->ARR = 20000 -1;
	
	//configurazione PWM mode per l'uscita del output 1
	TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
	TIM2->CCMR1 |=TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2M_2;
	
	//modifica di CCR1 in ogni istante con PE=0, ad ongli update event con PE=1
//	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE;
	
	//Selezione polarità: 0 Attivo alto; 1 attivo basso
	TIM2->CCER &= ~TIM_CCER_CC2P;
	
	//Abilitazione canale 1 complementare
	TIM2->CCER |= TIM_CCER_CC2E;
	
//	//abilitazione OCN1
//	TIM1->BDTR |= TIM_BDTR_MOE;
	
	//valore confronto
	TIM2->CCR2 = servo_Ton -1;
	
	//abilitazione timer1
	TIM2->CR1 |= TIM_CR1_CEN;
}


//PB7
void TIM4_CH2_PWM(int Ton,int T){
	//abilitazione registri timer
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	
	//direzione UP
	TIM4->CR1 &= ~TIM_CR1_DIR;
	
	//impostazione prescaler
	TIM4->PSC =SystemCoreClock/UNMILIONE - 1;
	
	//impostazione periodo
	TIM4->ARR = T-1;
	
	//configurazione PWM mode per l'uscita del output 1
	TIM4->CCMR1 &= ~TIM_CCMR1_OC2M;
	TIM4->CCMR1 |=TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2M_2;
	
	//modifica di CCR1 in ogni istante con PE=0, ad ongli update event con PE=1
//	TIM1->CCMR1 &= ~TIM_CCMR1_OC1PE;
	TIM4->CCMR1 |= TIM_CCMR1_OC2PE;
	
	//Selezione polarità: 0 Attivo alto; 1 attivo basso
	TIM4->CCER &= ~TIM_CCER_CC2P;
	
	//Abilitazione canale 1 complementare
	TIM4->CCER |= TIM_CCER_CC2E;
	
//	//abilitazione OCN1
//	TIM4->BDTR |= TIM_BDTR_MOE;
	
	//valore confronto
	TIM4->CCR2 = Ton-1;
	
	//abilitazione timer1
	TIM4->CR1 |= TIM_CR1_CEN;
}




//PB6
void TIM4_CH1_InCapt(void){
	//abilitazione registri timer
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	
	//prescaler
	TIM4->PSC =SystemCoreClock/UNMILIONE - 1;
	
	//impostazione della direzione
	//00 output
	//01 input, CC1 su TI1
	//10 input, CC1 su TI2
	//11 CC2 slave
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;
	
	//input filter   IC2F[3:0] 0 senza filtro
	TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;
	
	//selezione fronti con CC2NP e CC2P
//	00 rising edge
//	01 falling edge
//	11 entrambi
	TIM4->CCER |= TIM_CCER_CC1P|TIM_CCER_CC1NP;
	
	//input prescaler selezione numero frionti per ogni transizione
	//0 tutti i fronti
	TIM4->CCMR1 &= ~(TIM_CCMR1_IC1PSC);
	
	//abilitazione cattura su ch1
	TIM4->CCER |= TIM_CCER_CC1E;
	
	//abilitazione interrupt
	TIM4->DIER |= TIM_DIER_CC1IE;
	
	//abilitazione timer
	TIM4->CR1 |= TIM_CR1_CEN;
	
	//interrupt
	NVIC_SetPriority(TIM4_IRQn,1);
	NVIC_EnableIRQ(TIM4_IRQn);
}
//PB6
void TIM4_CH1_InCapt_SM(void){
	//abilitazione registri timer
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	
	//prescaler
	TIM4->PSC =SystemCoreClock/UNMILIONE - 1;
	
	//impostazione della direzione
	//00 output
	//01 input, CC1 su TI1
	//10 input, CC1 su TI2
	//11 CC2 slave
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;
	
	//input filter   IC2F[3:0] 0 senza filtro
	TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;
	
	//selezione fronti con CC2NP e CC2P
//	00 rising edge
//	01 falling edge
//	11 entrambi
	TIM4->CCER &= ~ (TIM_CCER_CC1P|TIM_CCER_CC1NP);
	TIM4->CCER |=  (TIM_CCER_CC1P);
	
	TIM4->SMCR &= ~TIM_SMCR_TS;
	TIM4->SMCR |= 4<<4;
	
	TIM4->SMCR &= ~TIM_SMCR_SMS;
	TIM4->SMCR |=4;
	
	
	//input prescaler selezione numero frionti per ogni transizione
	//0 tutti i fronti
	TIM4->CCMR1 &= ~(TIM_CCMR1_IC1PSC);
	
	//abilitazione cattura su ch1
	TIM4->CCER |= TIM_CCER_CC1E;
	
	//abilitazione interrupt
	TIM4->DIER |= TIM_DIER_CC1IE;
	
	//abilitazione timer
	TIM4->CR1 |= TIM_CR1_CEN;
	
	//interrupt
	NVIC_SetPriority(TIM4_IRQn,1);
	NVIC_EnableIRQ(TIM4_IRQn);
}






