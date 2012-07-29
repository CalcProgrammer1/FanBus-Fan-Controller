#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <ctime>
using namespace std;

char colors[4][12] ={{0,255,0,255,0,0,0,0,255,255,255,0},
                     {255,0,0,0,0,255,255,255,0,0,255,0},
                     {0,0,255,255,255,0,0,255,0,255,0,0},
                     {255,255,0,0,255,0,255,0,0,0,0,255}};

//char colors[4][12] = {{255,255,0,0,255,0,0,0,255,255,0,255},
//                      {0,255,0,0,0,255,255,0,255,255,255,0},
//                      {0,0,255,255,0,255,255,255,0,0,255,0},
//                      {255,0,255,255,255,0,0,255,0,0,0,255}};
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
    my = SerialInit("COM2",19200);
    while(1)
    {
      for(int i = 0; i < 4 ; i++)
      {
        for(char j = 0; j < 12; j++)
        {
          char cmd[4] = {0xAA, 0x41+j, colors[i][j], 0xFF};
          DWORD byteswritten;
          WriteFile(my,cmd,4,&byteswritten,NULL);
        }
        char cmd[4] = {0xAA, 0x61, 0x00, 0xFF};
        DWORD byteswritten;
        WriteFile(my,cmd,4,&byteswritten,NULL);
        while(!ReadFile(my,cmd,1,&byteswritten,NULL))
        {
          Sleep(10);
        }
      }
    }
    return 0;
}
