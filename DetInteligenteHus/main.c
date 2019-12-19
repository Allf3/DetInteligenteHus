#include <stdio.h>
#include "stdio_setup.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Keypad/Keypad.h"
#include "ADC/ADCTEMP.h"
#include "Timers/TimerMotor.h"

#define F_CPU 16000000UL

void init (){
	UartInit();
	sei();	 // Enable Global Interrupt

	DDRK |= 0x0f; // PK0-3 Output PK4-7 Input
	
	PORTK |= 0xff; //Aktivere alle Portene til at være Logical 1
}

void initLCD(){
	lcd_clrscr(); //clear display
	lcd_init(LCD_DISP_ON_CURSOR_BLINK); //Init LCD
	lcd_puts("Welcome Home\n");
}

void initinterupt(){
	PCICR |= (1<<PCIE0);					// Pin Change Interrupt Enable 0, datasheet 15.2.5
	PCMSK0 |= (1<<PCINT0);					// Pin Change Mask Register, datasheet 15.2.8
	//
	sei();									// Enables Global Interrupt
}

volatile static int alarm;

ISR(PCINT0_vect)
{
	lcd_clrscr();
	lcd_puts("Alarm!!");
	_delay_ms(10000);
	lcd_clrscr();
	_delay_ms(5000);
	lcd_puts("Alarm!!");
	_delay_ms(10000);
	lcd_clrscr();
	lcd_puts("Indtast Kode:\n");
	Set_OCR5C(0);
	alarm = 1;
}

int main(void)
{
	init();
	initinterupt();	
	initLCD();
	ADCINIT();
	init_Timer5();
	alarm = 1;
	while(1) {			
		DecodeKeyboard(ColumnScan(),ReadRows()); //Look in keypad.h for information about this Function'
		while (alarm == 1)
		{
			alarm = AlarmDecodeKeyboard(ColumnScan(),ReadRows());
		}
		//alarm = 0;
	}
}