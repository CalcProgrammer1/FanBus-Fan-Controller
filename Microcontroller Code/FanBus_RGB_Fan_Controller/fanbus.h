/*---------------------------------------------*\
|  RGB Fan Controller - Serial Port Header File	|
| Implements a buffered serial I/O port using 	|
|  USART0 on the ATMega168 and compatible chips	|
|												|
|  Adam Honse (CalcProgrammer1), Feb. 2010		|
|												|
|  This code may be freely reused for non-		|
|  commercial use.								|
\*---------------------------------------------*/
#ifndef FANBUS_H
#define FANBUS_H

#include <avr/io.h>
#include <avr/interrupt.h>

// USART0_Init
// Initializes the serial port
// Takes an AVR USART speed (see the ATMega168 datasheet)
void fanbus_init(unsigned int baud);

// FanBus_Transmit
// Transmits a single byte of data
void fanbus_transmit(unsigned char data);

#endif
