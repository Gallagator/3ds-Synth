#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <3ds.h>

#include "wav.h"
#include "Queue.h"
#include "Wave_Display.h"

#define SAMPLERATE 22050
#define SAMPLESPERBUF (SAMPLERATE / 30)
#define BYTESPERSAMPLE 4

#define TOPSCREENHEIGHT 240
#define TOPSCREENWIDTH 400
#define SCREENPROPORTION 0.1f


//----------------------------------------------------------------------------
int main(int argc, char **argv) {
//----------------------------------------------------------------------------

	initButtons();
	Queue sampleBuffer(TOPSCREENWIDTH);


//initialises wave buffer
    PrintConsole topScreen;
    ndspWaveBuf waveBuf[2];
//initialises the graphics for the 3ds
    gfxInitDefault();

//initialises screen

    
    consoleInit(GFX_TOP, &topScreen);

    consoleSelect(&topScreen);
//sets aside memory for the audio buffer to be stored
    u32 *audioBuffer = (u32*)linearAlloc(SAMPLESPERBUF*BYTESPERSAMPLE*2);
//acts as a toggle flag
    bool fillBlock = false;
//initialises audio
    ndspInit();

//initialises speakers to stereo output and sets the sample rate
    ndspSetOutputMode(NDSP_OUTPUT_STEREO);

    ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
    ndspChnSetRate(0, SAMPLERATE);
    ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);

    float mix[12];
    memset(mix, 0, sizeof(mix));//sets all elements of the array to zero
    mix[0] = 1.0;
    mix[1] = 1.0;
    ndspChnSetMix(0, mix);

    memset(waveBuf,0,sizeof(waveBuf));//clears waveBuf
    waveBuf[0].data_vaddr = &audioBuffer[0];
    waveBuf[0].nsamples = SAMPLESPERBUF;
    waveBuf[1].data_vaddr = &audioBuffer[SAMPLESPERBUF];
    waveBuf[1].nsamples = SAMPLESPERBUF;

    size_t stream_offset = 0;//variable to hold how far into the wave has run


    ndspChnWaveBufAdd(0, &waveBuf[0]);
    ndspChnWaveBufAdd(0, &waveBuf[1]);

    while(aptMainLoop()) 
	{

        gfxSwapBuffers();
        gfxFlushBuffers();
        gspWaitForVBlank();

		u8* framebuffer = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
		memset(framebuffer, 0, TOPSCREENHEIGHT * TOPSCREENWIDTH * 3);
		
		displayWave(framebuffer, &sampleBuffer);

        /*u32 kHeld = hidKeysHeld();


        if (kHeld& KEY_START)
            break; // break in order to return to hbmenu
		*/

//checks if audio buffer has been emptied if it has, it refills it
        if (waveBuf[fillBlock].status == NDSP_WBUF_DONE)
        {

            fill_buffer(waveBuf[fillBlock].data_pcm16, stream_offset, waveBuf[fillBlock].nsamples, &sampleBuffer);

            ndspChnWaveBufAdd(0, &waveBuf[fillBlock]);//adds data to the 3ds wave buffer from our buffer
            stream_offset += waveBuf[fillBlock].nsamples;

            fillBlock = !fillBlock;
			
        }
    }
	
	
	
    ndspExit();

    linearFree(audioBuffer);

    gfxExit();
    return 0;
}
