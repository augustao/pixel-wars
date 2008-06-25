/*

 @@@@@@@  @@@ @@@  @@@ @@@@@@@@ @@@     
 @@!  @@@ @@! @@!  !@@ @@!      @@!     
 @!@@!@!  !!@  !@@!@!  @!!!:!   @!!     
 !!:      !!:  !: :!!  !!:      !!:     
  :       :   :::  ::: : :: ::: : ::.: :
                                        
 @@@  @@@  @@@  @@@@@@  @@@@@@@   @@@@@@
 @@!  @@!  @@! @@!  @@@ @@!  @@@ !@@    
 @!!  !!@  @!@ @!@!@!@! @!@!!@!   !@@!! 
  !:  !!:  !!  !!:  !!! !!: :!!      !:!
   ::.:  :::    :   : :  :   : : ::.: : 

 Start: June 24th, 2008

*/

#include "main.h"
#include "defines.h"
#include "GS_memory.h"
#include "text_manager.h"
#include "timer.h"

using namespace std;

// Global Variables

bool FULL_SCREEN = 0;

// the screen surface
SDL_Surface* screen;

// Global Classes

mem_manager_class MEM;
text_system_class TextSYS;
Timer fpss;

stack<StateStruct> StateStack;

// Function declarations

void ClearScreen()
{
	SDL_FillRect(screen, 0, 0);
}

void Game()
{
	ClearScreen();
	
	if(fpss.get_ticks() >= 1000 / FRAMES_PER_SECOND )
    {
		fpss.start();

		ClearScreen();

		SDL_Flip(screen);
				
		SDL_Delay(10);
		
	}

}

void Init()
{
	// Setup state machine
	
	StateStruct state;
	
	state.StatePointer = Game;
	StateStack.push(state);
	

	if(DEBUG_MSG) cout << "Initializing video...\n";
	
	// Initializes SDL
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

	// Starts OPENGL window
	if(FULL_SCREEN)screen = SDL_SetVideoMode(WINDOW_WIDTH,	WINDOW_HEIGHT, 0, SDL_ANYFORMAT | SDL_GLSDL | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	else screen = SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT, 0, SDL_ANYFORMAT | SDL_GLSDL | SDL_DOUBLEBUF);
	
	if (screen == NULL)
	{
		cerr << "ERROR: Failed to start video: " << SDL_GetError();
		exit(2);
	}

	// SET THE TITLE OF THE GAME SCREEN, DEFINED IN DEFINES.H
    SDL_WM_SetCaption(WINDOW_CAPTION, WINDOW_ICON);
	
	if(DEBUG_MSG) cout << "Initializing memory manager...\n";

	MEM.Init();
	
	if(DEBUG_MSG) cout << "Initializing text system...\n";

	// Initializes text system
	TextSYS.Init();	
	
	fpss.start();

	// Start random number generator
	srand((unsigned)time(0)); 
	
	if(DEBUG_MSG) cout << "Loading game data...\n";
	
}

void Shutdown()
{
	// Shutdown text system
	TextSYS.Shutdown();

	// Frees memory
	MEM.Shutdown();

	// Closes SDL	
	SDL_Quit();

	cout << "Thanks for playing Pixel Wars.\n\n";
}

// Handles command line arguments
void HandleCmdArguments(int argcc,char **argvv)
{
	for (int i = 1; i < argcc; i++) 
	{
		if(strcmp(argvv[i],"-fullscreen") == 0) FULL_SCREEN = 1;
		
	}
}


// Main Function
int main(int argc, char **argv)
{
	system("cls");
	
	HandleCmdArguments(argc,argv);
	
	cout << "Pixel Wars by Magic Pixels Entertainment!\n\n";

	Init();

	while(!StateStack.empty())
	{
		
      	StateStack.top().StatePointer();
	
	}
    	
	Shutdown();

	return 0;

}

