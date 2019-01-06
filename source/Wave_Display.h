#ifndef WAVE_DISPLAY_H
#define WAVE_DISPLAY_H

#include "main.h"

#include "line.h"


void displayWave(u8* fb, Queue* sampleBuffer)
{

	for(u16 x = 0; x < TOPSCREEN_WIDTH - 1 ; x ++ )
	{
		drawLine(fb, x, (*sampleBuffer)[x], x + 1, (*sampleBuffer)[x + 1]);
	}

}

#endif //WAVE_DISPLAY_H
