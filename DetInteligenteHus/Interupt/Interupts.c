/*
 * Interupts.c
 *
 * Created: 19-12-2019 19:01:47
 *  Author: mart624n
 */ 

void initinterupt(){
	interupt_PCICR |= (1<<interupt_PCIE0);					// Pin Change Interrupt Enable 0, datasheet 15.2.5
	interupt_PCMSKX |= (1<<PCINT0);					// Pin Change Mask Register, datasheet 15.2.8
	sei();									// Enables Global Interrupt
}