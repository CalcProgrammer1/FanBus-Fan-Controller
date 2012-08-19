//serial test
#include "serial_port.h"

void fanbus_write(char int_addr, char dev_addr, char val, serial_port& myPort)
{
    char fan_cmd[] = {0x00, int_addr, dev_addr, val, 0xFF};
    myPort.serial_write(fan_cmd, 5);
    //Remove the command from the read buffer
    myPort.serial_read(fan_cmd, 5);
}

int fanbus_read(char int_addr, char dev_addr, char val, serial_port& myPort)
{
    char fan_cmd[6] = {0x01, int_addr, dev_addr, val, 0xFF};
    myPort.serial_write(fan_cmd, 5);
    if(myPort.serial_read(fan_cmd, 6) > 5)
    {
        return fan_cmd[5];
    }
    else
    {
        return 0;
    }
}

void scan_fanbus_devices(serial_port& myPort)
{
    char read_buf[10];
    for(int i = 3; i < 0x20; i++)
    {
        if(fanbus_read(0x00, (char) i, 0x00, myPort) >= 0)
        {
            printf("Found %02X\n", i);
        }
        //printf("Scan %x\n", i);
        //printf("Val: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",read_buf[0],read_buf[1],read_buf[2],read_buf[3],read_buf[4],read_buf[5]);
    }
}

int main()
{
    serial_port myPort("/dev/ttyS4", 38400);
    
    fanbus_write(0x01, 0x02, 0x20, myPort);

    scan_fanbus_devices(myPort);
    
    return 0;
}
