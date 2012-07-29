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
#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <avr/interrupt.h>

// USART0_Init
// Initializes the serial port
// Takes an AVR USART speed (see the ATMega168 datasheet)
void USART0_Init(unsigned int baud);

// USART0_Transmit
// Transmits a single byte of data
void USART0_Transmit(unsigned char data);

// USART0_Read
// Buffered read on USART0
// Pulls the first byte from the serial port buffer and deletes it
int USART0_Read(void);

// USART0_Flush
// Flush the USART0 buffer
// Deletes any data currently in the read buffer
void USART0_Flush();

// USART0_Available
// Returns 1 if there is at least one unread byte in the buffer
// Returns 0 if there is no unread bytes in the buffer
int USART0_Available();

#endif
