/*
* Keypad.h
*
* Created: 16-12-2019 12:29:24
*  Author: mart624n
*/
#define F_CPU 16000000UL
#define Col_Delay _delay_ms(50); //Bruger jeg ligesom en const value i C# så skal jeg bare ændre det et sted
#define Row_Delay _delay_ms(10); // -----||-----
#include <stdbool.h>

int ReadRows(void); //Read Rows for Keypad to work, return's row number

int ColumnScan(void); //Read's column when keypad is clicked, return's column number

void DecodeKeyboard(int col, int row); //return's output to lcd screen

void KeyFunctions(char input); //

int AlarmDecodeKeyboard(int col, int row);

/* KEYPAD_H_ */