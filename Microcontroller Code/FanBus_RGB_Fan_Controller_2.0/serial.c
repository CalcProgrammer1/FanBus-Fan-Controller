/*---------------------------------------------*\
|  RGB Fan Controller - Serial Port Code File	|
|  This file contains the functionality of the	|
|  buffered serial port.  It uses a buffer array|
|  and a position value.  The default buffer	|
|  size is 64 bytes, though you can increase 	|
|  it if you need a larger buffer.				|
|												|
|  Adam Honse (CalcProgrammer1), 2010			|
\*---------------------------------------------*/
#include "serial.h"

unsigned char buffer[64]; //Serial buffer
unsigned char buffer_pos = 0; //Current use of buffer

//USART Receive interrupt pushes the incoming byte into the buffer
ISR(USART_RX_vect)
{
  buffer[buffer_pos] = UDR0;
  //Increment buffer position
  buffer_pos++;
  if(buffer_pos > 64)
  {
    buffer_pos = 0;
  }
}

unsigned char serial_available()
{
  return buffer_pos;
}

void serial_init(unsigned int baud)
{
	//Set baud rate
	UBRR0H = (unsigned char) (baud >> 8);
	UBRR0L = (unsigned char) (baud);

	//Set frame format: 8 data, no parity, 2 stop bits
	UCSR0C = (0<<UMSEL00) | (0<<UPM00) | (0<<USBS0) | (3<<UCSZ00);

	//Enable receiver and transmitter
	UCSR0B = (1<<RXCIE0 | 1<<RXEN0) | (1<<TXEN0);
}

//Buffered read pops the first byte off the buffer
unsigned char serial_read()
{
  if(buffer_pos == 0)
  {
    return 0;
  }
  char value = buffer[0];
  for(char i = 1; i < 64; i++)
  {
    buffer[i-1] = buffer[i];
  }
  buffer[63] = 0;
  buffer_pos--;

  return value;
}

//Deletes all items in the buffer
void serial_flush()
{
  buffer_pos = 0;
}

void serial_transmit(unsigned char data)
{
	//Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));
	{
	  asm("nop");
	}

	//Put data into buffer, send data
	UDR0 = data;
}

void serial_print(char * text)
{
	int pos = 0;
	while(text[pos] != '\0')
	{
		serial_transmit(text[pos]);
		pos++;
	}
}
