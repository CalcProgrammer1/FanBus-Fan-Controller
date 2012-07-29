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

// setupFan
//  Sets up fan PWM output on Timer/Counter 2
//  Fan is connected on pin 5 (OC2B) as output
//  Connect fan using a transistor pair to switch 12V
void setupFan();

// setFanSpeed
//  Sets fan speed by changing Timer/Counter 2 register for OC2B
//  Fan Speed is a single unsigned byte (0 to 255)
void setFanSpeed(char speed);

// getFanSpeed
//  Returns the Timer/Counter2 PWM value, which is the
//  current fan speed
char getFanSpeed();

// setupCount
//  Sets up Timer/Counter1 to count pulses on the T1 pin
//  This counts the fan RPM using the sensor wire
void setupCount();

// calculateRPM
//  This function must be called exactly once per second to compute
//  an accurate RPM reading
void calculateRPM();

// fanRPM
//  Returns current fan RPM, this is only accurate if calculateRPM is called
//  exactly once per second
int fanRPM();

#endif
