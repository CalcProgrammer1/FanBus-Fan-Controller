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
#include <avr/eeprom.h>

#include "rgb.h"
#include "fan.h"
#include "fanbus.h"
#include "save.h"

extern unsigned char * fanbus_register_buffer[];
extern unsigned char fanbus_address;

extern char compbuff[12];
extern char update;

int main()
{
  unsigned char save = 0;
  unsigned char restore = 0;
  unsigned char old_fanbus_address;

  //Initialize LED's and Fan
  setupLEDs();
  setupFan();
  setupFanRPMCount();

  //Read FanBus address from EEPROM
  fanbus_address = eeprom_read_byte((unsigned char *)(14));

  //Make sure address is valid
  if(fanbus_address == 0x00 || fanbus_address == 0x01 || fanbus_address == 0x02 || fanbus_address == 0xFF)
  {
  	//If address is invalid, set it to 0xAA (default address)
  	fanbus_address == 0xAA;
	eeprom_write_byte((unsigned char *)(14), fanbus_address);
  }

  old_fanbus_address = fanbus_address;

  fanbus_init(12); 		//38400 baud

  //Set pointers to LED and Fan Registers
  fanbus_register_buffer[0x00] = &fanbus_address;
  fanbus_register_buffer[0x01] = getFanSpeedPointer();
  fanbus_register_buffer[0x02] = (unsigned char *)(getFanRPMPointer());
  fanbus_register_buffer[0x03] = (unsigned char *)(getFanRPMPointer()+1);
  
  fanbus_register_buffer[0x0A] = &save;
  fanbus_register_buffer[0x0B] = &restore;
  fanbus_register_buffer[0x0C] = &update;  

  fanbus_register_buffer[0x10] = &compbuff[0];
  fanbus_register_buffer[0x11] = &compbuff[1];
  fanbus_register_buffer[0x12] = &compbuff[2];
  fanbus_register_buffer[0x13] = &compbuff[3];
  fanbus_register_buffer[0x14] = &compbuff[4];
  fanbus_register_buffer[0x15] = &compbuff[5];
  fanbus_register_buffer[0x16] = &compbuff[6];
  fanbus_register_buffer[0x17] = &compbuff[7];
  fanbus_register_buffer[0x18] = &compbuff[8];
  fanbus_register_buffer[0x19] = &compbuff[9];
  fanbus_register_buffer[0x1A] = &compbuff[10];
  fanbus_register_buffer[0x1B] = &compbuff[11];
    
  startUp();

  while(1)
  {
	_delay_ms(100);

	//Check for address updates
    if(old_fanbus_address != fanbus_address)
	{
	  if(fanbus_address == 0x00 || fanbus_address == 0x01 || fanbus_address == 0x02 || fanbus_address == 0xFF)
	  {
	  	fanbus_address = old_fanbus_address;
		eeprom_write_byte((unsigned char *)(14), fanbus_address);
	  }
	  else
	  {
	    old_fanbus_address = fanbus_address;
	  	eeprom_write_byte((unsigned char *)(14), fanbus_address);
	  }
	}

	//Check for save
	if(save != 0)
	{
		saveState();
		save = 0;
	}

	//Check for restore

	if(restore != 0)
	{
		restoreState();
		restore = 0;
	}
  }
}

