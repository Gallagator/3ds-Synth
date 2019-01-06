#ifndef Application_H
#define Application_H

#include "main.h"
#include "Input.h"
#include "env.h"


#define BOTTOMWIDTH 40 //40 columns is the maximum
#define TOPWIDTH 50 //40 columns is the maximum
#define HEIGHT 30 //30 rows is the maximum

#define BLACK	0
#define RED		1
#define GREEN	2
#define YELLOW	3
#define BLUE	4
#define PURPLE	5
#define CYAN	6
#define WHITE	7

#define TEXT 30
#define BACKGROUND 40

#define OPTMAX 11

#define X1 1
#define X2 28


#define TWOTWELTH 1.059463094359295264561825294946341700779204317494185628559f //2^(1/12)


#define NUMERIC -1 //NUMERIC means the row has a numeric value rather than a catagorical value
#define INCPS 100   //increments per second for numeric values of indices


struct Row
{
	u32 y;
	int index;
	int maxIndex;
	const char name[OPTMAX];
	std::vector<std::string> options;
};

class Application
{
public:
	Application();
	~Application();

	void runApp(Input* inp);
	
private:
	PrintConsole bottomScreen;
	int row;
	void setIndexes();
//C, C#, D, D#, E, F, F#, G, G#, A, A# B
//NUMERIC means the row has a numeric value rather than a catagorical value
	Row menu[16] = { 
					 {2,	0, 		13, 		"Button", 		},
					 {3, 	0, 		4, 			"Waveform", 	}, 
					 {6, 	0, 		11, 		"Note1", 		},
					 {7, 	0, 		4, 			"Octave1", 		},//5 options for the octave
					 {8, 	1000, 	NUMERIC, 	"Amplitude1",	},
					 {11, 	0, 		11, 		"Note2", 		},
					 {12, 	0, 		4, 			"Octave2", 		}, 
					 {13, 	1000, 	NUMERIC, 	"Amplitude2",	}, 
					 {16, 	0, 		11, 		"Note3",		},
					 {17, 	0, 		4, 			"Octave3", 		}, 
					 {18, 	1000, 	NUMERIC, 	"Amplitude3",	},
				     {21, 	500, 	NUMERIC, 	"AttackT", 		},
					 {22, 	500, 	NUMERIC, 	"DecayT", 		},
					 {23, 	500, 	NUMERIC, 	"ReleaseT", 	}, 
					 {26, 	500, 	NUMERIC, 	"AttackAmp", 	},
					 {27, 	500, 	NUMERIC, 	"SustainAmp", 	},
					};



	double calculateFreq(u32 octave, u32 note);//C is note zero and B is note 11
	void setpos(u8 x, u8 y);
	void setColour(u8 colour);
	void printRow(int row);
	void printEntire();
	void commitChange();

};





Application::Application()
{
	consoleInit(GFX_BOTTOM, &bottomScreen);
	consoleSelect(&bottomScreen);

	row = 0;

	for(int i = 0; i < (int)( sizeof(menu) / sizeof(menu[0]) ); i++ )
	{
		if( menu[i].maxIndex )
			menu[i].options.resize( menu[i].maxIndex + 1 );
	}
	setIndexes();
	
/*initialising strings for menu*/
	menu[0].options[0] = "A";
 	menu[0].options[1] = "B";
 	menu[0].options[2] = "X";
 	menu[0].options[3] = "Y";
 	menu[0].options[4] = "DLEFT";
 	menu[0].options[5] = "DRIGHT";
 	menu[0].options[6] = "DUP";
 	menu[0].options[7] = "DDOWN";
 	menu[0].options[8] = "L";
 	menu[0].options[9] = "R";
 	menu[0].options[10] = "CLEFT";
 	menu[0].options[11] = "CRIGHT";
 	menu[0].options[12] = "CDOWN";
 	menu[0].options[13] = "CUP";

 	menu[1].options[0] = "SINE";
 	menu[1].options[1] = "TRIANGLE";
 	menu[1].options[2] = "SAWTOOTH";
 	menu[1].options[3] = "SQUARE";
 	menu[1].options[4] = "NOISE"; 	
 	
 	//C, C#, D, D#, E, F, F#, G, G#, A, A# B
 	menu[2].options[0] = "C";
 	menu[2].options[1] = "C#";
 	menu[2].options[2] = "D";
 	menu[2].options[3] = "D#";
 	menu[2].options[4] = "E";
 	menu[2].options[5] = "F";
 	menu[2].options[6] = "F#";
 	menu[2].options[7] = "G";
 	menu[2].options[8] = "G#";
 	menu[2].options[9] = "A";
 	menu[2].options[10] = "A#";
 	menu[2].options[11] = "B";
 	
 	menu[3].options[0] = "2";
 	menu[3].options[1] = "3";
 	menu[3].options[2] = "4";
 	menu[3].options[3] = "5";
 	menu[3].options[4] = "6";
 	
 	menu[5].options[0] = "C";
 	menu[5].options[1] = "C#";
 	menu[5].options[2] = "D";
 	menu[5].options[3] = "D#";
 	menu[5].options[4] = "E";
 	menu[5].options[5] = "F";
 	menu[5].options[6] = "F#";
 	menu[5].options[7] = "G";
 	menu[5].options[8] = "G#";
 	menu[5].options[9] = "A";
 	menu[5].options[10] = "A#";
 	menu[5].options[11] = "B";
 	
 	menu[6].options[0] = "2";
 	menu[6].options[1] = "3";
 	menu[6].options[2] = "4";
 	menu[6].options[3] = "5";
 	menu[6].options[4] = "6";
 	
 	menu[8].options[0] = "C";
 	menu[8].options[1] = "C#";
 	menu[8].options[2] = "D";
 	menu[8].options[3] = "D#";
 	menu[8].options[4] = "E";
 	menu[8].options[5] = "F";
 	menu[8].options[6] = "F#";
 	menu[8].options[7] = "G";
 	menu[8].options[8] = "G#";
 	menu[8].options[9] = "A";
 	menu[8].options[10] = "A#";
 	menu[8].options[11] = "B";
 	
 	menu[9].options[0] = "2";
 	menu[9].options[1] = "3";
 	menu[9].options[2] = "4";
 	menu[9].options[3] = "5";
 	menu[9].options[4] = "6";

	printEntire();
}

