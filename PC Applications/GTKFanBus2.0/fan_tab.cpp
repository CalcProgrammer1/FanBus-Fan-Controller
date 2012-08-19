#include "fan_tab.h"

fan_tab::fan_tab(unsigned char dev_addr)
{
    fan_addr = dev_addr;
    
    led1.set_addr(fan_addr, 0);
    led2.set_addr(fan_addr, 1);
    led3.set_addr(fan_addr, 2);
    led4.set_addr(fan_addr, 3);
    fan.set_addr (fan_addr);
    
    char label[11];
    sprintf(label, "RGB Fan %02X", fan_addr);
	set_label(label);
	add(table);
	table.resize(2,3);
	table.attach(led1, 0,1,0,1);
	table.attach(led2, 0,1,1,2);
	table.attach(led3, 1,2,0,1);
	table.attach(led4, 1,2,1,2);
	table.attach(fan,  0,2,2,3);
}
