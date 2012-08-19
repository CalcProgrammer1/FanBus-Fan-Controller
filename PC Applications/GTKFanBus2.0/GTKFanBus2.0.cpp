#include <gtk/gtk.h>
#include "main_window.h"

using namespace std;

fanbus bus;

int main(int argc, char** argv)
{
	Gtk::Main kit(argc, argv);
	main_window window;
	Gtk::Main::run(window);
}
