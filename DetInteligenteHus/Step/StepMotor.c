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
	Aktiv_Port_Step |= Aktiv_Ports_Step;
}

void TurnRight(int turns){
	int index;
	for (index = 0; index < turns; index++)
	{
		PortX_used &= 0x00;
		Delay_OnStep;
		PortX_used |= (1<<Step_PX0); //0001 step1
		Delay_OnStep;
		PortX_used |= (1<<Step_PX1); //0011 step2
		Delay_OnStep;
		PortX_used = (1<<Step_PX1); //0010 step3
		Delay_OnStep;
		PortX_used |= (1<<Step_PX2);  //0110 step4
		Delay_OnStep;
		PortX_used = (1<<Step_PX2); //0100 step5
		Delay_OnStep;
		PortX_used |= (1<<Step_PX3); //1100 step6
		Delay_OnStep;
		PortX_used = (1<<Step_PX3); //1000 step7
		Delay_OnStep;
		PortX_used = (1<<Step_PX0) | (1<<Step_PX3); //step 1001 step8
	}
}

void TurnLeft(int turns){
	int index;
	for (index = 0; index < turns; index++)
	{
		PortX_used &= 0x00;
		Delay_OnStep;
		PortX_used |= (1<<Step_PX3); //1000 step1
		Delay_OnStep;
		PortX_used |= (1<<Step_PX2); //1100 step2
		Delay_OnStep;
		PortX_used = (1<<Step_PX2); //0100 step3
		Delay_OnStep;
		PortX_used |= (1<<Step_PX1);  //0110 step4
		Delay_OnStep;
		PortX_used = (1<<Step_PX1); //0010 step5
		Delay_OnStep;
		PortX_used |= (1<<Step_PX0); //0011 step6
		Delay_OnStep;
		PortX_used = (1<<Step_PX0); //0001 step7
		Delay_OnStep;
		PortX_used = (1<<Step_PX0) | (1<<Step_PX3); //step 1001 step8
	}
}