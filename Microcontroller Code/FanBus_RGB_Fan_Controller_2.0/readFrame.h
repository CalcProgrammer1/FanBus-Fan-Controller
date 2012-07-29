/*-------------------------------------------------*\
|  RGB Fan Controller - Read Serial Frame Header	|
|  The readFrame function uses the buffered serial	|
|  port to receive a 4-byte serial frame from the	|
|  PC.  It then interprets the frame and performs	|
|  the appropriate action							|
|													|
|  Adam Honse (CalcProgrammer1), 2010				|
\*-------------------------------------------------*/

#ifndef READ_FRAME_H
#define READ_FRAME_H

#include "rgb.h"
#include "fan.h"
#include "crossfade.h"
#include "serial.h"
#include "save.h"

// readFrame
//  Reads 4-byte serial frames
//  The serial port must be opened first for this to work
void readFrame();

#endif
