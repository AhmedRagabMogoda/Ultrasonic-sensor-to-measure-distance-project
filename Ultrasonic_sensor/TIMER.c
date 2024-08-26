/*
 * TIMER.c
 *
 * Created: 8/14/2024 4:07:42 PM
 *  Author: Ahmed Ragab
 */ 

#include "TIMER.h"

void TIMER0_normal_init_with_interrupt(void)
{
	//determine normal mode
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	//determine prescaler=1024, timer0_clock=(cpu_clock/prescaler)=8000000/1024
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	//enable interrupt to compare match
	sei();
	SET_BIT(TIMSK,TOIE0);
	/*
	timer_tick_time=(1/timer0_clock)=0.128 ms
	occurs interrupt every 0.128*256
	*/
}


void TIMER0_CTC_init_with_interrupt(void)
{
	//determine CTC mode
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	//load value in OCR0 ,to compare match
	OCR0=80;
	//determine prescaler=1024, timer0_clock=(cpu_clock/prescaler)
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	//enable interrupt to compare match
	sei();
	SET_BIT(TIMSK,OCIE0);
	/*
	timer_tick_time=(1/timer0_clock)=0.128 ms
	occurs interrupt every 0.128*OCR0=0.128*80=(10 ms)
	*/
}

void TIMER0_CTC_wave_nonpwm(void)
{
	//determine CTC mode
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	//load value in OCR0 ,to compare match
	OCR0=80;
	//determine prescaler=1024, timer0_clock=(cpu_clock/prescaler)
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	//set OC0 as output pin to generetion wave
	SET_BIT(DDRB,PB3);
	//toggle OC0 on compare match
	SET_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
	/*
	timer_tick_time=(1/timer0_clock)=0.128 ms
	pulse repeated every 0.128*OCR0,cycle repeated every 2*(0.128*OCR0)= ?? ms
	*/
}

void TIMER0_fast_pwm_wave(void)
{
	//determine fast PWM mode
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	//load value in OCR0 ,to compare match
	OCR0=64;
	//determine prescaler=1024, timer0_clock=(cpu_clock/prescaler)
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	//set OC0 as output pin to generetion wave
	SET_BIT(DDRB,PB3);
	//clear OC0 on compare match and set OC0 at bottom=0
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	/*
	timer_tick_time=(1/timer0_clock)=0.128 ms
	on_pulse repeated every 0.128*OCR0=0.128*64 and off_pulse repeated every 0.128*(256-OCR0)=0.128*(256-64) ,cycle repeated every 0.128*256=?? ms
	*/
}

void TIMER0_phase_correct_pwm_wave(void)
{
	//determine phase correct PWM mode
	SET_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	//load value in OCR0 ,to compare match
	OCR0=64;
	//determine prescaler=1024, timer0_clock=(cpu_clock/prescaler)
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	//set OC0 as output pin to generetion wave
	SET_BIT(DDRB,PB3);
	//clear OC0 on compare match when up_counting and set OC0 on compare match when downcounting
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	/*
	timer_tick_time=(1/timer0_clock)=0.128 ms
	cycle repeated every 0.128*2*255=?? ms
	*/
}

void TIMER2_normal_init_with_interrupt(void)
{
	//determine normal mode
	CLR_BIT(TCCR2,WGM20);
	CLR_BIT(TCCR2,WGM21);
	//determine prescaler=128, timer2_clock=(cpu_clock/prescaler)=32768/128=256HZ
	SET_BIT(ASSR,AS2);    //exit external clock=32768 HZ
	SET_BIT(TCCR2,CS20);
	CLR_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	//enable interrupt to compare match
	sei();
	SET_BIT(TIMSK,TOIE2);
	/*
	timer_tick_time=(1/timer2_clock)=1/256 
	occurs interrupt every (1/256)*256=(1S)
	*/
}


void TIMER2_CTC_init_with_interrupt(void)
{
	//determine CTC mode
	CLR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	//load value in OCR2 ,to compare match
	OCR2=80;
	//determine prescaler=1024, timer2_clock=(cpu_clock/prescaler)
	CLR_BIT(ASSR,AS2);    //not exit external clock
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	//enable interrupt to compare match
	sei();
	SET_BIT(TIMSK,OCIE2);
	/*
	timer_tick_time=(1/timer2_clock)=0.128 ms
	occurs interrupt every 0.128*OCR0=0.128*80=(10 ms)
	*/
}

