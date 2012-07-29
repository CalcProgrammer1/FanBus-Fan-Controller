#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <ctime>
using namespace std;

char red[6] = {255,255,0,0,0,255};
char grn[6] = {0,255,255,255,0,0};
char blu[6] = {0,0,0,255,255,255};

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
      for(int i = 0; i < 6; i++)
      {
        DWORD byteswritten;

        char cmd1[4] = {0xAA, 0x41, red[i], 0xFF};
        WriteFile(my,cmd1,4,&byteswritten,NULL);
        char cmd2[4] = {0xAA, 0x42, grn[i], 0xFF};
        WriteFile(my,cmd2,4,&byteswritten,NULL);
        char cmd3[4] = {0xAA, 0x43, blu[i], 0xFF};
        WriteFile(my,cmd3,4,&byteswritten,NULL);
        char cmd4[4] = {0xAA, 0x44, red[i], 0xFF};
        WriteFile(my,cmd4,4,&byteswritten,NULL);
        char cmd5[4] = {0xAA, 0x45, grn[i], 0xFF};
        WriteFile(my,cmd5,4,&byteswritten,NULL);
        char cmd6[4] = {0xAA, 0x46, blu[i], 0xFF};
        WriteFile(my,cmd6,4,&byteswritten,NULL);
        char cmd7[4] = {0xAA, 0x47, red[i], 0xFF};
        WriteFile(my,cmd7,4,&byteswritten,NULL);
        char cmd8[4] = {0xAA, 0x48, grn[i], 0xFF};
        WriteFile(my,cmd8,4,&byteswritten,NULL);
        char cmd9[4] = {0xAA, 0x49, blu[i], 0xFF};
        WriteFile(my,cmd9,4,&byteswritten,NULL);
        char cmdA[4] = {0xAA, 0x4A, red[i], 0xFF};
        WriteFile(my,cmdA,4,&byteswritten,NULL);
        char cmdB[4] = {0xAA, 0x4B, grn[i], 0xFF};
        WriteFile(my,cmdB,4,&byteswritten,NULL);
        char cmdC[4] = {0xAA, 0x4C, blu[i], 0xFF};
        WriteFile(my,cmdC,4,&byteswritten,NULL);

        char cmd[4] = {0xAA, 0x61, 0x3F, 0xFF};

        WriteFile(my,cmd,4,&byteswritten,NULL);

        while(!ReadFile(my,cmd,1,&byteswritten,NULL))
        {
          Sleep(10);
        }
        Sleep(5000);
      }
    }
    return 0;
}
