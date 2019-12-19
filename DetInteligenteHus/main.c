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
#include "Step/StepMotor.h"
#include "Interupt/Interupts.h"

#define F_CPU 16000000UL

void init (){
	UartInit();
	init_KeyPad();
	initinterupt();
	initLCD();
	ADCINIT();
	init_Timer5();
	init_StepMotor();
	sei();	 // Enable Global Interrupt
}

void initLCD(){
	lcd_clrscr(); //clear display
	lcd_init(LCD_DISP_ON_CURSOR_BLINK); //Init LCD
	lcd_puts("Welcome Home\n");
}

volatile static int alarm; //volatile so it doesn't throw it away, would do it some times if missing

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
	alarm = 1;
	while(1) {
		DecodeKeyboard(ColumnScan(),ReadRows()); //Look in keypad.h for information about this Function'
		while (alarm == 1)
		{
			alarm = AlarmDecodeKeyboard(ColumnScan(),ReadRows());
		}
	}
}