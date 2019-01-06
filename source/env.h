#ifndef ENV_H
#define ENV_H


#include "main.h"
#define SAVENAME "buttons.sav"


typedef unsigned char byte;

struct ADSR
{
    //times for A, D and R will be in number of samples rather than number of seconds hence u32 type
    u32 attackTime;
    u32 decayTime;
    u32 releaseTime;
	
    double attackAmplitude;
    double sustainAmplitude;


	ADSR()
	{
	    attackTime = SAMPLERATE * 0.05;
		decayTime = SAMPLERATE * 0.2;
		releaseTime = SAMPLERATE * 0.05;
		
		attackAmplitude = 0.8f;
		sustainAmplitude = 0.6f;
	}
	
};

ADSR adsr;


struct envelope
{

    u32 triggerOnTime;//the sample number at which it has been pressed
    u32 triggerOffTime;


	
	bool isHeld;

    envelope()
    {
		triggerOnTime = 0;//the sample number at which it has been pressed
		triggerOffTime = 0;
		
		isHeld = 0;
    }


    double getAmplitude(u32 currentSample)
    {
        double amplitude = 0.0f;
        u32 lifetime = 0;
        if(triggerOnTime > triggerOffTime) //note on
        {
            //ADS
            lifetime = currentSample - triggerOnTime;

            //Attack
            if(lifetime <= adsr.attackTime)
                amplitude = ((double)lifetime / (double)adsr.attackTime) * adsr.attackAmplitude;
			//decay
            else if(lifetime > adsr.attackTime && lifetime <= (adsr.attackTime + adsr.decayTime))
				amplitude = ((double)(lifetime - adsr.attackTime) / (double)adsr.decayTime) * (double)(adsr.sustainAmplitude - adsr.attackAmplitude) + (double)adsr.attackAmplitude;
			    
				//amplitude = ((double)(lifetime - attackTime) / (double)(decayTime)) * (attackAmplitude - sustainAmplitude) + attackAmplitude;
		//Sustain
            else
                amplitude = adsr.sustainAmplitude;

        }//Release
        else
        {
            lifetime = currentSample - triggerOffTime;
            amplitude = ((double)lifetime/(double)adsr.releaseTime) * (-adsr.sustainAmplitude) + adsr.sustainAmplitude;
        }

        if(amplitude < 0.001)
        {
            amplitude = 0;
        }

        return amplitude;
    }


};

#define NFREQUENCIES 3

struct button
{
	typedef struct
	{
		double frequency;
		double amplitude;
	}wav;
	
	wav waves[NFREQUENCIES];

	u8 waveForm;
	struct envelope env;
	u32 ID;
	
	
	button()
	{
		for(int i = 0; i < NFREQUENCIES; i++)
		{
			waves[i].frequency = 440;
			waves[i].amplitude = 0;
		}
		waveForm = SQUARE;		
	}
	
};


//GLOBAL button variables
struct button buttons[14];

