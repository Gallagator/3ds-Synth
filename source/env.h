#ifndef ENV_H
#define ENV_H


#ifndef SAMPLERATE
#define SAMPLERATE 22050
#endif // SAMPLERATE

#ifndef SAMPLESPERBUF
#define SAMPLESPERBUF (SAMPLERATE / 30)
#endif // SAMPLESPERBUF


#ifndef BYTESPERSAMPLE
#define BYTESPERSAMPLE 4
#endif // BYTESPERSAMPLE


#ifndef SINE
#define SINE       0
#endif

#ifndef TRIANGLE
#define TRIANGLE   1
#endif

#ifndef SAWTOOTH
#define SAWTOOTH   2
#endif

#ifndef SQUARE
#define	SQUARE     3
#endif

typedef unsigned char byte;

struct envelope
{

        //times for A, D and R will be in samples rather that time hence u32 type
    u32 attackTime;
    u32 decayTime;
    u32 releaseTime;

    u32 triggerOnTime;//the sample number at which it has been pressed
    u32 triggerOffTime;

    double attackAmplitude;
    double sustainAmplitude;

	
	bool isHeld;

    envelope()
    {
        attackTime = SAMPLERATE * 0.05;
        decayTime = SAMPLERATE * 0.05;
        releaseTime = SAMPLERATE * 0.05;

		triggerOnTime = 0;//the sample number at which it has been pressed
		triggerOffTime = 0;
		
        attackAmplitude = 0.8f;
        sustainAmplitude = 0.6f;
		
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
            if(lifetime <= attackTime)
                amplitude = ((double)lifetime / (double)attackTime) * attackAmplitude;
			//decay
            else if(lifetime > attackTime && lifetime <= (attackTime + decayTime))
				amplitude = ((double)(lifetime - attackTime) / (double)decayTime) * (double)(sustainAmplitude - attackAmplitude) + (double)attackAmplitude;
			    
				//amplitude = ((double)(lifetime - attackTime) / (double)(decayTime)) * (attackAmplitude - sustainAmplitude) + attackAmplitude;
		//Sustain
            else
                amplitude = sustainAmplitude;

        }//Release
        else
        {
            lifetime = currentSample - triggerOffTime;
            amplitude = ((double)lifetime/(double)releaseTime) * (-sustainAmplitude) + sustainAmplitude;
        }

        if(amplitude < 0.001)
        {
            amplitude = 0;
        }

        return amplitude;
    }


};


struct button
{
	double frequency;
	byte waveForm;
	struct envelope env;
	u32 ID;
	
	
	button()
	{
		frequency = 440;
		waveForm = SQUARE;
		
	}
	
};


//GLOBAL button variables
struct button buttons[14];

void initButtons()
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
	
	buttons[0].frequency= 440; //A
	buttons[1].frequency = 466;//A#
	buttons[2].frequency = 494;//B
	buttons[3].frequency = 523;//C
	buttons[4].frequency = 554;//C#
	buttons[5].frequency = 587;//D
	buttons[6].frequency = 622;//D#
	buttons[7].frequency = 659;//E
	buttons[8].frequency = 698;//F
	buttons[9].frequency = 740;//F#
	buttons[10].frequency = 329.63;//G
	buttons[11].frequency = 830;//G#
	buttons[12].frequency = 415;//G#
	buttons[13].frequency = 392;//G
	


}

#endif
