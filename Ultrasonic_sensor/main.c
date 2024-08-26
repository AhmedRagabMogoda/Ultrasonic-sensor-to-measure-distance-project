/*
 * Ultrasonic_sensor.c
 *
 * Created: 8/24/2024 1:06:00 PM
 * Author : Ahmed Ragab
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include "macro_function.h"
#include "TIMER.h"
#include "LCD.h"
#define prescaling 1
#define speed_of_sound 34600 // 346 M/S = 34600 CM/S

int main(void)
{
   LCD_init();
   SET_BIT(DDRD,PD0);
   unsigned short rasing_value,failing_value;
   unsigned short on_pulse,distance;
   float time_on_pulse;
    while (1) 
    {
		SET_BIT(PORTD,PD0); //trigger to start
		_delay_us(10);
		CLR_BIT(PORTD,PD0);
		TIMER1_ICU_init();
		rasing_value=TIMER1_ICU_raising();
		failing_value=TIMER1_ICU_failing();
		TIMER1_stop_ICU();
		on_pulse=failing_value-rasing_value;
		time_on_pulse=on_pulse*((float)prescaling/F_CPU);
		distance=(speed_of_sound*time_on_pulse)/2; // CM
		if (distance>80)
		{
			LCD_clr_screen();
			LCD_send_string("  No object");
			_delay_ms(1000);
		}
		else
		{
			LCD_move_cursor(1,1);
			LCD_send_string("distance=");
			LCD_send_data(distance/10+48);
			LCD_send_data(distance%10+48);
			LCD_send_string("cm");
		}
		
    }
}

