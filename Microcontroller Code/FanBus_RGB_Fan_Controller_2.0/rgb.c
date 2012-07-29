/*-----------------------------------------*\
|  RGB Fan Controller - RGB LED Header File	|
| This provides the code for the LED soft-	|
| PWM pseudo-analog output for dimming the	|
| 4 RGB LED's.  It uses a buffer called		|
| compbuff[12] to store LED values in the 	|
| format:									|
|   [R1,G1,B1,R2,G2,B2,R3,G3,B3,R4,G4,B4]	|
|											|
| Adam Honse (CalcProgrammer1), 2010		|
\*-----------------------------------------*/

#include "rgb.h"

//Variables
unsigned char softcount = 0;   //Software counting byte
unsigned char pinlevelB = 0x3F; //Pin mask, port B (63 for 6 bits)
unsigned char pinlevelC = 0x3F; //Pin mask, port C (63 for 6 bits)
unsigned char compare[12];     //Compare Array

//Use compbuff in your code to set the colors, add it to your file using "extern char compbuff[12]"
unsigned char compbuff[12];    //Compare Buffer

//Set update to 1 to load compbuff
unsigned char update = 0;

void setupLEDs() //Sets up timer0 for soft-PWM of LEDs
{
  //Set up timer0
  TIFR0 = (1 << TOV0);           // clear interrupt flag
  TIMSK0 = (1 << TOIE0);         // enable overflow interrupt
  TCCR0B = (1<<CS00 | 0<<CS01 | 0<<CS02);// start timer, no prescale

  //Set up outputs
  DDRB = 0x3F; //00111111, 6 bits (0 through 5) as OUTPUT
  DDRC = 0x3F;

  //Clear buffer and compare arrays
  for(char i = 0; i < 12; i++)
  {
    compare[i] = 0;
	compbuff[i] = 0;
  }

  //Enable interrupts
  sei();
}

//This is the heart of the software PWM, whenever timer0 overflows this ISR
//performs all the software counting and checking to set the LED PWM for all
//12 channels
ISR(TIMER0_OVF_vect)
{
  PORTB = pinlevelB;            // update output mask B
  PORTC = pinlevelC;            // update output mask C

  if(++softcount == 128) 	//Increment software counter, if it overflows then update compare
  { 						//array with buffer array and turn all the LED's on in output mask
  	if(update == 1)
	{
	    compare[0] = compbuff[0];
	    compare[1] = compbuff[1];
	    compare[2] = compbuff[2];
	    compare[3] = compbuff[3];
	    compare[4] = compbuff[4];
	    compare[5] = compbuff[5];
	    compare[6] = compbuff[6];
	    compare[7] = compbuff[7];
	    compare[8] = compbuff[8];
	    compare[9] = compbuff[9];
	    compare[10] = compbuff[10];
		compare[11] = compbuff[11];
		
		update = 0;
	}
	softcount = 0;
    pinlevelB = 0x3F; //Set all LED's on mask B on
    pinlevelC = 0x3F; //Set all LED's on mask C on
  }

  //Compare each element of the compare array with the current software count
  //If equal, run the appropriate clearing routine to shut off that LED in the
  //port mask, on next iteration of the interrupt the port mask will be applied
  //to the hardware outputs and the LEDs will show the updated state
  if(compare[0] == softcount)  LED1_RED_CLEAR;
  if(compare[1] == softcount)  LED1_GRN_CLEAR;
  if(compare[2] == softcount)  LED1_BLU_CLEAR;

  if(compare[3] == softcount)  LED2_RED_CLEAR;
  if(compare[4] == softcount)  LED2_GRN_CLEAR;
  if(compare[5] == softcount)  LED2_BLU_CLEAR;

  if(compare[6] == softcount)  LED3_RED_CLEAR;
  if(compare[7] == softcount)  LED3_GRN_CLEAR;
  if(compare[8] == softcount)  LED3_BLU_CLEAR;

  if(compare[9] == softcount)  LED4_RED_CLEAR;
  if(compare[10] == softcount) LED4_GRN_CLEAR;
  if(compare[11] == softcount) LED4_BLU_CLEAR;
}
