#include <gtkmm.h>

class fan_control : public Gtk::Frame
{
	public:
		fan_control();

        void set_addr(unsigned char dev_addr);
        
		//void update();
		//void set_fan(unsigned char spd);
		//unsigned char get_fan();
		//unsigned int get_rpm();
		
	private:
	    unsigned char fan_addr;
		unsigned char fan_speed;
		unsigned int  fan_rpm;

		void slider_fan_move();
		
		Gtk::Table table;
		Gtk::HScale slider_fan;
		Gtk::Label label_fan;
		Gtk::Label label_fan_val;
		Gtk::Label label_fan_rpm;
};
