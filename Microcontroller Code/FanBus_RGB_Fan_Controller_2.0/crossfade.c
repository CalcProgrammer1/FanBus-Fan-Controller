/*---------------------------------------------*\
|  RGB Fan Controller - Cross Fade Code File	|
| Provides the cross-fading code for fading LEDs|
|												|
| Modified by Adam Honse (CalcProgrammer1), 2010|
\*---------------------------------------------*/

#include "crossfade.h"


extern unsigned char compbuff[12];
extern char update;

char colorVal[12];
int colorStep[12];
char crossfade[12];

void crossFade(char wait)
{
  for (unsigned char i = 0; i < 12; i++)
  {
    colorStep[i] = calculateStep(compbuff[i], crossfade[i]);
  }

  for (int i = 0; i < 1020; i++)
  {  
	for(int j = 0; j < 12; j++)
	{
	  compbuff[j] = calculateVal(colorStep[j], compbuff[j], i);
	  update = 1;
      _delay_us(wait); // Pause for 'wait' milliseconds before resuming the loop
    }
  }

  for (unsigned char i = 0; i < 12; i++)
  {
    compbuff[i] = crossfade[i];
	update = 1;
  }
}

char calculateVal(int step, char val, int i)
{
  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}

int calculateStep(char prevValue, char endValue)
{
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}
