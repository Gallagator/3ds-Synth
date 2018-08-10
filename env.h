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

	bool noteOn;

    envelope()
    {
        attackTime = SAMPLERATE * 0.5;
        decayTime = SAMPLERATE * 0.1;
        releaseTime = SAMPLERATE * 0.5;

		triggerOnTime = 0;//the sample number at which it has been pressed
		triggerOffTime = 0;
		
        attackAmplitude = 1.0;
        sustainAmplitude = 0.8;
		
		noteOn = 0;

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

            else if(lifetime > attackTime && lifetime <= (attackTime + decayTime))
                amplitude = ((double)(lifetime - attackTime) / (double)(decayTime)) * (attackAmplitude - sustainAmplitude) + attackAmplitude;

            else
                amplitude = sustainAmplitude;

        }
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
	u16 frequency;
	byte waveForm;
	struct envelope env;
	u32 ID;
	
	button()
	{
		frequency = 440;
		waveForm = SINE;
	}
	
};


//GLOBAL button variables
struct button buttons[12];

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
	
	for(unsigned int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
		buttons[i].frequency = 440 * pow(2, (i - 9) / 12);
	

}

#endif