void TIMER2_CTC_wave_nonpwm(void)
{
	//determine CTC mode
	CLR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	//load value in OCR2 ,to compare match
	OCR2=64;
	//determine prescaler=1024, timer2_clock=(cpu_clock/prescaler)
	CLR_BIT(ASSR,AS2);    //not exit external clock
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	//set OC2 as output pin to generetion wave
	SET_BIT(DDRD,PD7);
	//toggle OC2 on compare match
	SET_BIT(TCCR2,COM20);
	CLR_BIT(TCCR2,COM21);
	/*
	timer_tick_time=(1/timer2_clock)=0.128 ms
	pulse repeated every 0.128*OCR0=0.128*64,cycle repeated every 2*(0.128*64)= ?? ms
	*/
}

void TIMER2_fast_pwm_wave(void)
{
	//determine fast PWM mode
	SET_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	//load value in OCR2 ,to compare match
	OCR2=64;
	//determine prescaler=1024, timer2_clock=(cpu_clock/prescaler)
	CLR_BIT(ASSR,AS2);    //not exit external clock
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	//set OC2 as output pin to generetion wave
	SET_BIT(DDRD,PD7);
	//clear OC2 on compare match and set OC2 at bottom=0
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	/*
	timer_tick_time=(1/timer2_clock)=0.128 ms
	on_pulse repeated every 0.128*OCR0=0.128*64 and off_pulse repeated every 0.128*(256-OCR0)=0.128*(256-64) ,cycle repeated every 0.128*256=?? ms
	*/
}

void TIMER2_phase_correct_pwm_wave(void)
{
	//determine phase correct PWM mode
	SET_BIT(TCCR2,WGM20);
	CLR_BIT(TCCR2,WGM21);
	//load value in OCR2 ,to compare match
	OCR2=64;
	//determine prescaler=1024, timer2_clock=(cpu_clock/prescaler)
	CLR_BIT(ASSR,AS2);    //not exit external clock
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	//set OC2 as output pin to generetion wave
	SET_BIT(DDRD,PD7);
	//clear OC2 on compare match when up_counting and set OC2 on compare match when downcounting
	CLR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
	/*
	timer_tick_time=(1/timer2_clock)=0.128 ms
	cycle repeated every 0.128*2*255=?? ms
	*/
}

void TIMER1_fast_pwm_8bit_wave(void)
{
	//determine fast PWM 8_bit mode
	SET_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	//load value in OCR1A and OCR1B ,to compare match
	OCR1A=64;
	OCR1B=64;
	//determine prescaler=1024, timer1_clock=(cpu_clock/prescaler)
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	SET_BIT(TCCR1B,CS12);
	//set OC1A and OC1B as output pin to generetion wave
	SET_BIT(DDRD,PD5);
	SET_BIT(DDRD,PD4);
	//clear OC1A on compare match and set OC1A at bottom=0
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	//set OC1B on compare match and clear OC1B at bottom=0
	SET_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
	/*
	timer_tick_time=(1/timer1_clock)=0.128 ms
	on_pulse repeated every 0.128*OCR1=0.128*64 and off_pulse repeated every 0.128*(256-OCR1)=0.128*(256-64) ,cycle repeated every 0.128*256=?? ms
	*/
}

void TIMER1_ICU_init(void)
{
	//determine normal mode
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	//determine prescaler=1, timer1_clock=(cpu_clock/prescaler)
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	//set ICP1 as input pin to received wave
	CLR_BIT(DDRD,PD6);
	//filter noise on input capure pin
	SET_BIT(TCCR1B,ICNC1);
	//clear flag
	SET_BIT(TIFR,ICF1); 
}

void TIMER1_stop_ICU(void)
{
	TCCR1A=0;
	TCCR1B=0;
}


unsigned short TIMER1_ICU_raising(void)
{
	unsigned short val;
	//take capure when raising
	SET_BIT(TCCR1B,ICES1);
	// Wait for capture event and Read ICR1
	while(READ_BIT(TIFR,ICF1)==0);
	val=ICR1;
	SET_BIT(TIFR,ICF1); //clear flag
	return val;
	/*
	timer_tick_time=(1/timer1_clock)
	*/
}

unsigned short TIMER1_ICU_failing(void)
{
	unsigned short val;
	//take capure when failing
	CLR_BIT(TCCR1B,ICES1);
	// Wait for capture event and Read ICR1
	while(READ_BIT(TIFR,ICF1)==0);
	val=ICR1;
	SET_BIT(TIFR,ICF1); //clear flag
	return val;
	/*
	timer_tick_time=(1/timer1_clock)
	*/
}

void TIMER1_ICU_init_with_interrupt(void)
{
	//determine normal mode
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	//determine prescaler=1, timer1_clock=(cpu_clock/prescaler)
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	//set ICP1 as input pin to received wave
	CLR_BIT(DDRD,PD6);
	//filter noise on input capure pin
	SET_BIT(TCCR1B,ICNC1);
	//take capure when raising
	SET_BIT(TCCR1B,ICES1);
	//enable interrupt when capture event
	sei();
	SET_BIT(TIMSK,TICIE1);
}