#ifndef MAIN_H_34837243279342
#define MAIN_H_34837243279342

#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

#include <stdio.h>  
#include <stdlib.h>
#include <time.h>

#include <stack>

#include "SDL.h"
#include "SDL_TTF.h"
#include "SDL_image.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_mixer.h"
#include "glSDL.h"

#include "windows.h"
#include <GL/gl.h>
#include <GL/glu.h>


#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_image.lib")
#pragma comment(lib, "SDLgfx.lib")
#pragma comment(lib, "SDL_TTF.lib")
#pragma comment(lib, "SDL_mixer.lib")
#pragma comment(lib, "opengl32.lib")

#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;



struct StateStruct 
 {
   void (*StatePointer)();
};

string IntToString(int num);



#endif // MAIN_H_34837243279342