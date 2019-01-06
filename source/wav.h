#ifndef WAV_H
#define WAV_H

#include "main.h"

#include "mymaths.h"
#include "env.h"
#include "Queue.h"
#include "Input.h"

typedef unsigned char byte;



double oscilator(size_t offset, double freq, byte waveForm)
{
	switch (waveForm)
	{
		case SINE:
			return mysine(freq*(2*M_PI)*(offset)/SAMPLERATE);
		case TRIANGLE:
		{
			double x = freq * (double)(offset)/(double)SAMPLERATE;//x coordinate
			x = x - (size_t)x;
			double hold;
			if(x <= 0.5)
				hold = 4.0*x - 1;

			else
				hold = -4.0f*x + 3;
			return hold;
		}		
		case SAWTOOTH:
		{
			double x = freq * (double)(offset)/(double)SAMPLERATE;//x coordinate
			x = x - (size_t)x;
			return 2*x - 1;;
		}			
		case SQUARE:
		{
			double x = freq * (double)(offset)/(double)SAMPLERATE;
			return x - (size_t)x > 0.5 ? -1 : 1;
		}
		case NOISE:
			return ((double)rand() / (double)RAND_MAX) * 2 - 1;				
	}
	
	return 0.0;
}


u16 displacementPos(double displacement)
{
	return (displacement * TOPSCREEN_HEIGHT * SCREENPROPORTION +  0.5 *TOPSCREEN_HEIGHT);
}

  
void fill_buffer(Input* inp, void *audioBuffer,size_t offset, size_t size, Queue* sampleBuffer) {
//----------------------------------------------------------------------------
	
	u32 *dest = (u32*)audioBuffer;//allows dest to access audio buffer
//fills audio buffer and adds a sample to it for each i
	for (unsigned int i=0; i<size; i++) {


		byte nKeysPlaying = 0;

		size_t currentSample = offset + i;
			
		s16 sample = 0;
		double displacement = 0;

		inp->scanInput();

		for(unsigned int j = 0; j < sizeof(buttons) / sizeof(buttons[0]); j++)
		{
			
	
			
			if(buttons[j].ID & inp->kDown)
			{
				buttons[j].env.triggerOnTime = currentSample;
	
			}
			else if(buttons[j].ID & inp->kUp)
			{
				buttons[j].env.triggerOffTime = currentSample;
			}
			//If button is still making sound
			buttons[j].env.isHeld = buttons[j].ID & inp->kHeld;
			if( ( buttons[j].env.triggerOnTime > buttons[j].env.triggerOffTime && buttons[j].env.isHeld)|| ( (buttons[j].env.triggerOffTime + adsr.releaseTime) > currentSample && !buttons[j].env.isHeld ))
			{
				nKeysPlaying++;
				double amplitude = buttons[j].env.getAmplitude(currentSample);
				for(int wavenum = 0; wavenum < NFREQUENCIES; wavenum++)
				{				
					displacement += oscilator(currentSample, buttons[j].waves[wavenum].frequency, buttons[j].waveForm) * amplitude * 
					buttons[j].waves[wavenum].amplitude;
				}
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
