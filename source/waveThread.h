#ifndef WAVETHREAD_H
#define WAVETHREAD_H

#include "main.h"

#include "Input.h"

struct waveData
{
	Queue sampleBuffer;
    ndspWaveBuf waveBuf[2];
	u32 *audioBuffer;
    float mix[12];
	bool fillBlock;
    size_t stream_offset = 0; //variable to hold how far into the wave has run 
	
	waveData(); //constructor
	~waveData(); //destructor
};


waveData::waveData()
{

//sets aside memory for the audio buffer to be stored
    audioBuffer = (u32*)linearAlloc(SAMPLESPERBUF*BYTESPERSAMPLE*2);
//acts as a toggle flag
    fillBlock = false;
//initialises audio
    ndspInit();

//initialises speakers to stereo output and sets the sample rate
    ndspSetOutputMode(NDSP_OUTPUT_STEREO);

    ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
    ndspChnSetRate(0, SAMPLERATE);
    ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);

    
    memset(mix, 0, sizeof(mix));//sets all elements of the array to zero
    mix[0] = 1.0;
    mix[1] = 1.0;
    ndspChnSetMix(0, mix);

    memset(waveBuf,0,sizeof(waveBuf));//clears waveBuf
    waveBuf[0].data_vaddr = &audioBuffer[0];
    waveBuf[0].nsamples = SAMPLESPERBUF;
    waveBuf[1].data_vaddr = &audioBuffer[SAMPLESPERBUF];
    waveBuf[1].nsamples = SAMPLESPERBUF;

    stream_offset = 0; //variable to hold how far into the wave has run 

    ndspChnWaveBufAdd(0, &waveBuf[0]);
    ndspChnWaveBufAdd(0, &waveBuf[1]);

}



void runSynth(struct waveData* waveData, Input* inp)
{

	u8* framebuffer = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	memset(framebuffer, 0, TOPSCREEN_HEIGHT * TOPSCREEN_WIDTH * 3);
	
	displayWave(framebuffer, &(waveData->sampleBuffer));



//checks if audio buffer has been emptied if it has, it refills it
    if (waveData->waveBuf[waveData->fillBlock].status == NDSP_WBUF_DONE)
    {
		

        fill_buffer(inp, waveData->waveBuf[waveData->fillBlock].data_pcm16, waveData->stream_offset, waveData->waveBuf[waveData->fillBlock].nsamples, &waveData->sampleBuffer);	

        ndspChnWaveBufAdd(0, &waveData->waveBuf[waveData->fillBlock]);//adds data to the 3ds wave buffer from our buffer
		waveData->stream_offset += waveData->waveBuf[waveData->fillBlock].nsamples;
		
        waveData->fillBlock = !waveData->fillBlock;
		
    }

}

waveData::~waveData()
{
	ndspExit();
    linearFree(audioBuffer);

}

#endif// WAVETHREAD_H
