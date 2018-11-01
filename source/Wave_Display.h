#ifndef WAVE_DISPLAY_H
#define WAVE_DISPLAY_H

#ifndef TOPSCREENHEIGHT
#define TOPSCREENHEIGHT 240
#endif //TOPSCREENHEIGHT

#ifndef TOPSCREENWIDTH
#define TOPSCREENWIDTH 400
#endif //TOPSCREENWIDTH

#ifndef SCREENPROPORTION
#define SCREENPROPORTION 0.2f
#endif


#include "line.h"


void displayWave(u8* fb, Queue* sampleBuffer)
{

	for(u16 x = 0; x < TOPSCREENWIDTH - 1 ; x ++ )
	{
		drawLine(fb, x, (*sampleBuffer)[x], x + 1, (*sampleBuffer)[x + 1]);
	}

/*
	for(u16 x = 0; x < 400; x++)
	{
		fb[ 3 * (TOPSCREENHEIGHT *x + (*sampleBuffer)[x] ) + 0] = 255; 
		fb[ 3 * (TOPSCREENHEIGHT *x + (*sampleBuffer)[x] ) + 1] = 255;	
		fb[ 3 * (TOPSCREENHEIGHT *x + (*sampleBuffer)[x] ) + 2] = 255;
	}
*/
}

#endif //WAVE_DISPLAY_H
