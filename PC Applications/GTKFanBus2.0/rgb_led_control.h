#include <gtkmm.h>

//The rgb_led_control class defines a control panel for a single RGB LED
//It displays three sliders with matching numerical labels as well as
//a box that shows the current color on screen
//It may be locked (grayed out) by another process so that the user cannot
//interfere with other processes controlling the LED
class rgb_led_control : public Gtk::Frame
{
	public:
		//Constructor
		rgb_led_control();

        //Set address
        void set_addr(unsigned char dev_addr, unsigned char dev_led);
        
		//Updates all of the controls
		void update();

		//Allow external events to set LED
		void set_red(unsigned char r);
		void set_grn(unsigned char g);
		void set_blu(unsigned char b);

		//Allow external events to read LED
		unsigned char get_red();
		unsigned char get_grn();
		unsigned char get_blu();

		//Function to lock the controls (when effects are on)
		void set_lock(bool l);
		bool get_lock();
		
	private:
	    unsigned char fan_addr;
	    unsigned char fan_led;
	    
		//LED Color
		Gdk::Color color;
		
		//GTK Widget Pointers
		Gtk::Table table;
		
		Gtk::HScale slider_red;
		Gtk::HScale slider_grn;
		Gtk::HScale slider_blu;

		Gtk::Label label_red;
		Gtk::Label label_grn;
		Gtk::Label label_blu;

		Gtk::Label label_red_val;
		Gtk::Label label_grn_val;
		Gtk::Label label_blu_val;
		
		Gtk::ColorButton color_button;

		//Position Information for this control
		int x;
		int y;
		int width;
		int height;

		//Lock status
		bool lock;
		
		//GTK event functions
		void slider_red_move();
		void slider_grn_move();
		void slider_blu_move();
		void color_button_changed();
};
