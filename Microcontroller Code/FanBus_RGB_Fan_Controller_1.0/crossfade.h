/*-----------------------------------------*\
|  RGB Fan Controller - Cross Fade Header	|
|  Cross-fades from the existing color		|
|  to the crossfade[12] array.				|
|											|
|  Based on Arduino ColorCrossfader			|
|    Clay Shirky, April 2007				|
| http://www.arduino.cc/en/Tutorial/ColorCrossfader
|											|
|  Adapted to AVR-GCC and modified by		|
|  Adam Honse (CalcProgrammer1), 2010		|
\*-----------------------------------------*/

#ifndef CROSSFADE_H
#define CROSSFADE_H

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// crossFade
//  Fades the LED's from their existing colors to the new colors
//  as listed in the crossfade[12] array
//  Initialize the entire crossfade array before calling this function
void crossFade(char wait);

// calculateVal
//  Calculates color values, used internally
char calculateVal(int step, char val, int i);

// calculateStep
//  Calculate step values, used internally
int calculateStep(char prevValue, char endValue);

#endif
