#include "serial_control.h"
extern fanbus bus;

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

void serial_control::control_open()
{
    if(status == false)
    {
        port.serial_open(port_name_box.get_text().c_str(), atoi(port_baud_box.get_text().c_str()));
        port_open_button.set_label("Open");
        bus.fanbus_set_port(&port);
        status = true;
    }
}

void serial_control::control_close()
{
    if(status == true)
    {
        port.serial_close();
        port_open_button.set_label("Closed");
        status = false;
    }
}
void serial_control::toggle()
{
    if(status == true)
    {
        control_close();
    }
    else
    {
        control_open();
        serial_open_signal.emit();
    }
}
