#include "main_window.h"

extern fanbus bus;

main_window::main_window()
{
    //Set window size and title
	resize(600,400);
	set_title("FanBus Control Panel 2.0");

    //Set table size
    table.resize(1,2);

    num_fans = 0;

    table.attach(notebook,0,1,1,2);
    table.attach(port, 0, 1, 0, 1);

    port.serial_open_signal.connect(sigc::mem_fun(*this, &main_window::open_func));
	add(table);
	show_all_children();
}

void main_window::open_func()
{
    if(port.is_open())
    {
        bus.fanbus_scan_devices();
        for(int i = 0; i < bus.device_count; i++)
        {
            printf("Adding tab for device %02X.\n", bus.device_list[i]);
            fans[bus.device_list[i]] = new fan_tab(bus.device_list[i]);
            notebook.append_page((Gtk::Widget&)*fans[bus.device_list[i]]);
            notebook.show_all();
        }
    }
}
