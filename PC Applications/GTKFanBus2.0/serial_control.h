#include <gtkmm.h>
#include "serial_port.h"
#include "fanbus.h"

class serial_control : public Gtk::Frame
{
	public:
		serial_control();

        bool is_open();
        void control_open();
        void control_close();
        
        sigc::signal<void> serial_open_signal;
        
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