Application::~Application()
{
	;
}

void Application::printEntire()
{
	for(int i = 0; i <  (int)( sizeof(menu) / sizeof(menu[0]) ) ; i++)
	{
		if(i == row)
		{
			setColour(WHITE + BACKGROUND);
			setColour(BLACK + TEXT);
			printRow(i);
			setColour(0);
		}	
		else
		{
			printRow(i);
		}
	}	
}

void Application::commitChange()
{
	
	switch(row)
	{
		case 0:
		{
			setIndexes();
			printEntire();
			break;
		}
		case 1:
		{
			buttons[ menu[0].index ].waveForm = menu[1].index;//change waveform for all 
			break;
		}
		case 2:
		{
			buttons[ menu[0].index ].waves[0].frequency = calculateFreq( menu[3].index, menu[row].index);
			break;
		}
		case 3:
		{
			buttons[ menu[0].index ].waves[0].frequency = calculateFreq( menu[row].index, menu[2].index);
			break;
		}
		case 4:
		{
			buttons[ menu[0].index ].waves[0].amplitude = ((double)menu[row].index / (double)(menu[row].index + menu[7].index + menu[10].index) );
			break;
		}
		case 5:
		{
			buttons[ menu[0].index ].waves[1].frequency = calculateFreq( menu[6].index, menu[row].index);
			break;
		}
		case 6:
		{
			buttons[ menu[0].index ].waves[1].frequency = calculateFreq( menu[row].index, menu[5].index);
			break;
		}
		case 7:
		{
			buttons[ menu[0].index ].waves[1].amplitude = ((double)menu[row].index / (double)(menu[4].index + menu[7].index + menu[10].index) ) ;
			break;
		}
		case 8:
		{
			buttons[ menu[0].index ].waves[2].frequency = calculateFreq( menu[9].index, menu[row].index);
			break;
		}
		case 9:
		{
			buttons[ menu[0].index ].waves[2].frequency = calculateFreq( menu[row].index, menu[8].index);
			break;
		}
		case 10:
		{
			buttons[ menu[0].index ].waves[2].amplitude = ((double)menu[row].index / (double)(menu[4].index + menu[7].index + menu[10].index) );
			break;
		}
		case 11:
		{
			adsr.attackTime = menu[row].index * 0.001 * SAMPLERATE;
			break;
		}
		case 12:
		{
			adsr.decayTime = menu[row].index * 0.001 * SAMPLERATE;
			break;
		}
		case 13:
		{
			adsr.releaseTime = menu[row].index * 0.001 * SAMPLERATE;
			break;
		}
		case 14:
		{
			adsr.attackAmplitude = menu[row].index * 0.001;
			break;
		}
		case 15:
		{
			adsr.sustainAmplitude = menu[row].index * 0.001;
			break;
		}
		
		

	}
}


