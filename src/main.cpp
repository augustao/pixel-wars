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
bool FULL_SCREEN = false;

// If a certain key is held or not
bool keysHeld[323] = {false};
// SDL_Event structure
SDL_Event Event;

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


void GameInput()
{
	// Fill our Event structure with Event information.
    if ( SDL_PollEvent(&Event) )
    {
        // Handle user manually closing game window
        if (Event.type == SDL_QUIT)
        { 
            // While state stack isn't empty, pop 
            while (!StateStack.empty())
            {
                StateStack.pop();
            }

            return; // game is over, exit the function
        }
				
		if (Event.type == SDL_KEYDOWN)
        {
            keysHeld[Event.key.keysym.sym] = true;
			// For actions that are do not occur again if the key is still pressed, put inside this if
			if (Event.key.keysym.sym == SDLK_LEFT)
			{
				
				return;
				
			}
								
		 } 
         if (Event.type == SDL_KEYUP)
         {
            keysHeld[Event.key.keysym.sym] = false;

			
         }

		 if (Event.key.keysym.sym == SDLK_ESCAPE)
         {
				
			StateStack.pop();
            return; 
            
         } 
	}
 		    
	
	if (keysHeld[SDLK_u])
	{
				
		return;
	}


}

void Game()
{
	if (fpss.get_ticks() >= 1000 / FRAMES_PER_SECOND) {
		fpss.start();
		ClearScreen();
		GameInput();
		SDL_Flip(screen);
		Sleep(10);
	}
}

void Init()
{
	// Setup state machine
	StateStruct state;
	state.StatePointer = Game;
	StateStack.push(state);

	if (DEBUG_MSG) {
		cout << "Initializing video...\n";
	}

	// Initializes SDL
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

	// Starts OPENGL window
	if (FULL_SCREEN) {
		screen = SDL_SetVideoMode(WINDOW_WIDTH,	WINDOW_HEIGHT, 0, SDL_ANYFORMAT | SDL_GLSDL | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	} else {
		screen = SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT, 0, SDL_ANYFORMAT | SDL_GLSDL | SDL_DOUBLEBUF);
	}

	if (screen == NULL) {
		cerr << "ERROR: Failed to start video: " << SDL_GetError();
		exit(2);
	}

	// SET THE TITLE OF THE GAME SCREEN, DEFINED IN DEFINES.H
	SDL_WM_SetCaption(WINDOW_CAPTION, WINDOW_ICON);

	if (DEBUG_MSG) {
		cout << "Initializing memory manager...\n";
	}

	MEM.Init();

	if (DEBUG_MSG) {
		cout << "Initializing text system...\n";
	}

	// Initializes text system
	TextSYS.Init();	
	fpss.start();

	// Start random number generator
	srand((unsigned)time(0)); 

	if (DEBUG_MSG) {
		cout << "Loading game data...\n";
	}
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
	for (int i = 1; i < argcc; i++) {
		if (strcmp(argvv[i],"-fullscreen") == 0) {
			FULL_SCREEN = true;
		}
	}
}


// Main Function
int main(int argc, char **argv)
{
	HandleCmdArguments(argc,argv);

	cout << "Pixel Wars by Magic Pixels Entertainment!\n\n";

	Init();

	while(!StateStack.empty()) {
		StateStack.top().StatePointer();
	}

	Shutdown();

	return 0;
}

