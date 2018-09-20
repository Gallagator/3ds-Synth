#ifndef WAVE_DISPLAY_H
#define WAVE_DISPLAY_H

#ifndef TOPSCREENHEIGHT
#define TOPSCREENHEIGHT 240
#endif //TOPSCREENHEIGHT

#ifndef TOPSCREENWIDTH
#define TOPSCREENWIDTH 400
#endif //TOPSCREENWIDTH

#ifndef SCREENPROPORTION
#define SCREENPROPORTION 0.1f
#endif

void displayWave(u8* framebuffer, Queue* sampleBuffer)
{
	
	for(u16 x = 0; x < 400; x++)
	{
		framebuffer[ 3 * (TOPSCREENHEIGHT *x + (*sampleBuffer)[x] ) + 0] = 255; 
		framebuffer[ 3 * (TOPSCREENHEIGHT *x + (*sampleBuffer)[x] ) + 1] = 255;	
		framebuffer[ 3 * (TOPSCREENHEIGHT *x + (*sampleBuffer)[x] ) + 2] = 255;
	}

}

#endif //WAVE_DISPLAY_H
