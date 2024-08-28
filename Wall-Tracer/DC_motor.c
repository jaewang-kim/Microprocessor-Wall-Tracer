#include "TExaS.h"
#include "DC_motor.h"
#include "tm4c123gh6pm.h"
#include "sonic.h"
#include "stdlib.h"
#include "math.h"


unsigned long H, L, Val, Wave, Left_d, Mid_d, Right_d;
char m,l,r, Dir;

void DC_Motor_Init(void){ unsigned long volatile delay;  //PA5 = right wheel, PA6 = left wheel
   SYSCTL_RCGC2_R |= 0x00000001; // activate clock for port A
	 delay = SYSCTL_RCGC2_R;
		H =112000;// 5% 0.5ms를 만들기위핸 0도값
		L = 1600000 - H;
   Val = 0; // 중복 속도조절 방지 및 미드 사용.
   GPIO_PORTA_AMSEL_R &= ~0x7C; // disable analog functionality on PA5, PA6
   GPIO_PORTA_PCTL_R &= ~0x0FFF0000; // configure PA5 , PA6 ,PA4
   GPIO_PORTA_DIR_R |= 0x7C; // make PA5, PA6 ,PA7out
   GPIO_PORTA_DR8R_R |= 0x7C; // enable 8 mA drive on PA5, PA6,PA4
   GPIO_PORTA_AFSEL_R &= ~0x7C; // disable alt funct on PA5, PA6,PA7\4
   GPIO_PORTA_DEN_R |= 0x7C; // enable digital I/O on PA5, PA6,PA4
   GPIO_PORTA_DATA_R &= ~0x7C; // make PA5, 6 HIGH 
   NVIC_ST_CTRL_R = 0; // disable SysTick during setup
   NVIC_ST_RELOAD_R = L-1; // 초기값을 1로 주니 하이로 설정
   NVIC_ST_CURRENT_R = 0; // any write to current clears it
   NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x00000000; // priority 0
   NVIC_ST_CTRL_R = 0x00000007; // enable with core clock and interrupts
}
//왼쪽 바퀴 PA5(0X20), 오른쪽 바퀴 PA6(0X40), 왼쪽 센서가 3번째 BIT(0X40), 오른쪽ㅇ 첫번째BIT(0X01)
void SysTick_Handler(void){
   if(GPIO_PORTA_DATA_R&0x10){ // toggle PA4
      GPIO_PORTA_DATA_R &= ~0x10; // make PA4 low
      NVIC_ST_RELOAD_R = H-1; // reload value for low phase  PUILL UP이라 반대.
   } else{
      GPIO_PORTA_DATA_R |= 0x10; // make PA4 high
      NVIC_ST_RELOAD_R = L-1; // reload value for high phase
   }
}

	void Delay100ms(unsigned long time){
  unsigned long i; 
  while(time > 0){
    i = 1333333;      // this number means 100ms
    while(i > 0){
      i = i - 1;
			    }
    time = time - 1;  // decrements every 100 ms. Having time == 1 as an input parameter 
						          // makes sure this loop executes only once
  }
}

void Change_direction(unsigned long data, char d){   //3bit data
	if (/*(data & 0x04 ) == 0x04 ||*/ d == 'm' ){
		Val = 2;		//가운데 
	}
	else if (/*(data & 0x02) == 0x02 ||*/ d == 'l'){
		Val = 0;		//왼쪽
	}
	else if (/*(data & 0x08) == 0x08 ||*/ d == 'r'){	
		Val = 1;		//오른쪽 
	}
	/*else if ((data & 0x02) == 0x02){
		Val = 2;		//가운데 
	}*/

	 if(Val == 0){
     GPIO_PORTA_DATA_R |= 0x60;	//왼쪽 회전
		 GPIO_PORTA_DATA_R &= ~0x40;
   }                   
   else if (Val == 1) {
     GPIO_PORTA_DATA_R |= 0x60;	//오른쪽 회전
		 GPIO_PORTA_DATA_R &= ~0x20;
   }
	 else{
		GPIO_PORTA_DATA_R |= 0X60;
	 }
	// Delay1ms(1);
}

void Ser_motor_0(unsigned long* p, unsigned long* q){ //첫번째 이렇게 해보ㅓㅏ 두번째 nvic 값직접바꿔보기
	  
		*p = 38000; //0 도
	  *q = 1600000 - *p;
			}
void Ser_motor_90(unsigned long* p, unsigned long* q){
 	  *p= 112000; // 90도
	  *q = 1600000 - *p;
	
}
void Ser_motor_135(unsigned long* p, unsigned long* q){
		*p= 144000; // 180도
	  *q = 1600000 - *p;

}

void Ser_motor_180(unsigned long* p, unsigned long* q){
		*p= 192000; // 180도
	  *q = 1600000 - *p;

}



	/*	if(abs(Left_d - Right_d) <=  Mid_d){
			Dir = m;
		}
		else if(Left_d > Right_d){
			Dir = l;
		}
		else
		{
			Dir = r;
		}			
		return Dir; 
}*/

void Motor_stop(void){
	GPIO_PORTA_DATA_R &= ~0x60;
}


