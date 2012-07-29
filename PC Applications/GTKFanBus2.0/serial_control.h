#include <gtkmm.h>
#include "serial_port.h"
class serial_control : public Gtk::Frame
{
	public:
		serial_control();

        bool is_open();
        void open();
        void close();

        //Function to read data from the port buffer
		int read(char * buffer, int length);

		//Function to write data to the serial port
		int write(char * buffer, int length);

	private:
        serial_port port;
        bool status;

        void toggle();

		Gtk::Table table;
		Gtk::Entry port_name_box;
		Gtk::Entry port_baud_box;
		Gtk::Label label_port_name;
		Gtk::Label label_baud_rate;
		Gtk::Button port_open_button;
};
