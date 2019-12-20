/*
* Keypad.h
*
* Created: 16-12-2019 12:29:24
*  Author: mart624n
*/

#define F_CPU 16000000UL
#define Col_Delay _delay_ms(50); // Used to delay col, so it doesn't read so fast
#define Row_Delay _delay_ms(10); //  Used to delay row, so it doesn't read so fast

#define Keypad_Aktiv_DDR DDRK; //switch with desired Data Direction Register. Datasheet 13.4.30
#define Keypad_PINX PINK; //Switch with desired Input Pins Address. Datasheet 13.4.31
#define Keypad_PORTX PORTK; //switch with desired Data Register. Datasheet 13.4.29

//Colume Scan
#define Keypad_PX0 PK0; // Change this if other output pin is used
#define Keypad_PX1 PK1; // Change this if other output pin is used
#define Keypad_PX2 PK2; // Change this if other output pin is used
#define Keypad_PX3 PK3; // Change this if other output pin is used
//ROW READ
#define Keypad_PX4 PK4; // Change this if other output pin is used
#define Keypad_PX5 PK5; // Change this if other output pin is used
#define Keypad_PX6 PK6; // Change this if other output pin is used
#define Keypad_PX7 PK7; // Change this if other output pin is used

#define Keypad_Aktiv_PX (1<<Keypad_PX0) | (1<<Keypad_PX1) | (1<<Keypad_PX2) | (1<<Keypad_PX3); //Aktivates all ports

#include <stdbool.h>

void init_KeyPad(void);

int ReadRows(void); //Read Rows for Keypad to work, return's row number

int ColumnScan(void); //Read's column when keypad is clicked, return's column number

void DecodeKeyboard(int col, int row); //return's output to lcd screen

void KeyFunctions(char input); //MENU 

int StepKeyboard(int col, int row); // MENU for stepmotor

int AlarmDecodeKeyboard(int col, int row);

/* KEYPAD_H_ */