/*void Motor_stop(void){
   NVIC_ST_CTRL_R = 0;
   NVIC_ST_RELOAD_R = 0;
}

void Motor_go(void){
   NVIC_ST_RELOAD_R = L - 1;
   NVIC_ST_CTRL_R = 0x07;
}*/

/*#include "TExaS.h"
#include "DC_motor.h"
#include "tm4c123gh6pm.h"

unsigned long H, L, IR_data, Val;

void DC_Motor_Init(void){   //PA5 = right wheel, PA6 = left wheel
   SYSCTL_RCGC2_R |= 0x00000001; // activate clock for port A
    IR_data = 0x00;
   L = H = 40000; // 50%
    Val = 0; // 중복 속도조절 방지 및 미드 사용.
   GPIO_PORTA_AMSEL_R &= ~0x6C; // disable analog functionality on PA5, PA6
   GPIO_PORTA_PCTL_R &= ~0x00F00000; // configure PA5 , PA6 
   GPIO_PORTA_DIR_R |= 0x6C; // make PA5, PA6 out
   GPIO_PORTA_DR8R_R |= 0x6C; // enable 8 mA drive on PA5, PA6
   GPIO_PORTA_AFSEL_R &= ~0x6C; // disable alt funct on PA5, PA6
   GPIO_PORTA_DEN_R |= 0x6C; // enable digital I/O on PA5, PA6
   GPIO_PORTA_DATA_R &= ~0x6C; // make PA5, 6 HIGH
   //GPIO_PORTA_DATA_R |= 0x40; // make PA6 high
   NVIC_ST_CTRL_R = 0; // disable SysTick during setup
   NVIC_ST_RELOAD_R = H-1; // 초기값을 1로 주니 하이로 설정
   NVIC_ST_CURRENT_R = 0; // any write to current clears it
   NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x00000000; // priority 0
   NVIC_ST_CTRL_R = 0x00000001; // enable with core clock and interrupts
}
//왼쪽 바퀴 PA5(0X20), 오른쪽 바퀴 PA6(0X40), 왼쪽 센서가 3번째 BIT(0X40), 오른쪽ㅇ 첫번째BIT(0X01)
void SysTick_Handler(void){
   if(((IR_data & 0x07) == 0x04) || (((IR_data & 0x07) == 0x02 || (IR_data & 0x07) == 0x00) && Val == 0)){ //오른쪽 완만일떄. 왼쪽바퀴 1 오른쪽 바퀴 토글(50프로), val_2=1로 설정
      GPIO_PORTA_DATA_R |= 0x20;	//오른쪽 회전
			GPIO_PORTA_DATA_R &= ~0x40;
     }                                                                                                      // 오른쪽바퀴 1, 왼쪽 토글 70000정도, 80프로이상은 필요                                                                                             //왼쪽바퀴 토글(50프로)
   else if (((IR_data & 0x07) == 0x01) || (((IR_data & 0x07) == 0x02 || (IR_data & 0x07) == 0x00) && Val == 1)){ //왼쪽 완만일때, 오른쪽바퀴1, 왼쪽바퀴 토글, Val_1 = 1로설정.
      GPIO_PORTA_DATA_R |= 0x40;	//왼쪽 회전
			GPIO_PORTA_DATA_R &= ~0x20;
   }                                                                                                            //왼쪽바퀴1, 오른쪽 바퀴토글 70000정도 80프로 이상은 필요
}

void Change_direction(unsigned long data){   //3bit data
  IR_data = data;                                                                                                                                                                     //50프로로 토글값고정
	if ( (IR_data & 0x07) == 0x04){
		Val = 0;
	}
	else
		Val = 1;
	
	   if(((IR_data & 0x07) == 0x04) || (((IR_data & 0x07) == 0x02 || (IR_data & 0x07) == 0x00) && Val == 0)){ //오른쪽 완만일떄. 왼쪽바퀴 1 오른쪽 바퀴 토글(50프로), val_2=1로 설정
      GPIO_PORTA_DATA_R |= 0x20;	//오른쪽 회전
			GPIO_PORTA_DATA_R &= ~0x40;
     }                                                                                                      // 오른쪽바퀴 1, 왼쪽 토글 70000정도, 80프로이상은 필요                                                                                             //왼쪽바퀴 토글(50프로)
   else if (((IR_data & 0x07) == 0x01) || (((IR_data & 0x07) == 0x02 || (IR_data & 0x07) == 0x00) && Val == 1)){ //왼쪽 완만일때, 오른쪽바퀴1, 왼쪽바퀴 토글, Val_1 = 1로설정.
      GPIO_PORTA_DATA_R |= 0x40;	//왼쪽 회전
			GPIO_PORTA_DATA_R &= ~0x20;
   }
	 else
		 GPIO_PORTA_DATA_R |= 0x60;
	 
}*/

/*void Motor_stop(void){
   NVIC_ST_CTRL_R = 0;
   NVIC_ST_RELOAD_R = 0;
}

void Motor_go(void){
   NVIC_ST_RELOAD_R = L - 1;
   NVIC_ST_CTRL_R = 0x07;
}*/