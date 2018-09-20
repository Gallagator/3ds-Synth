#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <3ds.h>

#ifndef SAMPLERATE
#define SAMPLERATE 22050
#endif // SAMPLERATE

#ifndef SAMPLESPERBUF
#define SAMPLESPERBUF (SAMPLERATE / 30)
#endif // SAMPLESPERBUF


#ifndef BYTESPERSAMPLE
#define BYTESPERSAMPLE 4
#endif // BYTESPERSAMPLE

#include "env.h"
#include "Queue.h"

typedef unsigned char byte;

#define SINE       0
#define TRIANGLE   1
#define SAWTOOTH   2
#define	SQUARE     3

#ifndef TOPSCREENHEIGHT
#define TOPSCREENHEIGHT 240
#endif //TOPSCREENHEIGHT

#ifndef TOPSCREENWIDTH
#define TOPSCREENWIDTH 400
#endif //TOPSCREENWIDTH

#ifndef SCREENPROPORTION
#define SCREENPROPORTION 0.1f
#endif

double oscilator(size_t offset, int freq, double amplitude, byte waveForm)
{
	switch (waveForm)
	{
		case SINE:
			return amplitude * sin(freq*(2*M_PI)*(offset)/SAMPLERATE);
		case TRIANGLE:
			return asin(sin(freq * 2 * M_PI * (offset)/SAMPLERATE)) * amplitude;
		case SAWTOOTH:
			return 2*amplitude * (freq * M_PI * fmod((double)offset/SAMPLERATE, (double)1.0f/freq)) - amplitude/2;
		case SQUARE:
			if( sin(freq * (2*M_PI) * (offset)/SAMPLERATE) > 0)
				return amplitude;
			return -amplitude * INT16_MAX;
	}
	
	return 0.0;
}


u16 displacementPos(double displacement)
{
	return (displacement * TOPSCREENHEIGHT * SCREENPROPORTION +  TOPSCREENHEIGHT);
}

  
void fill_buffer(void *audioBuffer,size_t offset, size_t size, Queue* sampleBuffer) {
//----------------------------------------------------------------------------
	
	u32 *dest = (u32*)audioBuffer;//allows dest to access audio buffer
//fills audio buffer and adds a sample to it for each i
	for (unsigned int i=0; i<size; i++) {


		byte nKeysPlaying = 0;

		size_t currentSample = offset + i;
			
		s16 sample = 0;
		double displacement = 0;

		hidScanInput();
		u32 kHeld = hidKeysHeld();
		u32 kDown = hidKeysDown();
		u32 kUp = hidKeysUp();

		for(unsigned int j = 0; j < sizeof(buttons) / sizeof(buttons[0]); j++)
		{
			
			//printf("scanning");
			if(buttons[j].ID & kDown)
			{
				buttons[j].env.triggerOnTime = currentSample;
	
			}
			else if(buttons[j].ID & kUp)
			{
				buttons[j].env.triggerOffTime = currentSample;
			}
			//If button is still making sound
			buttons[j].env.isHeld = buttons[j].ID & kHeld;
			if( ( buttons[j].env.triggerOnTime > buttons[j].env.triggerOffTime && buttons[j].env.isHeld)|| ( (buttons[j].env.triggerOffTime + buttons[j].env.releaseTime) > currentSample && !buttons[j].env.isHeld ))
			{
				nKeysPlaying++;
				displacement += oscilator(currentSample, buttons[j].frequency, 1.0, buttons[j].waveForm) * buttons[j].env.getAmplitude(currentSample);
			}
		}
		displacement /= (nKeysPlaying) ? nKeysPlaying : 1;
		
		sampleBuffer->enqueue( displacementPos(displacement) );

		sample = INT16_MAX * displacement;

		dest[i] = (sample<<16) | (sample & 0xffff);
	}

	DSP_FlushDataCache(audioBuffer,size);

}





#endif // WAV_H
