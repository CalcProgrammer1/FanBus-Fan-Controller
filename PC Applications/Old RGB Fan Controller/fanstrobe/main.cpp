/*-----------------------------------------*\
| RGB Fan Controller - Fan Strobe Light     |
| This app communicates with the RGB Fan    |
| Controller via COM port (COM2), provides  |
| LED and fan control, saves and loads      |
| state, and displays the RPM feedback from |
| the fan.  Uses GTK+ for GUI.              |
|                                           |
| Adam Honse (CalcProgrammer1), 2010        |
\*-----------------------------------------*/
#include <gtk/gtk.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
HANDLE my;
unsigned char color[3] = {0,0,0};
unsigned int pulse = 1;
unsigned int delay = 5;
bool on = false;
unsigned int count = 0;

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

gboolean strobe()
{
  std::cout << "strobe" << std::endl;
  char colorc[3];
  bool send = false;
  if(on && count>=pulse) //need to turn off
  {
      colorc[0] = 0;
      colorc[1] = 0;
      colorc[2] = 0;
      send = true;
      on = false;
      count = 0;
  }
  else if(!on && count >= delay)
  {
      colorc[0] = color[0];
      colorc[1] = color[1];
      colorc[2] = color[2];
      send = true;
      on = true;
      count = 0;
  }
  else
  {
      count++;
  }
  if(send)
  {
  char cmd1[4] = {0xAA,0x21,colorc[0],0xFF};
  DWORD byteswritten;
  WriteFile(my,cmd1,4,&byteswritten,NULL);
  char cmd2[4] = {0xAA,0x22,colorc[1],0xFF};
  WriteFile(my,cmd2,4,&byteswritten,NULL);
  char cmd3[4] = {0xAA,0x23,colorc[2],0xFF};
  WriteFile(my,cmd3,4,&byteswritten,NULL);
  char cmd4[4] = {0xAA,0x24,colorc[0],0xFF};
  WriteFile(my,cmd4,4,&byteswritten,NULL);
  char cmd5[4] = {0xAA,0x25,colorc[1],0xFF};
  WriteFile(my,cmd5,4,&byteswritten,NULL);
  char cmd6[4] = {0xAA,0x26,colorc[2],0xFF};
  WriteFile(my,cmd6,4,&byteswritten,NULL);
  char cmd7[4] = {0xAA,0x27,colorc[0],0xFF};
  WriteFile(my,cmd7,4,&byteswritten,NULL);
  char cmd8[4] = {0xAA,0x28,colorc[1],0xFF};
  WriteFile(my,cmd8,4,&byteswritten,NULL);
  char cmd9[4] = {0xAA,0x29,colorc[2],0xFF};
  WriteFile(my,cmd9,4,&byteswritten,NULL);
  char cmda[4] = {0xAA,0x2A,colorc[0],0xFF};
  WriteFile(my,cmda,4,&byteswritten,NULL);
  char cmdb[4] = {0xAA,0x2B,colorc[1],0xFF};
  WriteFile(my,cmdb,4,&byteswritten,NULL);
  char cmdc[4] = {0xAA,0x2C,colorc[2],0xFF};
  WriteFile(my,cmdc,4,&byteswritten,NULL);
  }
  gtk_true();
}

void rslidermove(GtkWidget *widget)
{
  color[0] = gtk_range_get_value(GTK_RANGE(widget));
}

void gslidermove(GtkWidget *widget)
{
  color[1] = gtk_range_get_value(GTK_RANGE(widget));
}

void bslidermove(GtkWidget *widget)
{
  color[2] = gtk_range_get_value(GTK_RANGE(widget));
}

void delayslidermove(GtkWidget *widget)
{
  delay = gtk_range_get_value(GTK_RANGE(widget));
}

void pulseslidermove(GtkWidget *widget)
{
  pulse = gtk_range_get_value(GTK_RANGE(widget));
}

int main(int argc, char** argv) {

  my=SerialInit("COM2",19200);

  gtk_init(&argc, &argv);

  //Create Window//
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_window_set_title(GTK_WINDOW(window), "RGB Fan Strobe Light");

  //Create Frame//
  GtkWidget *frame;
  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  //Create Color Title//
  GtkWidget *colortitle;
  colortitle = gtk_label_new("Strobe Color");
  gtk_fixed_put(GTK_FIXED(frame), colortitle, 10, 10);

  //Create R Title//
  GtkWidget *rtitle;
  rtitle = gtk_label_new("R:");
  gtk_fixed_put(GTK_FIXED(frame), rtitle, 10, 30);

  //Create R Slider//
  GtkWidget *rslider;
  rslider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(rslider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(rslider), false);
  gtk_fixed_put(GTK_FIXED(frame), rslider, 30, 30);

  //Create G1Title//
  GtkWidget *gtitle;
  gtitle = gtk_label_new("G:");
  gtk_fixed_put(GTK_FIXED(frame), gtitle, 10, 50);

  //Create G Slider//
  GtkWidget *gslider;
  gslider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(gslider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(gslider), false);
  gtk_fixed_put(GTK_FIXED(frame), gslider, 30, 50);

  //Create B Title//
  GtkWidget *btitle;
  btitle = gtk_label_new("B:");
  gtk_fixed_put(GTK_FIXED(frame), btitle, 10, 70);

  //Create B Slider//
  GtkWidget *bslider;
  bslider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(bslider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(bslider), false);
  gtk_fixed_put(GTK_FIXED(frame), bslider, 30, 70);

  GtkWidget *delayslider;
  delayslider = gtk_hscale_new_with_range(0,100,1);
  gtk_widget_set_size_request(delayslider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(delayslider),false);
  gtk_fixed_put(GTK_FIXED(frame), delayslider, 30, 100);

  GtkWidget *pulseslider;
  pulseslider = gtk_hscale_new_with_range(0,100,1);
  gtk_widget_set_size_request(pulseslider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(pulseslider),false);
  gtk_fixed_put(GTK_FIXED(frame), pulseslider, 30, 120);

  gtk_widget_show_all(window);

  gtk_timeout_add(1,(GtkFunction)strobe,NULL);

  g_signal_connect(window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect(rslider, "value-changed", G_CALLBACK(rslidermove), NULL);
  g_signal_connect(gslider, "value-changed", G_CALLBACK(gslidermove), NULL);
  g_signal_connect(bslider, "value-changed", G_CALLBACK(bslidermove), NULL);

  g_signal_connect(delayslider, "value-changed", G_CALLBACK(delayslidermove), NULL);
  g_signal_connect(pulseslider, "value-changed", G_CALLBACK(pulseslidermove), NULL);
  gtk_main();

  return 0;
}
