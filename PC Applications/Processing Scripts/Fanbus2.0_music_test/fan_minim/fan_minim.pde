import ddf.minim.analysis.*;
import ddf.minim.*;
import processing.serial.*;

Serial myPort;
Minim minim;
AudioInput input;
FFT fft;
String windowName;
byte[] val = new byte[12];

void setup()
{
  size(512, 200, P3D);
  textMode(SCREEN);
  myPort = new Serial(this, Serial.list()[0], 38400);
  minim = new Minim(this);
  input = minim.getLineIn(minim.MONO, 2048);
   
  // create an FFT object that has a time-domain buffer 
  // the same size as jingle's sample buffer
  // note that this needs to be a power of two 
  // and that it means the size of the spectrum
  // will be 512. see the online tutorial for more info.
  fft = new FFT(input.bufferSize(), input.sampleRate());
  //frameRate(30);
  textFont(createFont("Arial", 16));
 
  windowName = "None";
}
 
void draw()
{
  background(0);
  stroke(255);
  // perform a forward FFT on the samples in jingle's left buffer
  // note that if jingle were a MONO file, 
  // this would be the same as using jingle.right or jingle.left
  fft.forward(input.mix);
  

  
  for(int i = 0; i < 12; i++)
  {
    val[i] = (byte)(pow(fft.getBand(50+i*20),fft.getBand(50+i*20)));
  }
  
  FanBus_Set_LED(val[0], val[1], val[2], (byte)0x01);
  FanBus_Set_LED(val[3], val[4], val[5], (byte)0x02);
  FanBus_Set_LED(val[6], val[7], val[8], (byte)0x04);
  FanBus_Set_LED(val[9], val[10], val[11], (byte)0x78);
  
  for(int i = 0; i < fft.specSize(); i++)
  {
    // draw the line for frequency band i, scaling it by 4 so we can see it a bit better
    line(i, height, i, height - fft.getBand(i)*4);
  }
  fill(255);
  // keep us informed about the window being used
  //text("The window being used is: " + windowName, 5, 20);
}
 
void keyReleased()
{
  if ( key == 'w' )
  {
    // a Hamming window can be used to shape the sample buffer that is passed to the FFT
    // this can reduce the amount of noise in the spectrum
    fft.window(FFT.HAMMING);
    windowName = "Hamming";
  }
 
  if ( key == 'e' )
  {
    fft.window(FFT.NONE);
    windowName = "None";
  }
}

void FanBus_Set_LED(byte r, byte g, byte b, byte led)
{
  myPort.clear();
  byte msg[] = {(byte)0xA7, 0x61, (byte)(r & 0x7F),(byte)(g & 0x7F), (byte)(b & 0x7F)};
  myPort.write(msg);
  while(myPort.available() < 6)
  {
  }
  myPort.clear();
  
  byte msg2[] = {(byte)0xA7, 0x41, led};
  myPort.write(msg2);
  while(myPort.available() < 4)
  {
  }
  myPort.clear();
}

void stop()
{
  // always close Minim audio classes when you finish with them
  input.close();
  minim.stop();
 
  super.stop();
}
