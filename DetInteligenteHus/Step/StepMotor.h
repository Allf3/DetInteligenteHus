/*
 * StepMotor.h
 *
 * Created: 19-12-2019 12:21:12
 *  Author: mart624n
 */ 


#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

#define Delay_OnStep _delay_ms(20); //commen delay between steps.

#define PortX_used PORTC; //Could be any port, make sure you dont use port with other possible functions

#define Aktiv_Port_Step DDRC; // change if other pinout regestior is used

#define Step_PX0 PC0; // Change this if other output pin is used.

#define Step_PX1 PC1; // Change this if other output pin is used.

#define Step_PX2 PC2; // Change this if other output pin is used.

#define Step_PX3 PC3; // Change this if other output pin is used.

#define Aktiv_Ports_Step (1<<Step_PX0) | (1<<Step_PX1) | (1<<Step_PX2) | (1<<Step_PX3); // Change this if other output pins is used.

void TurnRight(int turns); //Turns stepMotor Right

void init_StepMotor();

void TurnLeft(int turns); //Turns stepMotor Left

#endif /* STEPMOTOR_H_ */