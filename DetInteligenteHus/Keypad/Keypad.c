/*
* Keypad.c
*
* Created: 17-12-2019 09:14:29
*  Author: mart624n
*/
#define F_CPU 16000000UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "../LCD/lcd.h"
#include "Keypad.h"
#include <avr/interrupt.h>
#include "../ADC/ADCTEMP.h"
#include "../Step/StepMotor.h"
#include <string.h>

const char MatrixKeypad[4][4] =
{{'2','3','A','1'},
{'5','6','B','4'},
{'8','9','C','7'},
{'0','#','D','*'}}; //Array of the keypad, with char's.

int ReadRows()
{
	if (~PINK & (1<<PK7)) //Row 1
	{
		Row_Delay;
		if (~PINK & (1<<PK7)) //Fixes input glitch from Matrix keypad
		{
			return 1;
		}
	}
	else if (~PINK & (1<<PK6)) //ROW 2
	{
		Row_Delay;
		if (~PINK & (1<<PK6)) //Fixes input glitch from Matrix keypad
		{
			return 2;
		}
	}
	else if (~PINK & (1<<PK5)) //ROW 3
	{
		Row_Delay;
		if (~PINK & (1<<PK5)) //Fixes input glitch from Matrix keypad
		{
			return 3;
		}
	}
	else if (~PINK & (1<<PK4)) //ROW4
	{
		Row_Delay;
		if (~PINK & (1<<PK4)) //Fixes input glitch from Matrix keypad
		{
			return 4;
		}
	}
	return 0;
}

int ColumnScan(){
	
	PORTK  |= (1<<PK0) | (1<<PK1) | (1<<PK2) | (1<<PK3);
	static counter = 1;
	if (counter == 1) //COL 4
	{
		PORTK &= ~(1<<PK0); //1111 1110
		Col_Delay;
		_delay_ms(50);
		counter++; //Pludser counteren så den går hen i næste if statement næstegang denne er kørt.
		return 4; //return value for colume 4
	}
	else if (counter == 2) //COL 3
	{
		PORTK &= ~(1<<PK1); //1111 1101
		Col_Delay;
		_delay_ms(50);
		counter++;
		return 3; //return value for colume 3
	}
	else if (counter == 3) // COL 2
	{
		PORTK &= ~(1<<PK2); //1111 1011
		Col_Delay;
		_delay_ms(50);
		counter++;
		return 2; //return value for colume 2
	}
	else if (counter == 4) //COL 1
	{
		PORTK &= ~(1<<PK3); //1111 1101
		Col_Delay;
		_delay_ms(50);
		counter = 1;
		return 1; //return value for colume 1
	}
	else
	{
		counter == 1;
		return 0;
	}
	return 0;
}

void DecodeKeyboard(int col, int row){
	if (row != 0 && col != 0)
	{
		char matrixvalue = MatrixKeypad[row-1][col-1]; // Takes a specific value out from the array based on input
		
		printf("%c",matrixvalue); // Show's the result in a teraterm / serial connection.
		KeyFunctions(matrixvalue); //Display's char instead of puts that takes array of char and displays it.
		_delay_ms(150);	 //This delay made the keypad work very smoothly and make you control how many number's you press.
	}
}

void KeyFunctions(char input){
	static int currentmenu;
	char buffer[5];
	switch (input)
	{
		case '*':
		currentmenu = 0;
		lcd_clrscr();
		lcd_puts("Welcome Home \n");
		break;
		case 'C':
		currentmenu = 2;
		while (currentmenu == 2)
		{
			lcd_clrscr();
			dtostrf(ADCTEMP(),7,3,buffer);
			lcd_puts("Welcome Home \n");
			lcd_puts(buffer);
			lcd_puts("C");
			_delay_ms(1000);
			
			DecodeKeyboard(ColumnScan(),ReadRows());
		}
		break;
		case 'D':
			TurnRight(512);
		break;
		case 'A':
		lcd_clrscr();
		Set_OCR5C(200);
		//Skal være en blæser der går igang her.
		lcd_puts("AC Startet");
		break;
		case '#':
		
		break;
		case 'B':
		currentmenu = 0;
		lcd_clrscr();
		Set_OCR5C(0);
		lcd_puts("All Functions \nStopped..");
		break;
		default:
		lcd_putc(input);
		break;
	}
}

int AlarmDecodeKeyboard(int col, int row){
	char userinput[3];
	static char password[] = "1234";
	int atempts;
	static int inputsint = 0;
	char result[8];
	
	if ((strcmp(userinput,password) != 0))
	{
		if (row != 0 && col != 0)
		{
			result[inputsint] = MatrixKeypad[row-1][col-1];
			printf("%d", inputsint);
			
			lcd_puts("#");
			inputsint++;
			return 1;
		}
		if (inputsint == 4)
		{
			result[4] = '\0'; //if this isn't there it wouldn't work, shows that char array stops
			strcpy(userinput,result);
			atempts++;
		}
	}
	else if (strcmp(userinput,password) == 0)
	{
		printf("%d", result);
		lcd_clrscr();
		lcd_puts("  Alarm Afbrudt\n");
		lcd_puts("  Vent Venligst");
		_delay_ms(7000);
		lcd_clrscr();
		lcd_puts("Welcome Home \n");
		inputsint = 0;
		return 0;
	}
	
	return 1;
}