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
extern char compbuff[12];
extern char crossfade[12];
void readFrame()
{
  char frame[4];
  do
  {
    frame[0] = USART0_Read();
  }while(frame[0] != 0xCC);
  
  for(int i = 1; i < 4; i++)
  {
    while(USART0_Available() == 0)
	{
	}
	frame[i]=USART0_Read();
  }
  
  if(frame[3] == 0xFF)
  {
    switch(frame[1])
	{
	  case 0x01: //Ping
	    USART0_Transmit(0x7C);
		break;
      
	  case 0x02: //Echo
	    USART0_Transmit(frame[2]);
		break;

      case 0x03: //Save State
	    saveState();
		USART0_Transmit(0x72);
		break;
      
	  case 0x04: //Restore State
	    restoreState();
		USART0_Transmit(0x73);
		break;

	  case 0x11: //Set Fan Speed
	    setFanSpeed(frame[2]);
		break;

      case 0x12: //Get Fan Speed
	    USART0_Transmit(getFanSpeed());
		break;

      case 0x13: //Get RPM
	    USART0_Transmit(fanRPM());
	    USART0_Transmit(fanRPM() >> 8);
		break;
      
	  case 0x21: //Set R1
	    compbuff[0] = frame[2];
		break;
      
	  case 0x22: //Set G1
		compbuff[1] = frame[2];
		break;

      case 0x23: //Set B1
		compbuff[2] = frame[2];
		break;
      
	  case 0x24: //Set R2
	    compbuff[3] = frame[2];
		break;

      case 0x25: //Set G2
	    compbuff[4] = frame[2];
		break;

      case 0x26: //Set B2
	    compbuff[5] = frame[2];
		break;

      case 0x27: //Set R3
		compbuff[6] = frame[2];
		break;
     
	  case 0x28: //Set G3
		compbuff[7] = frame[2];
		break;

      case 0x29: //Set B3
	    compbuff[8] = frame[2];
		break;
      
	  case 0x2A: //Set R4
		compbuff[9] = frame[2];
		break;

	  case 0x2B: //Set G4
	    compbuff[10] = frame[2];
		break;
      
	  case 0x2C: //Set B3
		compbuff[11] = frame[2];
		break;
      
	  case 0x31: //Get R1
	    USART0_Transmit(compbuff[0]);
		break;

      case 0x32: //Get G1
	    USART0_Transmit(compbuff[1]);
		break;

      case 0x33: //Get B1
	    USART0_Transmit(compbuff[2]);
		break;

      case 0x34: //Get R2
	    USART0_Transmit(compbuff[3]);
		break;

      case 0x35: //Get G2
	    USART0_Transmit(compbuff[4]);
		break;
		
      case 0x36: //Get B2
	    USART0_Transmit(compbuff[5]);
		break;
      
	  case 0x37: //Get R3
	    USART0_Transmit(compbuff[6]);
		break;
      
	  case 0x38: //Get G3
	    USART0_Transmit(compbuff[7]);
		break;

      case 0x39: //Get B3
	    USART0_Transmit(compbuff[8]);
		break;

      case 0x3A: //Get R4
	    USART0_Transmit(compbuff[9]);
		break;

      case 0x3B: //Get G4
	    USART0_Transmit(compbuff[10]);
		break;

      case 0x3C: //Get B4
	    USART0_Transmit(compbuff[11]);
		break;
      
	  case 0x41: //Set R1 CrossFade
	    crossfade[0] = frame[2];
		break;
      
	  case 0x42: //Set G1 CrossFade
	    crossfade[1] = frame[2];
		break;

      case 0x43: //Set B1 CrossFade
	    crossfade[2] = frame[2];
		break;
      
	  case 0x44: //Set R2 CrossFade
	    crossfade[3] = frame[2];
		break;

      case 0x45: //Set G2 CrossFade
	    crossfade[4] = frame[2];
		break;

      case 0x46: //Set B2 CrossFade
	    crossfade[5] = frame[2];
		break;

      case 0x47: //Set R3 CrossFade
	    crossfade[6] = frame[2];
		break;
		
      case 0x48: //Set G3 CrossFade
	    crossfade[7] = frame[2];
		break;
      
	  case 0x49: //Set B3 CrossFade
	    crossfade[8] = frame[2];
		break;

      case 0x4A: //Set R4 CrossFade
	    crossfade[9] = frame[2];
		break;

      case 0x4B: //Set G4 CrossFade
	    crossfade[10] = frame[2];
		break;
      
	  case 0x4C: //Set B4 CrossFade
	    crossfade[11] = frame[2];
		break;
      
	  case 0x51: //Get R1 CrossFade
	    USART0_Transmit(crossfade[0]);
		break;

      case 0x52: //Get G1 CrossFade
	    USART0_Transmit(crossfade[1]);
		break;

      case 0x53: //Get B1 CrossFade
	    USART0_Transmit(crossfade[2]);
		break;

      case 0x54: //Get R2 CrossFade
	    USART0_Transmit(crossfade[3]);
		break;
      
	  case 0x55: //Get G2 CrossFade
	    USART0_Transmit(crossfade[4]);
		break;

      case 0x56: //Get B2 CrossFade
	    USART0_Transmit(crossfade[5]);
		break;

      case 0x57: //Get R3 CrossFade
	    USART0_Transmit(crossfade[6]);
		break;

      case 0x58: //Get G3 CrossFade
	    USART0_Transmit(crossfade[7]);
		break;

      case 0x59: //Get B3 CrossFade
	    USART0_Transmit(crossfade[8]);
		break;

      case 0x5A: //Get R4 CrossFade
	    USART0_Transmit(crossfade[9]);
		break;

      case 0x5B: //Get G4 CrossFade
	    USART0_Transmit(crossfade[10]);
		break;

      case 0x5C: //Get B4 CrossFade
	    USART0_Transmit(crossfade[11]);
		break;

      case 0x61: //Run CrossFade
	    crossFade(frame[2]);
		USART0_Transmit(0x74); //CrossFade complete
		break;
	}
  }
}