void defaultVals()
{
	buttons[0].ID = KEY_A;
	buttons[1].ID = KEY_B;
	buttons[2].ID = KEY_X;
	buttons[3].ID = KEY_Y;
	buttons[4].ID = KEY_DLEFT;
	buttons[5].ID = KEY_DRIGHT;
	buttons[6].ID = KEY_DUP;
	buttons[7].ID = KEY_DDOWN;
	buttons[8].ID = KEY_L;
	buttons[9].ID = KEY_R;
	buttons[10].ID = KEY_CPAD_LEFT;
	buttons[11].ID = KEY_CPAD_RIGHT;
	buttons[12].ID = KEY_CPAD_DOWN;
	buttons[13].ID = KEY_CPAD_UP;

	
	buttons[0].waves[0].frequency= 440; //A
	buttons[0].waves[0].amplitude = 0.3f;	
	buttons[1].waves[0].frequency = 466;//A#
	buttons[1].waves[0].amplitude = 0.3f;
	buttons[2].waves[0].frequency = 494;//B
	buttons[2].waves[0].amplitude = 0.3;
	buttons[3].waves[0].frequency = 523;//C
	buttons[3].waves[0].amplitude = 0.3f;
	buttons[4].waves[0].frequency = 554;//C#
	buttons[4].waves[0].amplitude = 0.3f;
	buttons[5].waves[0].frequency = 587;//D
	buttons[5].waves[0].amplitude = 0.3f;
	buttons[6].waves[0].frequency = 622;//D#
	buttons[6].waves[0].amplitude = 0.3f;
	buttons[7].waves[0].frequency = 659;//E
	buttons[7].waves[0].amplitude = 0.3f;	
	buttons[8].waves[0].frequency = 698;//F
	buttons[8].waves[0].amplitude = 0.3f;
	buttons[9].waves[0].frequency = 740;//F#
	buttons[9].waves[0].amplitude = 0.3f;	
	buttons[10].waves[0].frequency = 329.63;//G
	buttons[10].waves[0].amplitude = 0.3f;
	buttons[11].waves[0].frequency = 830;//G#
	buttons[11].waves[0].amplitude = 0.3f;		
	buttons[12].waves[0].frequency = 415;//G#
	buttons[12].waves[0].amplitude = 0.3f;
	buttons[13].waves[0].frequency = 392;//G	
	buttons[13].waves[0].amplitude = 0.3f;
	

	buttons[0].waves[1].frequency= 440; //A
	buttons[0].waves[1].amplitude = 0.3f;	
	buttons[1].waves[1].frequency = 466;//A#
	buttons[1].waves[1].amplitude = 0.3f;
	buttons[2].waves[1].frequency = 494;//B
	buttons[2].waves[1].amplitude = 0.3f;
	buttons[3].waves[1].frequency = 523;//C
	buttons[3].waves[1].amplitude = 0.3f;
	buttons[4].waves[1].frequency = 554;//C#
	buttons[4].waves[1].amplitude = 0.3f;
	buttons[5].waves[1].frequency = 587;//D
	buttons[5].waves[1].amplitude = 0.3f;
	buttons[6].waves[1].frequency = 622;//D#
	buttons[6].waves[1].amplitude = 0.3f;
	buttons[7].waves[1].frequency = 659;//E
	buttons[7].waves[1].amplitude = 0.3f;	
	buttons[8].waves[1].frequency = 698;//F
	buttons[8].waves[1].amplitude = 0.3f;
	buttons[9].waves[1].frequency = 740;//F#
	buttons[9].waves[1].amplitude = 0.3f;	
	buttons[10].waves[1].frequency = 329.63;//G
	buttons[10].waves[1].amplitude = 0.3f;
	buttons[11].waves[1].frequency = 830;//G#
	buttons[11].waves[1].amplitude = 0.3f;		
	buttons[12].waves[1].frequency = 415;//G#
	buttons[12].waves[1].amplitude = 0.3f;
	buttons[13].waves[1].frequency = 392;//G	
	buttons[13].waves[1].amplitude = 0.3f;


	buttons[0].waves[2].frequency= 440; //A
	buttons[0].waves[2].amplitude = 0.3f;	
	buttons[1].waves[2].frequency = 466;//A#
	buttons[1].waves[2].amplitude = 0.3f;
	buttons[2].waves[2].frequency = 494;//B
	buttons[2].waves[2].amplitude = 0.3f;
	buttons[3].waves[2].frequency = 523;//C
	buttons[3].waves[2].amplitude = 0.3f;
	buttons[4].waves[2].frequency = 554;//C#
	buttons[4].waves[2].amplitude = 0.3f;
	buttons[5].waves[2].frequency = 587;//D
	buttons[5].waves[2].amplitude = 0.3f;
	buttons[6].waves[2].frequency = 622;//D#
	buttons[6].waves[2].amplitude = 0.3f;
	buttons[7].waves[2].frequency = 659;//E
	buttons[7].waves[2].amplitude = 0.3f;	
	buttons[8].waves[2].frequency = 698;//F
	buttons[8].waves[2].amplitude = 0.3f;
	buttons[9].waves[2].frequency = 740;//F#
	buttons[9].waves[2].amplitude = 0.3f;	
	buttons[10].waves[2].frequency = 329.63;//G
	buttons[10].waves[2].amplitude = 0.3f;
	buttons[11].waves[2].frequency = 830;//G#
	buttons[11].waves[2].amplitude = 0.3f;		
	buttons[12].waves[2].frequency = 415;//G#
	buttons[12].waves[2].amplitude = 0.3f;
	buttons[13].waves[2].frequency = 392;//G	
	buttons[13].waves[2].amplitude = 0.3f;
}


void initButtons()
{
	FILE* fp;
	if( (fp = fopen(SAVENAME, "rb") ) == NULL )
	{
		defaultVals();
	}
	else
	{
/*retrieving button values from the save file*/
		for( byte* buttonBytes = (byte*) buttons; buttonBytes < (byte*)buttons + sizeof(buttons) - 1; buttonBytes++)
		{
			*buttonBytes = fgetc(fp);
		}
/*retrieving asdr values from the save file*/
		for( byte* adsrBytes = (byte*)&adsr; adsrBytes < (byte*)&adsr + sizeof(adsr); adsrBytes++)
		{
			*adsrBytes = fgetc(fp);
		}
/*making sure that the trigger on and off times are how they should be at the start of the program. They shouldn't be 
 the values that are saved when the program is exited*/
		
		for( u32 i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
		{
			buttons[0].env.isHeld = 0;
			buttons[0].env.triggerOffTime = 0;
			buttons[0].env.triggerOnTime = 0;
		}
	}
	fclose(fp);
}

void saveButtons()
{
	FILE* fp;
	if( (fp = fopen(SAVENAME, "w") ) == NULL )
	{
		return;
	}
	
/*saving button values to the save file*/
	for( byte* buttonBytes = (byte*) buttons; buttonBytes < (byte*)buttons + sizeof(buttons) - 1; buttonBytes++)
	{
		fputc(*buttonBytes, fp);
	}
	for( byte* adsrBytes = (byte*)&adsr; adsrBytes < (byte*)&adsr + sizeof(adsr); adsrBytes++)
	{
		fputc(*adsrBytes, fp);
	}
	fclose(fp);
}


#endif
