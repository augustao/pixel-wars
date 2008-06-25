// Text manager for SDL_TTF by Alpha Nox

#ifndef TEXT_MAN_232919283123
#define TEXT_MAN_232919283123



#include "main.h"

using namespace std;

bool compareSDL_Color(SDL_Color &col1,SDL_Color &col2);

class fontinfo
{
public:
	TTF_Font* font;
	string name;
	int size;
	fontinfo(string fname,int fsize);
	
};



struct cachedtext
{

	SDL_Surface* surface;
	string fontname;
	int size;
	SDL_Color fG;
	SDL_Color bG;
	
};

struct queuedtext
{

	char* text;
	int size;
	int X;
	int Y;
	int fR;
	int fG;
	int fB;
	int bR;
	int bG;
	int bB;

};

class text_system_class
{
	
	// Text Cache
	// Number of text lines to be cached
	size_t cachesize;

	// Multimap that holds all the text lines in cache
	multimap<string,cachedtext> cachedtexts;
	multimap<string,cachedtext>::iterator ctextsITR;
	// Queue that allows us to know the oldest value in cache and remove it to free space
	queue<string> cache_queue;

	void AddToCache(string textline,cachedtext &ctext);


	// The queue that holds the texts that will be displayed later(when DrawQueuedTexts() is called)
	queue<queuedtext> text_queue;
	
	// Vector that holds all the loaded fonts
	vector<fontinfo> fontsDB;
	vector<fontinfo>::iterator currentfont;
	void SetCurrentFont(string font,int size);

	string Default_Font;


public:

	// Initializes the text system (must be called before using it)
	void Init();

	// Unloads the system(must be called before exitting!)
	void Shutdown();
	
	
	// Sets the size of the cache, setting cachesize to 0 disables it and it is not recommended
	void SetCacheSize(size_t c_size);
	
	// Loads the requested font
	void LoadFont(string name,int size);

	// Text queue related functions

	void AddTextToQueue(const char* text,int size,int X,int Y,int fR,int fG,int fB,int bR,int bG,int bB);

	void DrawQueuedTexts();

	// Draw text line

	void DrawText(const char* text,int size,int X,int Y,int fR,int fG,int fB,int bR,int bG,int bB,int alpha);

	void DrawText(long number,int size,int X,int Y,int fR,int fG,int fB,int bR,int bG,int bB,int alpha);
	

};

string IntToString(int num);

#endif