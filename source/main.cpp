#include "main.h"
#include "wav.h"
#include "Queue.h"
#include "Wave_Display.h"
#include "waveThread.h"
#include "Application.h"
#include "Input.h"


//----------------------------------------------------------------------------
int main(int argc, char **argv) {
//----------------------------------------------------------------------------

	gfxInitDefault();
	
	struct waveData waveData;	

	initButtons();
	Application interface;
	

	Input inp;
	
    	// Main loop
	while (aptMainLoop()) 
	{
	    gfxSwapBuffers();
        gfxFlushBuffers();
        gspWaitForVBlank();	
		
		
	
		if ( inp.kHeld & KEY_START )
			break; // break in order to return to hbmenu
		
		if(inp.runApp)
		{
			interface.runApp(&inp);
		}
		else
			runSynth(&waveData, &inp);	
	}

 
	saveButtons();
    gfxExit();

    return 0;
}
