#include "fan_tab.h"

fan_tab::fan_tab()
{
	set_label("RGB Fan");
	add(table);
	table.resize(2,3);
	table.attach(led1, 0,1,0,1);
	table.attach(led2, 0,1,1,2);
	table.attach(led3, 1,2,0,1);
	table.attach(led4, 1,2,1,2);
	table.attach(fan,  0,2,2,3);
}
