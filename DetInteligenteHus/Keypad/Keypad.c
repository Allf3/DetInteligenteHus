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
	
	void init_KeyPad(){
		Keypad_Aktiv_DDR |= 0x0f; // PK0-3 Output PK4-7 Input
			
		Keypad_PORTX |= 0xff; //Aktivere alle Portene til at være Logical 1
	}

int ReadRows()
{
	if (~Keypad_PINX & (1<<Keypad_PX7)) //Row 1
	{
		Row_Delay;
		if (~Keypad_PINX & (1<<Keypad_PX7)) //Fixes input glitch from Matrix keypad
		{
			return 1;
		}
	}
	else if (~Keypad_PINX & (1<<Keypad_PX6)) //ROW 2
	{
		Row_Delay;
		if (~Keypad_PINX & (1<<Keypad_PX6)) //Fixes input glitch from Matrix keypad
		{
			return 2;
		}
	}
	else if (~Keypad_PINX & (1<<Keypad_PX5)) //ROW 3
	{
		Row_Delay;
		if (~Keypad_PINX & (1<<Keypad_PX5)) //Fixes input glitch from Matrix keypad
		{
			return 3;
		}
	}
	else if (~Keypad_PINX & (1<<Keypad_PX4)) //ROW4
	{
		Row_Delay;
		if (~Keypad_PINX & (1<<Keypad_PX4)) //Fixes input glitch from Matrix keypad
		{
			return 4;
		}
	}
	return 0;
}

int ColumnScan(){
	
	Keypad_PORTX  |= Keypad_Aktiv_PX;
	static counter = 1;
	if (counter == 1) //COL 4
	{
		Keypad_PORTX &= ~(1<<Keypad_PX0); //1111 1110
		Col_Delay;
		_delay_ms(50);
		counter++; //Pludser counteren så den går hen i næste if statement næstegang denne er kørt.
		return 4; //return value for colume 4
	}
	else if (counter == 2) //COL 3
	{
		Keypad_PORTX &= ~(1<<Keypad_PX1); //1111 1101
		Col_Delay;
		_delay_ms(50);
		counter++;
		return 3; //return value for colume 3
	}
	else if (counter == 3) // COL 2
	{
		Keypad_PORTX &= ~(1<<Keypad_PX2); //1111 1011
		Col_Delay;
		_delay_ms(50);
		counter++;
		return 2; //return value for colume 2
	}
	else if (counter == 4) //COL 1
	{
		Keypad_PORTX &= ~(1<<Keypad_PX3); //1111 1101
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

int StepKeyboard(int col, int row){
	//360 degress = 512 is max steps
	int step_postion = 1;
	if (row != 0 && col != 0)
	{
		char matrixvalue = MatrixKeypad[row-1][col-1]; // Takes a specific value out from the array based on input
		
		switch(matrixvalue){
			case '6'
				TurnRight(step_postion);
				return 3; //Current menu position
			break;
			case '4'
				TurnLeft(step_postion);
				return 3; //Current menu position
			break;
			case '5'
				return 3;
			break;
			case '*'
				return 0;
			break;
		}
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
			lcd_clrscr();
			lcd_puts("Garage Is Opening");
			currentmenu = 3
			while (currentmenu == 3)
			{
				currentmenu = StepKeyboard(ColumnScan(),ReadRows()); 
			}
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
	else if (strcmp(userinput,password) == 0) //Compares char array's if same it return's 0 else a negative number
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