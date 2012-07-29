import ddf.minim.analysis.*;
import ddf.minim.*;
import processing.serial.*;

Serial myPort;
Minim minim;
AudioInput input;
FFT fft;
String windowName;
void setup()
{
  frameRate(30);
  size(512, 200, P3D);
  textMode(SCREEN);
  myPort = new Serial(this, Serial.list()[2], 19200);
  minim = new Minim(this);
  
  input = minim.getLineIn(minim.MONO, 2048);
 
  // create an FFT object that has a time-domain buffer 
  // the same size as jingle's sample buffer
  // note that this needs to be a power of two 
  // and that it means the size of the spectrum
  // will be 512. see the online tutorial for more info.
  fft = new FFT(input.bufferSize(), input.sampleRate());
 
  textFont(createFont("Arial", 16));
 
  windowName = "None";
}
char time1 = 0; 
void draw()
{
  
  background(0);
  stroke(255);
  // perform a forward FFT on the samples in jingle's left buffer
  // note that if jingle were a MONO file, 
  // this would be the same as using jingle.right or jingle.left
  fft.forward(input.mix);
  
  char val2 = (char)pow(fft.getBand(150),fft.getBand(150));
  char val5 = (char)pow(fft.getBand(160),fft.getBand(160));
  char val8 = (char)pow(fft.getBand(170),fft.getBand(170));
  char val11 = (char)pow(fft.getBand(180),fft.getBand(180));
  char val1 = (char)pow(fft.getBand(250),fft.getBand(250));
  char val4 = (char)pow(fft.getBand(260),fft.getBand(260));
  char val7 = (char)pow(fft.getBand(270),fft.getBand(270));
  char val10 = (char)pow(fft.getBand(280),fft.getBand(280));
  char val0 = (char)pow(fft.getBand(350),fft.getBand(350));
  char val3 = (char)pow(fft.getBand(360),fft.getBand(360));
  char val6 = (char)pow(fft.getBand(370),fft.getBand(370));
  char val9 = (char)pow(fft.getBand(380),fft.getBand(380));
  

  char mycmd[] = {0xAA,0x21,val0,0xFF};
  myPort.write(mycmd[0]);
  myPort.write(mycmd[1]);
  myPort.write(mycmd[2]);
  myPort.write(mycmd[3]);
  
  char mycmd1[] = {0xAA,0x22,val1,0xFF};
  myPort.write(mycmd1[0]);
  myPort.write(mycmd1[1]);
  myPort.write(mycmd1[2]);
  myPort.write(mycmd1[3]);
  
  char mycmd2[] = {0xAA,0x23,val2,0xFF};
  myPort.write(mycmd2[0]);
  myPort.write(mycmd2[1]);
  myPort.write(mycmd2[2]);
  myPort.write(mycmd2[3]);
  
  char mycmd3[] = {0xAA,0x24,val3,0xFF};
  myPort.write(mycmd3[0]);
  myPort.write(mycmd3[1]);
  myPort.write(mycmd3[2]);
  myPort.write(mycmd3[3]);
  
  char mycmd4[] = {0xAA,0x25,val4,0xFF};
  myPort.write(mycmd4[0]);
  myPort.write(mycmd4[1]);
  myPort.write(mycmd4[2]);
  myPort.write(mycmd4[3]);
  
  char mycmd5[] = {0xAA,0x26,val5,0xFF};
  myPort.write(mycmd5[0]);
  myPort.write(mycmd5[1]);
  myPort.write(mycmd5[2]);
  myPort.write(mycmd5[3]);
  
  char mycmd6[] = {0xAA,0x27,val6,0xFF};
  myPort.write(mycmd6[0]);
  myPort.write(mycmd6[1]);
  myPort.write(mycmd6[2]);
  myPort.write(mycmd6[3]);
 
  char mycmd7[] = {0xAA,0x28,val7,0xFF};
  myPort.write(mycmd7[0]);
  myPort.write(mycmd7[1]);
  myPort.write(mycmd7[2]);
  myPort.write(mycmd7[3]);
  
  char mycmd8[] = {0xAA,0x29,val8,0xFF};
  myPort.write(mycmd8[0]);
  myPort.write(mycmd8[1]);
  myPort.write(mycmd8[2]);
  myPort.write(mycmd8[3]);
  
  char mycmd9[] = {0xAA,0x2A,val9,0xFF};
  myPort.write(mycmd9[0]);
  myPort.write(mycmd9[1]);
  myPort.write(mycmd9[2]);
  myPort.write(mycmd9[3]);
  
  char mycmda[] = {0xAA,0x2B,val10,0xFF};
  myPort.write(mycmda[0]);
  myPort.write(mycmda[1]);
  myPort.write(mycmda[2]);
  myPort.write(mycmda[3]);
  
  char mycmdb[] = {0xAA,0x2C,val11,0xFF};
  myPort.write(mycmdb[0]);
  myPort.write(mycmdb[1]);
  myPort.write(mycmdb[2]);
  myPort.write(mycmdb[3]);

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
 
void stop()
{
  // always close Minim audio classes when you finish with them
  input.close();
  minim.stop();
 
  super.stop();
}
