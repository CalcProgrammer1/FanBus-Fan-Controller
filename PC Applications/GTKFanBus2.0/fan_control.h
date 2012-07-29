#include <gtkmm.h>

class fan_control : public Gtk::Frame
{
	public:
		fan_control();

		//void update();
		//void set_fan(unsigned char spd);
		//unsigned char get_fan();
		//unsigned int get_rpm();
		
	private:
		unsigned char speed;
		unsigned int rpm;

		Gtk::Table table;
		Gtk::HScale slider_fan;
		Gtk::Label label_fan;
		Gtk::Label label_fan_val;
		Gtk::Label label_fan_rpm;
};
