void DC_Motor_Init(void);
void Change_direction(unsigned long data, char d);
void SysTick_Handler(void);
void Delay100ms(unsigned long time);
void Ser_motor_0(unsigned long*, unsigned long*);
void Ser_motor_90(unsigned long*, unsigned long*);
void Ser_motor_135(unsigned long*, unsigned long*);
void Ser_motor_180(unsigned long*, unsigned long*);
void Motor_stop(void);
void Motor_start(void);
