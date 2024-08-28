/*#include "..//tm4c123gh6pm.h"
#include "TExaS2.h"
#include "IR_sensor.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

void EnableInterrupts(void);  // E nable interrupts
unsigned long sensor_data;    // 12-bit 0 to 4095 sample
void GPIO_PORTF_Init(void);

int main(void){

  TExaS_Init(ADC0_AIN1_PIN_PE2, ADC0_AIN1_PIN_PE1, ADC0_AIN1_PIN_PE0, LED_PIN_PF2);
	IR_sensor_Init();
	GPIO_PORTF_Init();
  EnableInterrupts();
	
  while(1){ 
    sensor_data = rotate_direction();
		GPIO_PORTF_DATA_R = sensor_data;
  }
}

void GPIO_PORTF_Init(void){
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_DATA_R &= 0xFF;
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_AFSEL_R = 0x00;
	GPIO_PORTF_PUR_R = 0x00;
	GPIO_PORTF_DEN_R = 0xFF;
	GPIO_PORTF_AMSEL_R = 0x00;
	GPIO_PORTF_PCTL_R = 0x00;
}*/

/*work sch
data flow
dc motor
ir sensor*/

/*
#include "..//tm4c123gh6pm.h"
#include "TExaS2.h"
#include "IR_0.h"
#include "IR_1.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

void EnableInterrupts(void);  // E nable interrupts
unsigned long ADC0data, ADC1data;    // 12-bit 0 to 4095 sample
void GPIO_PORTF_Init(void);

int main(void){
  TExaS_Init(ADC0_AIN1_PIN_PE1, ADC0_AIN1_PIN_PE0, LED_PIN_PF2);
  IR0_Init();    // initialize ADC0, channel 1, sequencer 3
	IR1_Init();
	GPIO_PORTF_Init();
  EnableInterrupts();
	
  while(1){ 
    ADC0data = IR0_In();
		ADC1data = IR1_In();
		
		if ((ADC0data < 0xFF) && (ADC1data < 0x300)){
			GPIO_PORTF_DATA_R &= 0x00;
			GPIO_PORTF_DATA_R |= 0x08;
		}
		else if (ADC0data < 0xFF){
			GPIO_PORTF_DATA_R &= 0x00;
			GPIO_PORTF_DATA_R |= 0x04;
		}
		else if(ADC1data < 0x300){
			GPIO_PORTF_DATA_R &= 0x00;			
			GPIO_PORTF_DATA_R |= 0x02;
		}
		else {
			GPIO_PORTF_DATA_R &= 0x00;
		}
  }
}

void GPIO_PORTF_Init(void){
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_DATA_R &= 0xFF;
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_AFSEL_R = 0x00;
	GPIO_PORTF_PUR_R = 0x00;
	GPIO_PORTF_DEN_R = 0xFF;
	GPIO_PORTF_AMSEL_R = 0x00;
	GPIO_PORTF_PCTL_R = 0x00;
}
*/