/*---------------------------------*\
| Adam Honse (CalcProgrammer1)		|
| RGB LED Software PWM Header		|
| Opens right side of ATMega168 for |
| software PWM for 4 RGB LED's		|
| Uses Timer0, PB0-PB5, and PC0-PC5 |
\*---------------------------------*/
#ifndef RGB_H
#define RGB_H

#include <avr/io.h>
#include <avr/interrupt.h>

//Pin mappings for LED PWM
#define LED1_RED_CLEAR (pinlevelB &= ~(1 << PORTB0)) //LED1 Red is PB0
#define LED1_GRN_CLEAR (pinlevelB &= ~(1 << PORTB1)) //LED1 Green is PB1
#define LED1_BLU_CLEAR (pinlevelB &= ~(1 << PORTB2)) //LED1 Blue is PB2

#define LED2_RED_CLEAR (pinlevelB &= ~(1 << PORTB3)) //LED2 Red is PB3
#define LED2_GRN_CLEAR (pinlevelB &= ~(1 << PORTB4)) //LED2 Green is PB4
#define LED2_BLU_CLEAR (pinlevelB &= ~(1 << PORTB5)) //LED2 Blue is PB5

#define LED3_RED_CLEAR (pinlevelC &= ~(1 << PORTC0)) //LED3 Red is PC0
#define LED3_GRN_CLEAR (pinlevelC &= ~(1 << PORTC1)) //LED3 Green is PC1
#define LED3_BLU_CLEAR (pinlevelC &= ~(1 << PORTC2)) //LED3 Blue is PC2

#define LED4_RED_CLEAR (pinlevelC &= ~(1 << PORTC3)) //LED4 Red is PC3
#define LED4_GRN_CLEAR (pinlevelC &= ~(1 << PORTC4)) //LED4 Green is PC4
#define LED4_BLU_CLEAR (pinlevelC &= ~(1 << PORTC5)) //LED4 Blue is PC5

// setupLEDs
//  Sets up Timer0 to overflow and enables the overflow interrupt
//  ISR provided in source code drives the software PWM every time
//  timer0 overflows.
void setupLEDs();

#endif
