#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <ctime>
using namespace std;

HANDLE my;

HANDLE SerialInit(char *ComPortName, int BaudRate)
{
       HANDLE hComm;
       DCB dcb;
       hComm = CreateFile(ComPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

       SetupComm(hComm, 1, 128);

       GetCommState(hComm, &dcb);
       dcb.BaudRate = BaudRate;
       dcb.ByteSize = 8;
       dcb.Parity = NOPARITY;

       dcb.StopBits = ONESTOPBIT;
       dcb.fAbortOnError = TRUE;

       dcb.fOutX = FALSE; // XON/XOFF off for transmit
       dcb.fInX = FALSE; // XON/XOFF off for receive
       dcb.fOutxCtsFlow = FALSE; // turn on CTS flow control
       dcb.fRtsControl = RTS_CONTROL_HANDSHAKE; //
       dcb.fOutxDsrFlow = FALSE; // turn on DSR flow control
       dcb.fDtrControl = DTR_CONTROL_ENABLE; //
       dcb.fDtrControl = DTR_CONTROL_DISABLE; //
       dcb.fDtrControl = DTR_CONTROL_HANDSHAKE; //

       SetCommState(hComm, &dcb);

       return hComm;
}
int main()
{
        srand(time(0));
    my = SerialInit("COM2",19200);
    while(1)
    {

    for(char i = 0x41; i < 0x4D; i++)
    {
      char random1 = rand()%256;
      char cmd[4] = {0xAA, i, random1, 0xFF};
      DWORD byteswritten;
      WriteFile(my,cmd,4,&byteswritten,NULL);
    }
    char cmd[4] = {0xAA, 0x61, 0x00, 0xFF};
    DWORD byteswritten;
    WriteFile(my,cmd,4,&byteswritten,NULL);
    Sleep(2000);
    }
    return 0;
}
