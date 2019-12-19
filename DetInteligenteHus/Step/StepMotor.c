/*
 * StepMotor.c
 *
 * Created: 19-12-2019 12:21:28
 *  Author: mart624n
 */
//512 turns are 360 degrees. 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void init_StepMotor(){
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);
}

void TurnRight(int turns){
	int index;
	for (index = 0; index < turns; index++)
	{
		PORTC &= 0x00;
		_delay_ms(20);
		PORTC |= (1<<PC0); //0001 step1
		_delay_ms(20);
		PORTC |= (1<<PC1); //0011 step2
		_delay_ms(20);
		PORTC = (1<<PC1); //0010 step3
		_delay_ms(20);
		PORTC |= (1<<PC2);  //0110 step4
		_delay_ms(20);
		PORTC = (1<<PC2); //0100 step5
		_delay_ms(20);
		PORTC |= (1<<PC3); //1100 step6
		_delay_ms(20);
		PORTC = (1<<PC3); //1000 step7
		_delay_ms(20);
		PORTC = (1<<PC0) | (1<<PC3); //step 1001 step8
	}
}

void TurnLeft(int turns){
	//not Finished skal lige have vendt alt om.
	int index;
	for (index = 0; index < turns; index++)
	{
		PORTC &= 0x00;
		_delay_ms(20);
		PORTC |= (1<<PC0); //0001 step1
		_delay_ms(20);
		PORTC |= (1<<PC1); //0011 step2
		_delay_ms(20);
		PORTC = (1<<PC1); //0010 step3
		_delay_ms(20);
		PORTC |= (1<<PC2);  //0110 step4
		_delay_ms(20);
		PORTC = (1<<PC2); //0100 step5
		_delay_ms(20);
		PORTC |= (1<<PC3); //1100 step6
		_delay_ms(20);
		PORTC = (1<<PC3); //1000 step7
		_delay_ms(20);
		PORTC = (1<<PC0) | (1<<PC3); //step 1001 step8
	}

}