#include </gtk/gtk.h>
//#include <stdio.h>
//#include <iostream>
//#include <fcntl.h>
//#include <termios.h>

unsigned char count = 0;
char buf[5];
int fd;

void fanslidermove(GtkWidget *widget, GtkLabel *label)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x11, count, 0xFF};
  
  sprintf(buf, "%d", count);
  gtk_label_set_text(label, buf);
}

void r1slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x21, count, 0xFF};
  
}

void g1slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x22, count, 0xFF};
  
}

void b1slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x23, count, 0xFF};
  
}

void r2slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x24, count, 0xFF};
 
}

void g2slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x25, count, 0xFF};
  
}

void b2slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x26, count, 0xFF};
  
}

void r3slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x27, count, 0xFF};
  
}

void g3slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x28, count, 0xFF};
  
}

void b3slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x29, count, 0xFF};
 
}

void r4slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x2A, count, 0xFF};
 
}

void g4slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x2B, count, 0xFF};
  
}

void b4slidermove(GtkWidget *widget)
{
  count = gtk_range_get_value(GTK_RANGE(widget));
  char cmd[4] = {0xAA, 0x2C, count, 0xFF};
  
}

int main(int argc, char** argv) {

  

  gtk_init(&argc, &argv);

  //Create Window//
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 300);
  gtk_window_set_title(GTK_WINDOW(window), "RGB Fan Controller");
  
  //Create Frame//
  GtkWidget *frame;
  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  //Create Fan Speed Title//
  GtkWidget *fantitle;
  fantitle = gtk_label_new("Fan Speed");
  gtk_fixed_put(GTK_FIXED(frame), fantitle, 10, 10);
  
  //Create Fan Speed Slider//
  GtkWidget *fanslider;
  fanslider = gtk_hscale_new_with_range( 0, 255, 1 );
  gtk_widget_set_size_request(fanslider, 230, 20);
  gtk_scale_set_draw_value(GTK_SCALE(fanslider), false);
  gtk_fixed_put(GTK_FIXED(frame), fanslider, 10, 30);

  //Create Fan Number Label//
  GtkWidget *fanlabel;
  fanlabel = gtk_label_new("0");
  gtk_fixed_put(GTK_FIXED(frame), fanlabel, 260, 30); 

  ///////////////////////////////////////////////////////////////////////////////////////RGB1
  //Create RGB1 Title//
  GtkWidget *rgb1title;
  rgb1title = gtk_label_new("RGB LED #1");
  gtk_fixed_put(GTK_FIXED(frame), rgb1title, 10, 70);

  //Create R1 Title//
  GtkWidget *r1title;
  r1title = gtk_label_new("R:");
  gtk_fixed_put(GTK_FIXED(frame), r1title, 10, 90);

  //Create R1 Slider//
  GtkWidget *r1slider;
  r1slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(r1slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(r1slider), false);
  gtk_fixed_put(GTK_FIXED(frame), r1slider, 30, 90);

  //Create G1 Title//
  GtkWidget *g1title;
  g1title = gtk_label_new("G:");
  gtk_fixed_put(GTK_FIXED(frame), g1title, 10, 110);

  //Create G1 Slider//
  GtkWidget *g1slider;
  g1slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(g1slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(g1slider), false);
  gtk_fixed_put(GTK_FIXED(frame), g1slider, 30, 110);

  //Create B1 Title//
  GtkWidget *b1title;
  b1title = gtk_label_new("B:");
  gtk_fixed_put(GTK_FIXED(frame), b1title, 10, 130);

  //Create B1 Slider//
  GtkWidget *b1slider;
  b1slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(b1slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(b1slider), false);
  gtk_fixed_put(GTK_FIXED(frame), b1slider, 30, 130);
  ///////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////////////RGB2
  //Create RGB1 Title//
  GtkWidget *rgb2title;
  rgb2title = gtk_label_new("RGB LED #2");
  gtk_fixed_put(GTK_FIXED(frame), rgb2title, 10, 170);

  //Create R2 Title//
  GtkWidget *r2title;
  r2title = gtk_label_new("R:");
  gtk_fixed_put(GTK_FIXED(frame), r2title, 10, 190);

  //Create R2 Slider//
  GtkWidget *r2slider;
  r2slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(r2slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(r2slider), false);
  gtk_fixed_put(GTK_FIXED(frame), r2slider, 30, 190);

  //Create G1 Title//
  GtkWidget *g2title;
  g2title = gtk_label_new("G:");
  gtk_fixed_put(GTK_FIXED(frame), g2title, 10, 210);

  //Create G2 Slider//
  GtkWidget *g2slider;
  g2slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(g2slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(g2slider), false);
  gtk_fixed_put(GTK_FIXED(frame), g2slider, 30, 210);

  //Create B2 Title//
  GtkWidget *b2title;
  b2title = gtk_label_new("B:");
  gtk_fixed_put(GTK_FIXED(frame), b2title, 10, 230);

  //Create B2 Slider//
  GtkWidget *b2slider;
  b2slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(b2slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(b2slider), false);
  gtk_fixed_put(GTK_FIXED(frame), b2slider, 30, 230);
  ///////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////////////RGB3
  //Create RGB3 Title//
  GtkWidget *rgb3title;
  rgb3title = gtk_label_new("RGB LED #3");
  gtk_fixed_put(GTK_FIXED(frame), rgb3title, 310, 70);

  //Create R3 Title//
  GtkWidget *r3title;
  r3title = gtk_label_new("R:");
  gtk_fixed_put(GTK_FIXED(frame), r3title, 310, 90);

  //Create R3 Slider//
  GtkWidget *r3slider;
  r3slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(r3slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(r3slider), false);
  gtk_fixed_put(GTK_FIXED(frame), r3slider, 330, 90);

  //Create G3 Title//
  GtkWidget *g3title;
  g3title = gtk_label_new("G:");
  gtk_fixed_put(GTK_FIXED(frame), g3title, 310, 110);

  //Create G3 Slider//
  GtkWidget *g3slider;
  g3slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(g3slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(g3slider), false);
  gtk_fixed_put(GTK_FIXED(frame), g3slider, 330, 110);

  //Create B3 Title//
  GtkWidget *b3title;
  b3title = gtk_label_new("B:");
  gtk_fixed_put(GTK_FIXED(frame), b3title, 310, 130);

  //Create B3 Slider//
  GtkWidget *b3slider;
  b3slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(b3slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(b3slider), false);
  gtk_fixed_put(GTK_FIXED(frame), b3slider, 330, 130);
  ///////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////////////RGB4
  //Create RGB4 Title//
  GtkWidget *rgb4title;
  rgb4title = gtk_label_new("RGB LED #4");
  gtk_fixed_put(GTK_FIXED(frame), rgb4title, 310, 170);

  //Create R4 Title//
  GtkWidget *r4title;
  r4title = gtk_label_new("R:");
  gtk_fixed_put(GTK_FIXED(frame), r4title, 310, 190);

  //Create R4 Slider//
  GtkWidget *r4slider;
  r4slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(r4slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(r4slider), false);
  gtk_fixed_put(GTK_FIXED(frame), r4slider, 330, 190);

  //Create G4 Title//
  GtkWidget *g4title;
  g4title = gtk_label_new("G:");
  gtk_fixed_put(GTK_FIXED(frame), g4title, 310, 210);

  //Create G4 Slider//
  GtkWidget *g4slider;
  g4slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(g4slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(g4slider), false);
  gtk_fixed_put(GTK_FIXED(frame), g4slider, 330, 210);

  //Create B4 Title//
  GtkWidget *b4title;
  b4title = gtk_label_new("B:");
  gtk_fixed_put(GTK_FIXED(frame), b4title, 310, 230);

  //Create B4 Slider//
  GtkWidget *b4slider;
  b4slider = gtk_hscale_new_with_range(0, 255, 1);
  gtk_widget_set_size_request(b4slider, 210, 20);
  gtk_scale_set_draw_value(GTK_SCALE(b4slider), false);
  gtk_fixed_put(GTK_FIXED(frame), b4slider, 330, 230);
  ///////////////////////////////////////////////////////////////////////////////////////

  //Create Connect Button//
  GtkWidget *conbutton;
  conbutton = gtk_button_new_with_label("Connect");
  gtk_widget_set_size_request(conbutton, 100, 40);
  gtk_fixed_put(GTK_FIXED(frame), conbutton, 310, 10);

  //Create Status Label//
  GtkWidget *statlabel;
  statlabel = gtk_label_new("Status: Disconnected");
  gtk_fixed_put(GTK_FIXED(frame), statlabel, 420, 20);

  gtk_widget_show_all(window);

  g_signal_connect(window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect(fanslider, "value-changed", G_CALLBACK(fanslidermove), fanlabel);
  g_signal_connect(r1slider, "value-changed", G_CALLBACK(r1slidermove), NULL);
  g_signal_connect(g1slider, "value-changed", G_CALLBACK(g1slidermove), NULL);
  g_signal_connect(b1slider, "value-changed", G_CALLBACK(b1slidermove), NULL);
  g_signal_connect(r2slider, "value-changed", G_CALLBACK(r2slidermove), NULL);
  g_signal_connect(g2slider, "value-changed", G_CALLBACK(g2slidermove), NULL);
  g_signal_connect(b2slider, "value-changed", G_CALLBACK(b2slidermove), NULL);
  g_signal_connect(r3slider, "value-changed", G_CALLBACK(r3slidermove), NULL);
  g_signal_connect(g3slider, "value-changed", G_CALLBACK(g3slidermove), NULL);
  g_signal_connect(b3slider, "value-changed", G_CALLBACK(b3slidermove), NULL);
  g_signal_connect(r4slider, "value-changed", G_CALLBACK(r4slidermove), NULL);
  g_signal_connect(g4slider, "value-changed", G_CALLBACK(g4slidermove), NULL);
  g_signal_connect(b4slider, "value-changed", G_CALLBACK(b4slidermove), NULL);
  gtk_main();

  return 0;
}
