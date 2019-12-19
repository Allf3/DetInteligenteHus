/*
 * TimerMotor.c
 *
 * Created: 18-12-2019 08:37:05
 *  Author: mart624n
 */

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void init_Timer5(){
	//Timer FOund on Datasheet 17.11.1
	TCCR5A |= (1<<COM1C1); //FAST PWM: Compare output MODE (Table 16-3) (1<<COM1A1) | (1<<COM1B1) | 
	
	//Waveform Generation Mode: Mode 3 Fast PWM: WGM10 = 1, WGM1 = 1 (Table 17-2)
	TCCR5A |= (1<<WGM50); //17.11.4
	
	TCCR5B |= (1<<CS51) | (1<<CS50) | (1<<WGM52); // 17.11.8
	
	DDRL |= (1<<PB7) | (1<<PB6) | (1<<PB5); //Datasheet 13.3.11
	
	OCR5C = 0;
}

void Set_OCR5C(int val){
	OCR5C = val;
}