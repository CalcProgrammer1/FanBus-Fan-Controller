#include "fan_control.h"
#include "fanbus.h"

extern fanbus bus;

fan_control::fan_control()
{

	fan_speed = 0;
	
	//Set Frame Label
	set_label("Fan Speed");

	//Add Table to Frame
	add(table);

	//Set Table to 2x2
	table.resize(2, 2);

	//Set up slider objects
	slider_fan.set_size_request(85, 20);
	slider_fan.set_draw_value(false);
	slider_fan.set_range(0, 255);
	slider_fan.set_increments(1, 5);

	table.attach(slider_fan, 0, 2, 0, 1);
	
    slider_fan.signal_value_changed().connect(sigc::mem_fun(*this, &fan_control::slider_fan_move));
}

void fan_control::set_addr(unsigned char dev_addr)
{
    fan_addr = dev_addr;
    fan_speed = bus.fanbus_read(0x01, fan_addr);
    slider_fan.set_value(fan_speed);
}

void fan_control::slider_fan_move()
{
    fan_speed = slider_fan.get_value();
    bus.fanbus_write(0x01, fan_addr, fan_speed);
}
