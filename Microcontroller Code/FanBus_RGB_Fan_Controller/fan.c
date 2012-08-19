/*---------------------------------------------*\
|  RGB Fan Controller - Fan Code File			|
|  Contains all the functionality to control	|
|  fan speed as well as code to count the fan	|
|  RPM using Timer/Counter1 and calculate the	|
|  RPM by counting pulses on the sensor wire	|
|												|
|  Adam Honse (CalcProgrammer1), 2010			|
\*---------------------------------------------*/

#include "fan.h"

unsigned int FanRPM = 0;

//Sets up fan PWM output on Timer/Counter 2
//Fan is connected on pin 5 (OC2B) as output
//Connect fan using a transistor pair to switch 12V
void setupFan()
{
   //Fan on pin 5 (OC2B)
   DDRD   |= (1 << 3);

   //Fan starts out off
   OCR2B = 0;
     
   // Set up fan for PWM
   TCCR2A  = ((1 << COM2B1) | (1 << WGM20) | (1 << WGM21));
   TCCR2B  = ((1 << CS20) | (0 << CS21) | (0 << CS22) | (0 << WGM22));
   TIMSK2  = (0<<OCIE2B); //Enable Timer2 Overflow Interrupt
   sei();
}

char getFanSpeed()
{
	return OCR2B;
}

void setFanSpeed(char speed)
{
	OCR2B = speed;
}

unsigned char * getFanSpeedPointer()
{
   return &OCR2B;
}

unsigned int * getFanRPMPointer()
{
   return &FanRPM;
}

void setupFanRPMCount()
{
  TCCR1A=0;                 // reset timer/counter1 control register A
  TCCR1B=0;              	// reset timer/counter1 control register A
  TCNT1=0;           		// counter value = 0
  //Clock source on T1, falling edge (fan pulls down)
  TCCR1B = (1 << CS10) | (1 << CS11) | (1 << CS12);

  //Setup watchdog timer for 1hz refresh
  //WDTCSR = (1 << WDCE);
  //WDTCSR = (1 << WDP0) | (1 << WDP3);
  //WDTCSR = (1 << WDIE);
  WD_SET(WD_IRQ, WDTO_1S);
}

int fanRPM()
{
  return FanRPM;
}

ISR(WDT_vect)
{
  FanRPM = TCNT1*30;
  TCNT1 = 0;
}

