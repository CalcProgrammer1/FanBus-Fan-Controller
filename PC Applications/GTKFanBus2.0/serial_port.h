#include <cstring>
#include <stdio.h>
#include <iostream>
#define WINDOWS
#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef LINUX
#include <fcntl.h>
#include <termios.h>
#endif

//Serial Port Class
//The reason for this class is that serial ports are treated differently
//on Windows and Linux.  By creating a class, those differences can be
//made invisible to the program and make cross-platform usage easy

class serial_port
{
	public:
		serial_port();
		serial_port(const char * name, unsigned int baud);

		~serial_port();

		//Function to open the port
		void open();
		void open(const char* name);
		void open(const char* name, unsigned int baud);

		//Function to close the port
		void close();

		//Functions for controlling baud rate
		void set_baud(unsigned int baud);
		int get_baud();

		//Function to read data from the port buffer
		int read(char * buffer, int length);

		//Function to write data to the serial port
		int write(char * buffer, int length);

		//Function to flush the serial port buffer
		void flush();

		//Function to list the number of available bytes
		int available();

	private:
		char port_name[1024];
		unsigned int baud_rate;

		#ifdef LINUX
		int file_descriptor;
		#endif

		#ifdef WINDOWS
		HANDLE file_descriptor;
		DCB dcb;
		#endif
};
