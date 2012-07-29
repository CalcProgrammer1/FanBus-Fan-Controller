/*-----------------------------------------------------*\
|   Atmel ATMega168 RGB LED Fan Controller with PWM		|
| This project is a PC fan controller that provides all	|
| fan speed control options, RPM feedback, as well as 	|
| full 24-bit control over 4 RGB LED's mounted in the 	|
| fan.  The LED's use software pulse-width modulation	|
| (PWM) while the fan motor uses hardware PWM with step-|
| up transistors to switch the +12V line.				|
|														|
| Designed by Adam Honse (CalcProgrammer1), 2010		|
| Visit www.instructables.com to see a full writeup on	|
|  the associated hardware for this project				|
\*-----------------------------------------------------*/

//Using the internal oscillator at 8MHz
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "rgb.h"
#include "fan.h"
#include "serial.h"
#include "readFrame.h"
#include "save.h"

int main()
{
  USART0_Init(12);
  setupLEDs();
  setupFan();
  setupCount();
  startUp();
  while(1)
  {
    readFrame();
  }
}

