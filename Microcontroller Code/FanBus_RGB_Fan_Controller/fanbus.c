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
#include "fanbus.h"

#define FANBUS_REGISTER_BUFFER_SIZE 0x20

unsigned char fanbus_serial_buffer[5]; //Serial buffer
unsigned char * fanbus_register_buffer[FANBUS_REGISTER_BUFFER_SIZE];
unsigned char fanbus_dummy = 0;
unsigned char fanbus_address = 0xAA;

//USART Receive interrupt pushes the incoming byte into the buffer
ISR(USART_RX_vect)
{
	//Shift in new data
	fanbus_serial_buffer[0] = fanbus_serial_buffer[1];
	fanbus_serial_buffer[1] = fanbus_serial_buffer[2];
	fanbus_serial_buffer[2] = fanbus_serial_buffer[3];
	fanbus_serial_buffer[3] = fanbus_serial_buffer[4];
	fanbus_serial_buffer[4] = UDR0;

	//Test if valid write packet
	if(fanbus_serial_buffer[0] == 0x00 && fanbus_serial_buffer[4] == 0xFF)
	{
		//Check if it is our address or global address (0x02)
		if(fanbus_serial_buffer[2] == fanbus_address || fanbus_serial_buffer[2] == 0x02)
		{
			//Perform operation
			*(fanbus_register_buffer[fanbus_serial_buffer[1]]) = fanbus_serial_buffer[3];
		}
	}
	else if(fanbus_serial_buffer[0] == 0x01 && fanbus_serial_buffer[4] == 0xFF)
	{
		//Check if it is our address
		if(fanbus_serial_buffer[2] == fanbus_address || fanbus_serial_buffer[2] == 0x02)
		{
			//Perform Read Operation
			fanbus_transmit(*(fanbus_register_buffer[fanbus_serial_buffer[1]]));
		}
	}
}

void fanbus_init(unsigned int baud)
{
	//Set baud rate
	UBRR0H = (unsigned char) (baud >> 8);
	UBRR0L = (unsigned char) (baud);

	//Set frame format: 8 data, no parity, 2 stop bits
	UCSR0C = (0<<UMSEL00) | (0<<UPM00) | (0<<USBS0) | (3<<UCSZ00);

	//Enable receiver and transmitter
	UCSR0B = (1<<RXCIE0 | 1<<RXEN0) | (1<<TXEN0);

	//Initialize pointers to reserved safe address
	for(unsigned char i = 0; i < FANBUS_REGISTER_BUFFER_SIZE; i++)
	{
		fanbus_register_buffer[i] = &fanbus_dummy;
	}
}

void fanbus_transmit(unsigned char data)
{
	//Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));

	//Put data into buffer, send data
	UDR0 = data;
}
