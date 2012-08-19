import processing.core.*; 
import processing.data.*; 
import processing.opengl.*; 

import ddf.minim.analysis.*; 
import ddf.minim.*; 
import processing.serial.*; 
import javax.sound.sampled.*; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class fanbus_music_2 extends PApplet {






Serial myPort;
Minim minim;

AudioInput input;
FFT fft;
String windowName;

char val1_r;
char val1_g;
char val1_b;

char val2_r;
char val2_g;
char val2_b;

char val3_r;
char val3_g;
char val3_b;

int col = 0;

Mixer.Info[] mixerInfo;

public void setup()
{
  frameRate(60);
  size(512, 200, P3D);

  //myPort = new Serial(this, Serial.list()[1], 38400);
  minim = new Minim(this);

  input = minim.getLineIn(minim.MONO, 128, 16000);
 
  fft = new FFT(input.bufferSize(), input.sampleRate());
  fft.window(FFT.HAMMING);
}

public void set_fan_led(int addr, int led, char val)
{
  char serial_cmd[] = {0x00,(char)led,(char)addr,val,0xFF};
  for(int i = 0; i < 5; i++)
  {
    //myPort.write(serial_cmd[i]);
  }
}

public void fan_update_leds(int addr)
{
  final char serial_cmd[] = {0x00,0x0C,(char)addr,0x01,0xFF};
  for(int i = 0; i < 5; i++)
  {
    //myPort.write(serial_cmd[i]);
  }
}

public int calc_step(float val)
{
  if(val < 5)
  {
    return 0;
  }
  else if(val < 10)
  {
    return 10;
  }
  else if(val < 20)
  {
    return 50;
  }
  else if(val < 30)
  {
    if(++col > 2)
    {
      col = 0;
    }
    return 100;
  }
  else
  {
    return 255;
  }
}

public float col_test(int colr)
{
  if(col == colr)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

public void draw()
{
  background(0);
  stroke(255);
  // perform a forward FFT on the samples in jingle's left buffer
  // note that if jingle were a MONO file, 
  // this would be the same as using jingle.right or jingle.left
  fft.forward(input.mix);

  
  val1_r = (char)(exp(fft.getBand(10))-1);
  val1_g = (char)(exp(fft.getBand(15))-1);
  val1_b = (char)(exp(fft.getBand(20))-1);

  
  set_fan_led(0x10, 0x10, val1_r);
  set_fan_led(0x10, 0x11, val1_g);
  set_fan_led(0x10, 0x12, val1_b);
  
  set_fan_led(0x10, 0x13, val1_r);
  set_fan_led(0x10, 0x14, val1_g);
  set_fan_led(0x10, 0x15, val1_b);
  
  set_fan_led(0x10, 0x16, val1_r);
  set_fan_led(0x10, 0x17, val1_g);
  set_fan_led(0x10, 0x18, val1_b);
  
  set_fan_led(0x10, 0x19, val1_r);
  set_fan_led(0x10, 0x1A, val1_g);
  set_fan_led(0x10, 0x1B, val1_b);
  
  set_fan_led(0x11, 0x10, val2_r);
  set_fan_led(0x11, 0x11, val2_g);
  set_fan_led(0x11, 0x12, val2_b);
  
  set_fan_led(0x11, 0x13, val2_r);
  set_fan_led(0x11, 0x14, val2_g);
  set_fan_led(0x11, 0x15, val2_b);
  
  set_fan_led(0x11, 0x16, val2_r);
  set_fan_led(0x11, 0x17, val2_g);
  set_fan_led(0x11, 0x18, val2_b);
  
  set_fan_led(0x11, 0x19, val2_r);
  set_fan_led(0x11, 0x1A, val2_g);
  set_fan_led(0x11, 0x1B, val2_b);
   
  set_fan_led(0x12, 0x10, val3_r);
  set_fan_led(0x12, 0x11, val3_g);
  set_fan_led(0x12, 0x12, val3_b);
  
  set_fan_led(0x12, 0x13, val3_r);
  set_fan_led(0x12, 0x14, val3_g);
  set_fan_led(0x12, 0x15, val3_b);
  
  set_fan_led(0x12, 0x16, val3_r);
  set_fan_led(0x12, 0x17, val3_g);
  set_fan_led(0x12, 0x18, val3_b);
  
  set_fan_led(0x12, 0x19, val3_r);
  set_fan_led(0x12, 0x1A, val3_g);
  set_fan_led(0x12, 0x1B, val3_b);
  
  fan_update_leds(0x10);
  fan_update_leds(0x11);
  fan_update_leds(0x12);
  stroke(255);
  for(int i = 0; i < fft.specSize(); i++)
  {
     //draw the line for frequency band i, scaling it by 4 so we can see it a bit better
    line(i*5, height, i*5, height - Math.round(2*20*Math.log10(100*fft.getBand(i))));
  }
  stroke(0);
  for(int i = 0; i < width/4; i++)
  {
    line(0, height - i*4, width, height - i*4);
  }
  fill(255);
}

public void stop()
{
  // always close Minim audio classes when you finish with them
  input.close();
  minim.stop();
 
  super.stop();
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "fanbus_music_2" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
