/*-----------------------------------------*\
|  RGB Fan Controller - Fan Control Header	|
| This file provides functions that control	|
| the fan motor as well as run the RPM		|
| counter on Timer/Counter 1 and computes	|
| the RPM values							|
| Uses Timer/Counter 1 and 2				|
|											|
|  Adam Honse (CalcProgrammer1), 2010		|
|											|
|  This code is free to use in all your non-|
| commercial projects.						|
\*-----------------------------------------*/
#ifndef FAN_H
#define FAN_H

#include "wd.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// setupFan
//  Sets up fan PWM output on Timer/Counter 2
//  Fan is connected on pin 5 (OC2B) as output
//  Connect fan using a transistor pair to switch 12V
void setupFan();

// getFanSpeedPointer
//  Returns the address of the Fan Speed Register (OCR2B)
unsigned char * getFanSpeedPointer();

unsigned int * getFanRPMPointer();

char getFanSpeed();

void setFanSpeed(char speed);

// setupCount
//  Sets up Timer/Counter1 to count pulses on the T1 pin
//  This counts the fan RPM using the sensor wire
void setupFanRPMCount();

// calculateRPM
//  This function must be called exactly once per second to compute
//  an accurate RPM reading
void calculateRPM();

// fanRPM
//  Returns current fan RPM, this is only accurate if calculateRPM is called
//  exactly once per second
int fanRPM();

#endif
