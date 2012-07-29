#include "main_window.h"

main_window::main_window()
{
    //Set window size and title
	resize(600,400);
	set_title("FanBus Control Panel 2.0");

    //Set table size
    table.resize(2,2);

    num_fans = 0;

    table.attach(notebook,0,1,1,2);
    table.attach(port, 0, 1, 0, 1);

	//notebook.append_page(fan1, "Fan 1");
	//notebook.append_page(fan2, "Fan 2");
	//notebook.append_page(fan3, "Fan 3");

    test.set_label("Test Port");
    table.attach(test, 1, 2, 0, 1);
    test.signal_clicked().connect(sigc::mem_fun(*this, &main_window::test_func));

	add(table);
	show_all_children();
}

void main_window::test_func()
{
    if(port.is_open())
    {
        char devices = 0;
        for(unsigned char i = 0; i < 255; i++)
        {
            char my_cmd[5] = {0x00, 0x01, 0xFF, 0xFF};
            my_cmd[0] = i;
            port.write(my_cmd, 4);
            char bytes_read = port.read(my_cmd, 5);
            if(bytes_read > 4)
            {
                devices++;
                fans[num_fans] = new fan_tab;
                char tab_label[32];
                sprintf(tab_label, "Fan %X", i);
                notebook.append_page(*fans[num_fans], tab_label);
                show_all_children();
            }
        }
        std::cout << "finished" << (int)devices << std::endl;
    }
}
