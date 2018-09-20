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
        attackTime = SAMPLERATE * 1;
        decayTime = SAMPLERATE * 1;
        releaseTime = SAMPLERATE * 1;

		triggerOnTime = 0;//the sample number at which it has been pressed
		triggerOffTime = 0;
		
        attackAmplitude = 0.4f;
        sustainAmplitude = 0.4f;
		
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
			    amplitude = ((double)(lifetime - attackTime) / (double)(decayTime)) * (attackAmplitude - sustainAmplitude) + attackAmplitude;
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
	
	buttons[0].frequency= 100;
	buttons[1].frequency = 200;
	buttons[2].frequency = 300;
	buttons[3].frequency = 400;
	buttons[4].frequency = 500;
	buttons[5].frequency = 600;
	buttons[6].frequency = 700;
	buttons[7].frequency = 800;
	buttons[8].frequency = 900;
	buttons[9].frequency = 1000;
	buttons[10].frequency = 1100;
	buttons[11].frequency = 1200;

	buttons[0].waveForm = SQUARE;
	buttons[1].waveForm = SQUARE;
	buttons[2].waveForm = SAWTOOTH;
	buttons[3].waveForm = SAWTOOTH;
	buttons[4].waveForm = TRIANGLE;
	buttons[5].waveForm = TRIANGLE;

}

#endif
