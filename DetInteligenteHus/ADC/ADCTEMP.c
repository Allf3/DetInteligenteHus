/*
* ADCTEMP.c
*
* Created: 17-12-2019 13:05:34
*  Author: mart624n
*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <stdio.h>

float ADCTEMP(){
	char buffer[7];
	float temp;
	float tempK;
	float tempC;
	
	temp = log(10000.0 * (1024.0/ADC -1));		// get the ADC value, datasheet 26.8.4.1
	tempK =  1/(0.001129148+(0.000234125+(0.0000000876741*temp*temp))* temp);
	tempC = tempK - 273.15;
	ADCSRA |= (1 << ADSC);						// start the next ADC conversion
	//dtostrf(tempC,7,3,buffer);
	return tempC;
}

void ADCINIT(){
	ADMUX |= (1 << REFS0);	// 5V supply used for ADC reference, select ADC channel 0 26.8.2 Table 26-4, datasheet 26.8.1
	//ADC0 is standard.
	DIDR0 = (1 << ADC0D);	// disable digital input on ADC0 pin, Datasheet 26.8.6
	// enable ADC, start ADC, ADC clock = 16MHz / 128 = 125kHz, Datasheet 26.8.3
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Datasheet 26.8.3
}