//Developed by Rajarshi Roy
import java.awt.Robot; //java library that lets us take screenshots
import java.awt.AWTException;
import java.awt.event.InputEvent;
import java.awt.image.BufferedImage;
import java.awt.Rectangle;
import java.awt.Dimension;
import processing.serial.*; //library for serial communication


Serial myPort; //creates object "port" of serial class
Robot robby; //creates object "robby" of robot class

void setup()
{
  myPort = new Serial(this, Serial.list()[1],38400); //set baud rate
  size(100, 100); //window size (doesn't matter)
  try //standard Robot class error check
  {
    robby = new Robot();
  }
  catch (AWTException e)
  {
    println("Robot class not supported by your system!");
    exit();
  }
}

void sendLED(int addr, int led, char r, char g, char b)
{
   myPort.write((char)addr);
   myPort.write((char)(0x21 + (3*led)));
   myPort.write((char)r);
   myPort.write((char)0xFF);
   
   myPort.write(addr);
   myPort.write(0x21 + (3*led) + 1);
   myPort.write(g);
   myPort.write(0xFF);
   
   myPort.write(addr);
   myPort.write(0x21 + (3*led) + 2);
   myPort.write(b);
   myPort.write(0xFF);
}

void draw()
{
  int pixel; //ARGB variable with 32 int bytes where
  //sets of 8 bytes are: Alpha, Red, Green, Blue
  float r=0;
  float g=0;
  float b=0;

  //get screenshot into object "screenshot" of class BufferedImage
  BufferedImage screenshot = robby.createScreenCapture(new Rectangle(new Dimension(1920,1080)));
  //1368*928 is the screen resolution


  int i=0;
  int j=0;
  //1368*928
  //I skip every alternate pixel making my program 4 times faster
  for(i =0;i<1920; i=i+1)
  {
    for(j=0; j<1080;j=j+1)
    {
      pixel = screenshot.getRGB(i,j); //the ARGB integer has the colors of pixel (i,j)
      r = r+(int)(255&(pixel>>16)); //add up reds
      g = g+(int)(255&(pixel>>8)); //add up greens
      b = b+(int)(255&(pixel)); //add up blues
    }
  }
  r=r/(1920*1080); //average red (remember that I skipped ever alternate pixel)
  g=g/(1920*1080); //average green
  b=b/(1920*1080); //average blue
  sendLED(0xAA,1,(char)r,(char)g,(char)b);
  sendLED(0xAA,2,(char)r,(char)g,(char)b);
  sendLED(0xAA,3,(char)r,(char)g,(char)b);
  sendLED(0xAA,0,(char)r,(char)g,(char)b);
  sendLED(0xBB,1,(char)r,(char)g,(char)b);
  sendLED(0xBB,2,(char)r,(char)g,(char)b);
  sendLED(0xBB,3,(char)r,(char)g,(char)b);
  sendLED(0xBB,0,(char)r,(char)g,(char)b);
  sendLED(0xCC,1,(char)r,(char)g,(char)b);
  sendLED(0xCC,2,(char)r,(char)g,(char)b);
  sendLED(0xCC,3,(char)r,(char)g,(char)b);
  sendLED(0xCC,0,(char)r,(char)g,(char)b);
  delay(10); //delay for safety

  background(r,g,b); //make window background average color
}
