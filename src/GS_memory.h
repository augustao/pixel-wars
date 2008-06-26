/* 

   GLSDL/SDL MEMORY MANAGER
   WRITTEN BY ALPHA NOX

*/
#ifndef H_GS_MEM
#define H_GS_MEM

#include "main.h"

using namespace std;

// MEMORY MANAGER 
class mem_manager_class
{
	multimap<string,SDL_Surface*> surfaces;
	multimap<string,SDL_Surface*>::iterator surfsITR;

	multimap<string,Mix_Chunk*> chunks;
	multimap<string,Mix_Chunk*>::iterator chunksITR;

	multimap<string,Mix_Music*> musics;
	multimap<string,Mix_Music*>::iterator musicsITR;

	string lastmusic;

public:
	// Obvious...
	void Init();
	void Shutdown();
	void Flush();

	string SurfTypeToPath(string type);

	// Audio managers
	void LoadSFX(string name);
	void LoadMusic(string name,bool is_ogg);

	Mix_Music* GetMusic(string name);
	string GetLastMusicName();
	Mix_Chunk* GetSFX(string name);

	// Surfaces managers
	void LoadSurf(string name,string type);
	void LoadSurf(string name,string type,int cR,int cG,int cB);
	SDL_Surface* GetSurf(string s_name,string type);
};

#endif
