/*
 * Interupts.h
 *
 * Created: 19-12-2019 19:01:32
 *  Author: mart624n
 */ 


#ifndef INTERUPTS_H_
#define INTERUPTS_H_

#define interupt_PCICR PCICR; //Interrupt Control Register. Datasheet 15.2.5
#define interupt_PCIE0 PCIE0; //Bit 0 Pin Change Interrupt Enable 0. Datasheet 15.2.5
#define interupt_PCIE1 PCIE1; //Bit 1 Pin Change Interrupt Enable 1. Datasheet 15.2.5
#define interupt_PCIE2 PCIE2; //Bit 2 Pin Change Interrupt Enable 1. Datasheet 15.2.5

#define interupt_PCMSKX PCMSK0; //Pin Change Mask Register 0. Datasheet 15.2.9
#define interupt_PCINITX PCINT0; //Check Datasheet 15.2.9 for corresponding I/O Pin

void initinterupt(void);


#endif /* INTERUPTS_H_ */