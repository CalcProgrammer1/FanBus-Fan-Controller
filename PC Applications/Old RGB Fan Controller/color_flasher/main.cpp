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
    my = SerialInit("COM2",38400);
    while(1)
    {
      for(int i = 0; i < 6; i++)
      {
        DWORD byteswritten;

        char cmd1[4] = {0xAA, 0x21, red[i], 0xFF};
        WriteFile(my,cmd1,4,&byteswritten,NULL);
        char cmd2[4] = {0xAA, 0x22, grn[i], 0xFF};
        WriteFile(my,cmd2,4,&byteswritten,NULL);
        char cmd3[4] = {0xAA, 0x23, blu[i], 0xFF};
        WriteFile(my,cmd3,4,&byteswritten,NULL);
        char cmd4[4] = {0xAA, 0x24, red[i], 0xFF};
        WriteFile(my,cmd4,4,&byteswritten,NULL);
        char cmd5[4] = {0xAA, 0x25, grn[i], 0xFF};
        WriteFile(my,cmd5,4,&byteswritten,NULL);
        char cmd6[4] = {0xAA, 0x26, blu[i], 0xFF};
        WriteFile(my,cmd6,4,&byteswritten,NULL);
        char cmd7[4] = {0xAA, 0x27, red[i], 0xFF};
        WriteFile(my,cmd7,4,&byteswritten,NULL);
        char cmd8[4] = {0xAA, 0x28, grn[i], 0xFF};
        WriteFile(my,cmd8,4,&byteswritten,NULL);
        char cmd9[4] = {0xAA, 0x29, blu[i], 0xFF};
        WriteFile(my,cmd9,4,&byteswritten,NULL);
        char cmdA[4] = {0xAA, 0x2A, red[i], 0xFF};
        WriteFile(my,cmdA,4,&byteswritten,NULL);
        char cmdB[4] = {0xAA, 0x2B, grn[i], 0xFF};
        WriteFile(my,cmdB,4,&byteswritten,NULL);
        char cmdC[4] = {0xAA, 0x2C, blu[i], 0xFF};
        WriteFile(my,cmdC,4,&byteswritten,NULL);
        char cmdd1[4] = {0xBB, 0x21, red[i], 0xFF};
        WriteFile(my,cmdd1,4,&byteswritten,NULL);
        char cmdd2[4] = {0xBB, 0x22, grn[i], 0xFF};
        WriteFile(my,cmdd2,4,&byteswritten,NULL);
        char cmdd3[4] = {0xBB, 0x23, blu[i], 0xFF};
        WriteFile(my,cmdd3,4,&byteswritten,NULL);
        char cmdd4[4] = {0xBB, 0x24, red[i], 0xFF};
        WriteFile(my,cmdd4,4,&byteswritten,NULL);
        char cmdd5[4] = {0xBB, 0x25, grn[i], 0xFF};
        WriteFile(my,cmdd5,4,&byteswritten,NULL);
        char cmdd6[4] = {0xBB, 0x26, blu[i], 0xFF};
        WriteFile(my,cmdd6,4,&byteswritten,NULL);
        char cmdd7[4] = {0xBB, 0x27, red[i], 0xFF};
        WriteFile(my,cmdd7,4,&byteswritten,NULL);
        char cmdd8[4] = {0xBB, 0x28, grn[i], 0xFF};
        WriteFile(my,cmdd8,4,&byteswritten,NULL);
        char cmdd9[4] = {0xBB, 0x29, blu[i], 0xFF};
        WriteFile(my,cmdd9,4,&byteswritten,NULL);
        char cmddA[4] = {0xBB, 0x2A, red[i], 0xFF};
        WriteFile(my,cmddA,4,&byteswritten,NULL);
        char cmddB[4] = {0xBB, 0x2B, grn[i], 0xFF};
        WriteFile(my,cmddB,4,&byteswritten,NULL);
        char cmddC[4] = {0xBB, 0x2C, blu[i], 0xFF};
        WriteFile(my,cmddC,4,&byteswritten,NULL);
        Sleep(250);
      }
    }
    return 0;
}
