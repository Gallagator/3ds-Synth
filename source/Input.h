#ifndef INPUT_H
#define INPUT_H

#include "main.h"

class Input
{
public:
	void scanInput()
	{
		hidScanInput();
		kHeld = hidKeysHeld();
		kDown = hidKeysDown();
		kUp = hidKeysUp();
		if(kDown & KEY_SELECT)
			runApp = !runApp;	
	}	
	u32 kHeld;
	u32 kDown;
	u32 kUp;
	bool runApp;
};



#endif // INPUT_H
