/*-----------------------------------------*\
|  FanBus RGB Fan Controller 1.0			|
| Digital PC Fan Controller with half-duplex|
| FanBus serial interface powered by ATMega	|
| 168.  Features 4 RGB LEDs, speed control,	|
| and RPM monitoring.						|
|											|
| Adam Honse (CalcProgrammer1), 2/2/2011	|
\*-----------------------------------------*/

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
  USART0_Init(12); 		//38400 baud
  setupLEDs();
  setupFan();
  setupCount();
  startUp();
  while(1)
  {
    readFrame();
  }
}

