/*---------------------------------------------*\
|  RGB Fan Controller - Save State Code File	|
|  This file contains the code needed to save	|
|  the fan's state, restore the fan's state, and|
|  apply the fan state at start-up				|
|												|
|  It saves the LED array and the desired fan	|
|  speed, it does not save the crossfade array	|
|												|
|  Adam Honse (CalcProgrammer1), February 2010	|
\*---------------------------------------------*/

#include "save.h"

char save_compbuff[12];
char save_fanspeed;

extern unsigned char compbuff[12];
extern char crossfade[12];
extern char update;

void saveState()
{
  for(char i = 0; i < 12; i++)
  {
    save_compbuff[i] = compbuff[i];
	eeprom_write_byte((unsigned char*)(i+1),save_compbuff[i]);
  }
  
  save_fanspeed = getFanSpeed(); 
  eeprom_write_byte((unsigned char*)13,save_fanspeed);
}

void restoreState()
{
  for(char i = 0; i < 12; i++)
  {
    compbuff[i] = save_compbuff[i];
	update = 1;
  }

  setFanSpeed(save_fanspeed);
}

void readEeprom()
{
  for(char i = 0; i < 12; i++)
  {
    save_compbuff[i] = eeprom_read_byte((unsigned char*)(i+1));
  }

  save_fanspeed = eeprom_read_byte((unsigned char*)(13));
}

void startUp()
{
  readEeprom();
  for(char i = 0; i < 12; i++)
  {
    crossfade[i] = save_compbuff[i];
  }
  setFanSpeed(255);
  _delay_us(100);
  setFanSpeed(save_fanspeed);
  crossFade(100);
  for(char i = 0; i < 12; i++)
  {
    crossfade[i] = 0;
  }
}
