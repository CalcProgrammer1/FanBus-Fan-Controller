#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <cmath>
using namespace std;

char red[6] = {255,255,0,0,0,255};
char grn[6] = {0,255,255,255,0,0};
char blu[6] = {0,0,0,255,255,255};

#define PI 3.1415926
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
    double count1 = 0;
    double count2 = 0;
    double count3 = 0;
    double count4 = 0;
    char val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12;
    while(1)
    {
      val1 = (sin(count1+1))*127;
      val2 = ((sin(count1+((2*PI)/3)))+1)*127;
      val3 = ((sin(count1+((4*PI)/3)))+1)*127;
      val4 = (sin(count2+1))*127;
      val5 = ((sin(count2+((2*PI)/3)))+1)*127;
      val6 = ((sin(count2+((4*PI)/3)))+1)*127;
      val7 = (sin(count3+1))*127;
      val8 = ((sin(count3+((2*PI)/3)))+1)*127;
      val9 = ((sin(count3+((4*PI)/3)))+1)*127;
      val10 = (sin(count4+1))*127;
      val11 = ((sin(count4+((2*PI)/3)))+1)*127;
      val12 = ((sin(count4+((4*PI)/3)))+1)*127;
        DWORD byteswritten;

        char cmd1[4] = {0xAA, 0x21, val1, 0xFF};
        WriteFile(my,cmd1,4,&byteswritten,NULL);
        char cmd2[4] = {0xAA, 0x22, val2, 0xFF};
        WriteFile(my,cmd2,4,&byteswritten,NULL);
        char cmd3[4] = {0xAA, 0x23, val3, 0xFF};
        WriteFile(my,cmd3,4,&byteswritten,NULL);
        char cmd4[4] = {0xAA, 0x24, val4, 0xFF};
        WriteFile(my,cmd4,4,&byteswritten,NULL);
        char cmd5[4] = {0xAA, 0x25, val5, 0xFF};
        WriteFile(my,cmd5,4,&byteswritten,NULL);
        char cmd6[4] = {0xAA, 0x26, val6, 0xFF};
        WriteFile(my,cmd6,4,&byteswritten,NULL);
        char cmd7[4] = {0xAA, 0x27, val7, 0xFF};
        WriteFile(my,cmd7,4,&byteswritten,NULL);
        char cmd8[4] = {0xAA, 0x28, val8, 0xFF};
        WriteFile(my,cmd8,4,&byteswritten,NULL);
        char cmd9[4] = {0xAA, 0x29, val9, 0xFF};
        WriteFile(my,cmd9,4,&byteswritten,NULL);
        char cmdA[4] = {0xAA, 0x2A, val10, 0xFF};
        WriteFile(my,cmdA,4,&byteswritten,NULL);
        char cmdB[4] = {0xAA, 0x2B, val11, 0xFF};
        WriteFile(my,cmdB,4,&byteswritten,NULL);
        char cmdC[4] = {0xAA, 0x2C, val12, 0xFF};
        WriteFile(my,cmdC,4,&byteswritten,NULL);
        Sleep(25);
        count1 = count1 + (((2*PI)/3)/60);
        count2 = count2 + (((2*PI)/3)/27);
        count2 = count3 + (((2*PI)/3)/80);
        count4 = count4 + (((2*PI)/3)/99);
    }
    return 0;
}
