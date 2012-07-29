#include "serial_control.h"

serial_control::serial_control()
{

	//Set Frame Label
	set_label("Serial Port");

	//Add Table to Frame
	add(table);

	//Set Table to 2x1
	table.resize(6, 1);

    label_port_name.set_label("Port:");
    label_baud_rate.set_label("Baud:");
    port_open_button.set_label("Closed");
	table.attach(label_port_name, 0, 1, 0, 1);
	table.attach(port_name_box, 1, 2, 0, 1);
	table.attach(label_baud_rate, 2, 3, 0, 1);
	table.attach(port_baud_box, 3, 4, 0, 1);
	table.attach(port_open_button, 5, 6, 0, 1);

	port_open_button.signal_clicked().connect(sigc::mem_fun(*this, &serial_control::toggle));
	status = false;

}

bool serial_control::is_open()
{
    return status;
}

void serial_control::open()
{
    if(status == false)
    {
        port.open(port_name_box.get_text().c_str(), atoi(port_baud_box.get_text().c_str()));
        port_open_button.set_label("Open");
        status = true;
    }
}

void serial_control::close()
{
    if(status == true)
    {
        port.close();
        port_open_button.set_label("Closed");
        status = false;
    }
}
void serial_control::toggle()
{
    if(status == true)
    {
        close();
    }
    else
    {
        open();
    }
}

//Function to read data from the port buffer
int serial_control::read(char * buffer, int length)
{
    return port.read(buffer, length);
}

//Function to write data to the serial port
int serial_control::write(char * buffer, int length)
{
    return port.write(buffer, length);
}