//TODO!!!
void Application::runApp(Input* inp)
{
	inp->scanInput();

	
	if(inp->kDown & KEY_UP)
	{
		setColour(0);			
		printRow(row);
		row--;
		if(row < 0)
		{
			row = (int)( sizeof( menu ) / sizeof( menu[0] ) ) - 1;
		}

		setColour(WHITE + BACKGROUND);
		setColour(BLACK + TEXT);
		printRow(row);
	}
	else if(inp->kDown & KEY_DOWN)
	{
		setColour(0);
		printRow(row);
		row++;
		if(row >= (int) ( sizeof( menu ) / sizeof( menu[0] ) ))
			row = 0;

		setColour(WHITE + BACKGROUND);
		setColour(BLACK + TEXT);
		printRow(row);
		
	}
	
	if(inp->kDown & KEY_LEFT || ( inp->kHeld & KEY_LEFT && menu[row].maxIndex == NUMERIC && menu[row].index > 0 ))
	{
		menu[row].index--;
		if(menu[row].index < 0 && menu[row].maxIndex != NUMERIC )
			menu[row].index = menu[row].options.size() - 1;
		setColour(0);								//make to func			
		printRow(row);
		setColour(WHITE + BACKGROUND);
		setColour(BLACK + TEXT);
		printRow(row);
		commitChange();
	}
	else if(inp->kDown & KEY_RIGHT || (inp->kHeld & KEY_RIGHT && menu[row].maxIndex == NUMERIC && menu[row].index < 1000))
	{
		menu[row].index++;
		if(menu[row].index > menu[row].maxIndex && menu[row].maxIndex != NUMERIC )
			menu[row].index = 0;
		setColour(0);			
		printRow(row);
		setColour(WHITE + BACKGROUND);
		setColour(BLACK + TEXT);
		printRow(row);
		commitChange();
	}
	/*
	else if(inp->kHeld & KEY_LEFT && menu[row].maxIndex == NUMERIC && menu[row].index >= 0)
	{
		menu[row].index -= ;
		if(menu[row].index > menu[row].maxIndex && menu[row].maxIndex != NUMERIC )
			menu[row].index = 0;
		setColour(0);			
		printRow(row);
		setColour(WHITE + BACKGROUND);
		setColour(BLACK + TEXT);
		printRow(row);
		commitChange();
	}
	else if(inp->kHeld & KEY_RIGHT && menu[row].maxIndex == NUMERIC && menu[row].index <= 1000)
	{
		menu[row].index += ;
		setColour(0);			
		printRow(row);
		setColour(WHITE + BACKGROUND);
		setColour(BLACK + TEXT);
		printRow(row);
		commitChange();
	}
	*/
}	


void Application::setpos(u8 x, u8 y)
{	
	//use itoa
	if( x > TOPWIDTH || y > HEIGHT )
	{
		return;
	}
;	char xbuf[2];
	char ybuf[2];
	itoa(x, xbuf, 10);
	itoa(y, ybuf, 10);
	printf("\x1b[%s;%sH", ybuf, xbuf);
}

void Application::setColour(u8 colour)
{
	if(colour > 100)
	{
		return;
	}
	char buf[2];
	itoa(colour, buf, 10);
	printf("\x1b[%sm", buf);
}

double Application::calculateFreq(u32 octave, u32 note)
{
	return 65.41f * pow(TWOTWELTH, 12 * octave + note);
}


void Application::printRow(int r)
{
	setpos(0, menu[r].y);
	for(int i = 1; i <= BOTTOMWIDTH; i++ )
		printf(" ");
	setpos(X1, menu[r].y);
	printf("%s", menu[r].name);
	setpos(X2, menu[r].y);
	if( menu[r].maxIndex == NUMERIC)
		printf("%d", menu[r].index);
	else
		printf("%s", menu[r].options[ menu[r].index ].c_str() );
}



void Application::setIndexes()
{
	int i = menu[0].index;
	menu[1].index = buttons[i].waveForm;

	int steps = round ( log( buttons[i].waves[0].frequency / 65.41f) / log(TWOTWELTH) );
	menu[2].index = steps % 12;
	menu[3].index = (int)(steps / 12);
	menu[4].index = 1000 * buttons[i].waves[0].amplitude;

	steps = round ( log( buttons[i].waves[1].frequency / 65.41f) / log(TWOTWELTH) );
	menu[5].index = steps % 12;
	menu[6].index = (int)(steps / 12);
	menu[7].index = 1000 * buttons[i].waves[1].amplitude;

	steps = round ( log( buttons[i].waves[2].frequency / 65.41f) / log(TWOTWELTH) );
	menu[8].index = steps % 12;
	menu[9].index = (int)(steps / 12);
	menu[10].index = 1000 * buttons[i].waves[2].amplitude;

	menu[11].index = 1000 * adsr.attackTime / SAMPLERATE;
	menu[12].index = 1000 * adsr.decayTime / SAMPLERATE;
	menu[13].index = 1000 * adsr.releaseTime / SAMPLERATE; 
	
	menu[14].index = 1000 * adsr.attackAmplitude;
	menu[15].index = 1000 * adsr.sustainAmplitude;
	
}


#endif //Application_H
