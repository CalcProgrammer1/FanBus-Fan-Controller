/*-----------------------------------------*\
|  RGB Fan Controller - Save Header File	|
|  Provides functions to save the current	|
|  state, restore the state, and start up	|
|  the controller with the saved state		|
|											|
|  Adam Honse (CalcProgrammer1), 2010		|
\*-----------------------------------------*/
#ifndef SAVE_H
#define SAVE_H

#include "fan.h"
#include <util/delay.h>
#include <avr/eeprom.h>
#define F_CPU 8000000

//  Save State
//  Saves the current state to EEPROM memory
void saveState();

//  Restore State
//  Restores the saved state from EEPROM
void restoreState();

//  Read EEPROM
//  Used internally to read saved values out of
//  EEPROM memory
void readEeprom();

//  Start Up
//  Turns on the LED's and fan from the saved state
void startUp();

#endif
