/*---------------------------------------------*\
|  RGB Fan Controller - Read Serial Frame Code	|
|  Contains the code for reading commands from 	|
|  the serial port.  Commands are 4 bytes and	|
|  are defined in the serial protocol text		|
|  document included with the source code.		|
|												|
|  Adam Honse (CalcProgrammer1), 2010			|
\*---------------------------------------------*/

#include "readFrame.h"

//compbuff from rgb.c, sets the LED colors
extern unsigned char compbuff[12];
extern char crossfade[12];
extern char update;
char address = 0x27;

char r;
char g;
char b;


void readFrame()
{
	unsigned char frame[8];
	unsigned char complete = 0;
	unsigned char enabled = 0;
	unsigned char new_byte;
	unsigned char pos = 0;
	unsigned char frame_size = 0;
	while(complete == 0)
	{
		while(serial_available() == 0)
		{
		}

		new_byte = serial_read();

		if((new_byte & 0x80) == 0x80)
		{
			frame[0] = new_byte;
			pos = 1;
			//enabled = 1;
		}
		else //if(enabled == 1)
		{
			frame[pos] = new_byte;
			
			if(pos == 1)
			{
				switch(new_byte & 0x60)
				{
					case 0x00:
					case 0x20:
						frame_size = 1;
						complete = 1;
						enabled = 0;
					break;

					case 0x40:
						frame_size = 2;
					break;

					case 0x60:
						frame_size = 4;
					break;
				}
			}
			else if(pos >= frame_size)
			{
				complete = 1;
				//enabled = 0;
			}
			pos++;
		}
	}

	if((frame[0] == (address | 0x80)) || (frame[0] == 0x80))
	{
		switch(frame[1])
		{
			//Case 0x01 - Ping - Returns Address - No reply on global call
			case 0x01:
			{
				if(frame[0] != 0x80)
				{
					serial_transmit(address);
				}
			}
			break;

			//Case 0x02 - 
			case 0x02:
			{
				serial_transmit(0x01);
			}
			break;

			case 0x03:
			{
				serial_transmit(0x01);
			}
			break;

			case 0x04:
			{
				serial_print("FanBus 4 RGB LED Fan Controller v1.0");
			}
			break;

			case 0x41:
			{
				if((frame[2] & 0x01) == 0x01)
				{
					compbuff[0] = r;
					compbuff[1] = g;
					compbuff[2] = b;
				}

				if((frame[2] & 0x02) == 0x02)
				{
					compbuff[3] = r;
					compbuff[4] = g;
					compbuff[5] = b;
				}

				if((frame[2] & 0x04) == 0x04)
				{
					compbuff[6] = r;
					compbuff[7] = g;
					compbuff[8] = b;
				}

				if((frame[2] & 0x08) == 0x08)
				{
					compbuff[9] = r;
					compbuff[10] = g;
					compbuff[11] = b;
				}
				if((frame[2] & 0x40) == 0x40)
				{
					update = 1;
				}
				serial_transmit(address);
			}
			break;

			case 0x61:
			{
				r = frame[2];
				g = frame[3];
				b = frame[4];
				serial_transmit(address);
			}
			break;
		}
		serial_flush();
	}
}
