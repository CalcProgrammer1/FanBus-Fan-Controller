#include "rgb_led_control.h"
#include <stdio.h>
#include "fanbus.h"
extern fanbus bus;

rgb_led_control::rgb_led_control()
{   
	color.set_rgb(0, 0, 0);

	//Set Frame Label
	set_label("RGB LED");

	//Add Table to Frame
	add(table);
	
	//Set Table to 4x4
	table.resize(4, 4);

	//Set Up Slider Objects
	slider_red.set_size_request(85, 20);
	slider_grn.set_size_request(85, 20);
	slider_blu.set_size_request(85, 20);

	slider_red.set_draw_value(false);
	slider_grn.set_draw_value(false);
	slider_blu.set_draw_value(false);
	
	slider_red.set_range(0, 255);
	slider_grn.set_range(0, 255);
	slider_blu.set_range(0, 255);

	slider_red.set_increments(1, 5);
	slider_grn.set_increments(1, 5);
	slider_blu.set_increments(1, 5);

	table.attach(slider_red, 1, 3, 0, 1);
	table.attach(slider_grn, 1, 3, 1, 2);
	table.attach(slider_blu, 1, 3, 2, 3);

	//Set Up Label Objects
	label_red.set_label("R:");
	label_grn.set_label("G:");
	label_blu.set_label("B:");

	table.attach(label_red, 0, 1, 0, 1);
	table.attach(label_grn, 0, 1, 1, 2);
	table.attach(label_blu, 0, 1, 2, 3);
	
	label_red_val.set_label("");
	label_grn_val.set_label("");
	label_blu_val.set_label("");

	table.attach(label_red_val, 3, 4, 0, 1);
	table.attach(label_grn_val, 3, 4, 1, 2);
	table.attach(label_blu_val, 3, 4, 2, 3);

	//Create Color Chooser and Color Chooser button
	color_button.set_color(color);
	table.attach(color_button, 1, 3, 3, 4);	

	//Connect Signals to Functions
	slider_red.signal_value_changed().connect(sigc::mem_fun(*this, &rgb_led_control::slider_red_move));
	slider_grn.signal_value_changed().connect(sigc::mem_fun(*this, &rgb_led_control::slider_grn_move));
	slider_blu.signal_value_changed().connect(sigc::mem_fun(*this, &rgb_led_control::slider_blu_move));
	color_button.signal_color_set().connect(  sigc::mem_fun(*this, &rgb_led_control::color_button_changed));
}

void rgb_led_control::set_addr(unsigned char dev_addr, unsigned char dev_led)
{
    fan_addr = dev_addr;
    fan_led  = dev_led;
    
    //Update colors from fan
  	color.set_red  (((bus.fanbus_read(0x10 + (fan_led*3), fan_addr)+1)*256)-1);
 	color.set_green(((bus.fanbus_read(0x11 + (fan_led*3), fan_addr)+1)*256)-1);
    color.set_blue (((bus.fanbus_read(0x12 + (fan_led*3), fan_addr)+1)*256)-1);
    update();
    color_button_changed();
}

void rgb_led_control::update()
{
	//This function should update the labels, color preview, and
	//RGB LED state when called.  It must have access to the LED output
	color_button.set_color(color);

	//Update Value Labels
	char red_val[4];
	char grn_val[4];
	char blu_val[4];

	sprintf(red_val, "%d", color.get_red()/256);
	sprintf(grn_val, "%d", color.get_green()/256);
	sprintf(blu_val, "%d", color.get_blue()/256);
	
	label_red_val.set_label(red_val);
	label_grn_val.set_label(grn_val);
	label_blu_val.set_label(blu_val);
	
	//Update fan device
	bus.fanbus_write(0x10 + (fan_led*3), fan_addr, color.get_red()/256);
	bus.fanbus_write(0x11 + (fan_led*3), fan_addr, color.get_green()/256);
    bus.fanbus_write(0x12 + (fan_led*3), fan_addr, color.get_blue()/256);
	bus.fanbus_write(0x0C, fan_addr, 0x01);
}

void rgb_led_control::set_red(unsigned char r)
{
	color.set_red(((r+1)*256)-1);
	update();
}

void rgb_led_control::set_grn(unsigned char g)
{
	color.set_green(((g+1)*256)-1);
	update();
}

void rgb_led_control::set_blu(unsigned char b)
{
	color.set_blue(((b+1)*256)-1);
	update();
}

unsigned char rgb_led_control::get_red()
{
	return color.get_red();
}

unsigned char rgb_led_control::get_grn()
{
	return color.get_green();
}

unsigned char rgb_led_control::get_blu()
{
	return color.get_blue();
}

void rgb_led_control::set_lock(bool l)
{
	if(l)
	{
		if(!lock)
		{
			//lock all controls
			lock = true;
		}
	}
	else
	{
		if(lock)
		{
			//unlock all controls
			lock = false;
		}
	}
}

bool rgb_led_control::get_lock()
{
	return lock;
}

void rgb_led_control::slider_red_move()
{
	color.set_red(((unsigned int)slider_red.get_value()*256)|(((unsigned int)slider_red.get_value()>127)*0x00FF));
	update();
}

void rgb_led_control::slider_grn_move()
{
	color.set_green(((unsigned int)slider_grn.get_value()*256)|(((unsigned int)slider_grn.get_value()>127)*0x00FF));
	update();
}

void rgb_led_control::slider_blu_move()
{
	color.set_blue(((unsigned int)slider_blu.get_value()*256)|(((unsigned int)slider_blu.get_value()>127)*0x00FF));
	update();
}

void rgb_led_control::color_button_changed()
{
	color = color_button.get_color();
	slider_red.set_value(color.get_red()/256);
	slider_grn.set_value(color.get_green()/256);
	slider_blu.set_value(color.get_blue()/256);
	update();
}
