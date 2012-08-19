#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define WINDOWS
#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef LINUX
#include <fcntl.h>
#include <termios.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
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
		bool serial_open();
		bool serial_open(const char* name);
		bool serial_open(const char* name, unsigned int baud);

		//Function to close the port
		void serial_close();

		//Functions for controlling baud rate
		void serial_set_baud(unsigned int baud);
		int serial_get_baud();

		//Function to read data from the port buffer
		int serial_read(char * buffer, int length);

		//Function to write data to the serial port
		int serial_write(char * buffer, int length);

		//Function to flush the serial port buffer
		void serial_flush();

		//Function to list the number of available bytes
		int serial_available();

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
