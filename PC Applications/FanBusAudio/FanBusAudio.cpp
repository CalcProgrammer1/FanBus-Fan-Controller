#include <AL/al.h>
#include <AL/alc.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "chuck_fft.h"
#include <stdio.h>
#include "serial_port.h"
#include "fanbus.h"
#include <math.h>
using namespace std;

serial_port port;
fanbus bus;

unsigned char buffer[256];
ALint sample;
float fft[256];
unsigned char charfft[256];
float win[256];

float normalizeFFT(float fftin)
{
    if(fftin > 0)
    {
        return 20.0f*log10(fftin);
    }
    else
    {
        return 0;
    }
}

int main()
{
    SDL_Surface* wavs = NULL;
    SDL_Surface* screen = NULL;
    SDL_Init( SDL_INIT_EVERYTHING );
    screen = SDL_SetVideoMode( 256, 256, 32, SDL_HWSURFACE );
    wavs = SDL_SetVideoMode( 256, 256, 32, SDL_SWSURFACE );

    port.serial_open("/dev/ttyUSB0", 38400);
    bus.fanbus_set_port(&port);

    ALCdevice *device = alcCaptureOpenDevice(NULL, 10000, AL_FORMAT_MONO8, 256);
    alcCaptureStart(device);

    hanning(win, 256);

    while (true)
    {
        for(int i = 0; i < 256; i++)
        {
            buffer[i] = 0;
            charfft[i] = 0;
            fft[i] = 0;
        }

        alcCaptureSamples(device, (ALCvoid *)buffer, 256);
        printf("buffer val: %d", buffer[3]);
        for(int i = 0; i < 256; i++)
        {
            fft[i] = (buffer[i]-128)*10.0f;
        }

        rfft(fft, 256, 1);
        //apply_window(fft, win, 256);
        boxRGBA(wavs, 0, 0, 255, 255, 0, 0, 0, 255);

        for(int i = 0; i < 256; i+=2)
        {
            float fftmag = sqrt((fft[i]*fft[i])+(fft[i+1]*fft[i+1]));
            charfft[i] = (unsigned char)fftmag;
            charfft[i+1] = charfft[i];
        }

        for(int i = 0; i < 256; i++)
        {
            pixelRGBA(wavs, i, 255- (unsigned char)buffer[i], 255, 0, 0, 255);
            lineRGBA(wavs, i, 255, i, 255-charfft[i], 0, 255, 0, 255);
        }

        SDL_BlitSurface(wavs, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(25);

        unsigned char red = exp(charfft[200]);
        unsigned char grn = exp(charfft[120]);
        unsigned char blu = exp(charfft[50]);

        printf("Red: %02X Grn: %02X Blu: %02X\n", red, grn, blu);

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
