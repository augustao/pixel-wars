/* 

GLSDL/SDL MEMORY MANAGER
WRITTEN BY ALPHA NOX

*/

#include "GS_memory.h"

bool DEBUG_MSG = false;

using namespace std;


string mem_manager_class::SurfTypeToPath(string type)
{
	if(type == "tile") {
		return "data/graphics/tiles/";
	} else if(type == "bg") {
		return "data/graphics/bg/";
	} else if(type == "effect") {
		return "data/graphics/effects/"; 
	} else if(type == "item") {
		return "data/graphics/items/";
	} else if(type == "misc") {
		return "data/graphics/misc/";
	} else if(type == "missile") {
		return "data/graphic/missiles/";
	} else if(type == "animation") {
		return "data/graphics/animations/";
	} else if(type == "movie") {
		return "data/movies/";
	} else if(type == "default") {
		return "data/graphics/";
	}
	return "data/graphics/test/";
}

string mem_manager_class::GetLastMusicName()
{
	return lastmusic;
}

void mem_manager_class::Init()
{
	lastmusic = "none";
}

void mem_manager_class::Flush()
{
	if (DEBUG_MSG) {
		cout << "Clearing memory...\n";
	}
	surfaces.clear();
	chunks.clear();
	musics.clear();
}

SDL_Surface* mem_manager_class::GetSurf(string s_name,string type)
{
	surfsITR = surfaces.find(s_name);
		
	if (surfsITR == surfaces.end()) {
		if (DEBUG_MSG) {
			cout << "Surface not precached,loading...\n";
		}
		LoadSurf(s_name,type);
		surfsITR = surfaces.find(s_name);
		if (surfsITR == surfaces.end()) {
			cerr << "Loading failed!!! Surface: " << s_name << " - " << type << "\n\n";
			exit(1);
		}
	} else if (surfsITR->second == NULL) {
		cerr << "ERROR: Null surface!\n";
		cerr << surfaces.count(s_name);
		exit(1);
	}
	return surfsITR->second;
}

void mem_manager_class::LoadSurf(string name,string type)
{
	LoadSurf(name,type,255,0,255);
};


Mix_Chunk* mem_manager_class::GetSFX(string name)
{
	chunksITR = chunks.find(name);

	if (chunksITR == chunks.end()) {
		if (DEBUG_MSG) {
			cout << "Chunk not precached,loading...\n";
		}
		LoadSFX(name);
		chunksITR = chunks.find(name);
		if (chunksITR == chunks.end()) {
			cerr << "Loading failed!!! SFX: " << name << "\n\n";
			exit(1);
		}
	}
	return chunksITR->second;
}

Mix_Music* mem_manager_class::GetMusic(string name)
{
	musicsITR = musics.find(name);

	lastmusic = name;
		
	if (musicsITR == musics.end()) {
		if (DEBUG_MSG) {
			cout << "Music not precached,loading...\n";
		}
		LoadMusic(name,false);
		musicsITR = musics.find(name);
		if (musicsITR == musics.end()) {
			LoadMusic(name,true);
			musicsITR = musics.find(name);
			if (musicsITR == musics.end()) {
				cerr << "Loading failed!!! Music: " << name << "\n\n";
				exit(1);
			}
		}
	}
	return musicsITR->second;
}

void mem_manager_class::LoadSFX(string name)
{
	string path = "data/sfx/";
	path += name + ".ogg";
	
	Mix_Chunk *newchunk = Mix_LoadWAV(path.c_str());
	if (newchunk == NULL) {
		path = "data/sfx/";
		path += name + ".wav";
		newchunk = Mix_LoadWAV(path.c_str());
		if (newchunk == NULL) {
			cerr << "Error loading sfx: " << path << "\n\n";
			return;
		}
	}
	chunks.insert(pair<string,Mix_Chunk*>(name,newchunk));
}

void mem_manager_class::LoadMusic(string name,bool is_ogg)
{
	string path = "data/music/" + name;
	if (is_ogg) {
		path += ".ogg";
	} else {
		path += ".mid";
	}

	Mix_Music *newmusic = Mix_LoadMUS(path.c_str());
	if (newmusic == NULL) {
		if(DEBUG_MSG) {
			cerr << "Error loading music: " << path << "\n\n";
		}
		return;
	}
	musics.insert(pair<string,Mix_Music*>(name,newmusic));
}

void mem_manager_class::LoadSurf(string name,string type,int cR,int cG,int cB)
{
	// Loads an image with the default color key(255 0 255)
	
	SDL_Surface *temp, *temp2;
	
	string path = SurfTypeToPath(type);
	path += name + ".bmp";
	
	temp2 = IMG_Load(path.c_str());
	
	if (temp2 == NULL) {
		string path = SurfTypeToPath(type);
		path += name + ".png";
		temp2 = IMG_Load(path.c_str());
		if (temp2 == NULL) {
			cerr << "CRITICAL ERROR: Failed to open \"" << path<< "\" !!! \n";
			cerr << "REASON: " << IMG_GetError() << endl;
		
			system("pause");

			exit(1);
		}
	}
	SDL_SetColorKey(temp2, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(temp2->format, cR, cG, cB) );

	temp = SDL_DisplayFormat(temp2);

	SDL_FreeSurface(temp2);
	
	surfaces.insert(pair<string,SDL_Surface*>(name,temp));
}

void mem_manager_class::Shutdown()
{
	for (surfsITR = surfaces.begin();surfsITR != surfaces.end();surfsITR++) {
		SDL_FreeSurface(surfsITR->second);
	}
	
	for (chunksITR = chunks.begin();chunksITR != chunks.end();chunksITR++) {
		Mix_FreeChunk(chunksITR->second);
	}

	for (musicsITR = musics.begin();musicsITR != musics.end();musicsITR++) {
		Mix_FreeMusic(musicsITR->second);
	}
}
