/*
 * ADCTEMP.h
 *
 * Created: 17-12-2019 13:02:34
 *  Author: mart624n
 */ 


#ifndef ADCTEMP_H_
#define ADCTEMP_H_

#define ADC_ADCSRX ADCSRA; // ADC Control and Status Register A. Datasheet 26.8.3
#define ADC_StartConversion (1 << ADSC); // Datasheet 26.8.3
#define ADC_ADMUX ADMUX; // ADC Multiplexer Selection Register
#define ADC_REFS0 REFS0; // Voltage Refrence Selections for ADC, Datasheet 26.8.1 Table 26-3
#define ADC_REFS0 REFS1; //----||----
#define ADC_DIDR0 DIDR0; //Digital input Disable Register 0. Datasheet 26.8.6
#define ADC_ADC0D ADC0D; //disable digital input on ADC0 pin, Datasheet 26.8.6

float ADCTEMP(void);

void ADCINIT(void);

#endif /* ADCTEMP_H_ */