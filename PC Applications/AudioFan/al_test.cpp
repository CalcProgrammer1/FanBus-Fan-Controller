#include <AL/al.h>
#include <AL/alc.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "chuck_fft.h"
#include <iostream>
#include "serial_port.h"
#include "fanbus.h"
#include <math.h>
using namespace std;

serial_port port;
fanbus bus;

unsigned char buffer[128];
ALint sample;
float fft[128];
float win[128];

int main()
{
    SDL_Surface* wavs = NULL;
    SDL_Surface* ffts = NULL;
    SDL_Init( SDL_INIT_EVERYTHING );
    wavs = SDL_SetVideoMode( 128, 256, 32, SDL_HWSURFACE );
    
    port.serial_open("/dev/ttyUSB0", 38400);
    bus.fanbus_set_port(&port);

    ALCdevice *device = alcCaptureOpenDevice(NULL, 8000, AL_FORMAT_MONO8, 128);
    alcCaptureStart(device);

    blackman(win, 128);
    
    while (true)
    {
        for(int i = 0; i < 128; i++)
        {
            buffer[i] = 0;
        }
        
        alcCaptureSamples(device, (ALCvoid *)buffer, 128);
        
        for(int i = 0; i < 128; i++)
        {
            fft[i] = buffer[i]*5;
        }
        
        rfft(fft, 128, 1);
        apply_window(fft, win, 128);
        
        boxRGBA(wavs, 0, 0, 256, 256, 0, 0, 0, 255);
        for(int i = 0; i < 128; i++)
        {
            pixelRGBA(wavs, i, 255-buffer[i], 255, 0, 0, 255);
            if(i%2==0)
            {
                lineRGBA(wavs, i, 255, i, 255-(unsigned char)fabs(fft[i])*3, 0, 255, 0, 255);
            }
            else
            {
                lineRGBA(wavs, i, 255, i, 255-(unsigned char)fabs(fft[i])*3, 0, 0, 255, 255);
            }
            SDL_Flip(wavs);
            
        }
        
        SDL_Delay(25);
        
        char red = (char)fabs(fft[10]);
        char grn = (char)fabs(fft[20]);
        char blu = (char)fabs(fft[30]);
        
        bus.fanbus_write(0x10, 0x02, red);
        bus.fanbus_write(0x13, 0x02, red);
        bus.fanbus_write(0x16, 0x02, red);
        bus.fanbus_write(0x19, 0x02, red);
        
        bus.fanbus_write(0x11, 0x02, grn);
        bus.fanbus_write(0x14, 0x02, grn);
        bus.fanbus_write(0x17, 0x02, grn);
        bus.fanbus_write(0x1A, 0x02, grn);
        
        bus.fanbus_write(0x12, 0x02, blu);
        bus.fanbus_write(0x15, 0x02, blu);
        bus.fanbus_write(0x18, 0x02, blu);
        bus.fanbus_write(0x1B, 0x02, blu);
        
        bus.fanbus_write(0x0C, 0x02, 0x01);
    }

    alcCaptureStop(device);
    alcCaptureCloseDevice(device);

    return 0;
}
