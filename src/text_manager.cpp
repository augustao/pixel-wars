// Text manager for SDL_TTF by Alpha Nox

#include "text_manager.h"

using namespace std;

extern SDL_Surface *screen;

string IntToString(int num)
{
	ostringstream myStream;
	myStream << num << flush;
	return(myStream.str()); 
}

bool compareSDL_Color(SDL_Color &col1,SDL_Color &col2)
{
	if(col1.r != col2.r || col1.g != col2.g || col1.b != col2.b) {
		return false;
	} else {
		return true;
	}
}


fontinfo::fontinfo(string fname,int fsize)
{
	name = fname;
	size = fsize;

	font = TTF_OpenFont(name.c_str(),size);

	if(font == NULL) cerr << "ERROR: Couldn't open font '" << name << "' !!!!\n";
}

void text_system_class::Init()
{
	TTF_Init();

	SetCacheSize(1000);

	// Sets default font to be used
	Default_Font = "CBM-64.TTF";

	// Preload commonly used fonts
	LoadFont(Default_Font,12);
	LoadFont(Default_Font,14);
	LoadFont(Default_Font,16);
	LoadFont(Default_Font,18);
	LoadFont(Default_Font,22);
	LoadFont(Default_Font,24);
	LoadFont(Default_Font,28);
	LoadFont(Default_Font,36);
	LoadFont(Default_Font,72);
}

void text_system_class::Shutdown()
{
	for(currentfont = fontsDB.begin();currentfont != fontsDB.end();currentfont++) {
		TTF_CloseFont(currentfont->font);
	}

	for(ctextsITR = cachedtexts.begin();ctextsITR != cachedtexts.end();ctextsITR++) {
		SDL_FreeSurface(ctextsITR->second.surface);
	}
}

void text_system_class::SetCacheSize(size_t c_size)
{
	cachesize = c_size;
}

void text_system_class::AddToCache(string textline,cachedtext &ctext)
{
	// Adds to cache
	cachedtexts.insert(pair<string,cachedtext>(textline,ctext));
	cache_queue.push(textline);

	// Gets the used amount of the cache
	size_t used_cache_size = cachedtexts.size();

	// Finishes functions if there is still free cache space
	if(used_cache_size < cachesize)		return;

	// Cache is full, erases oldest entry to acquire free space
	ctextsITR = cachedtexts.find(cache_queue.front());
	SDL_FreeSurface(ctextsITR->second.surface);
	cachedtexts.erase(ctextsITR);
	cache_queue.pop();
}

void text_system_class::LoadFont(string name,int size)
{
	// Creates font based on the info received
	fontinfo newfont(name,size);

	// Adds the new loaded font to the database
	fontsDB.push_back(newfont);
}

void text_system_class::SetCurrentFont(string name,int size)
{
	// Checks if the requested font has been loaded and sets the iterator
	for(currentfont = fontsDB.begin();currentfont != fontsDB.end();currentfont++) {
		if(currentfont->name == name && currentfont->size == size) {
			// Iterator is pointing to the requested font, returning
			return;
		}
	}


	// The requested font has not been loaded yet
	cout << "Requested font not in memory, loading...\n";

	LoadFont(name,size);

	currentfont = fontsDB.end();
	currentfont--;

	if(currentfont->name == name && currentfont->size == size) {
		// Font loaded and iterator is pointing correctly, returning		
		return;
	}

	// Iterator is not right, abnormal error
	cerr << "ERROR: SetCurrentIterator() didn't work!\n";
	exit(1);
}

void text_system_class::AddTextToQueue(const char* text,int size,int X,int Y,int fR,int fG,int fB,int bR,int bG,int bB)
{
	queuedtext newtext;

	newtext.text = const_cast<char*>(text);
	newtext.size = size;
	newtext.X = X;
	newtext.Y = Y;
	newtext.fR = fR;
	newtext.fG = fG;
	newtext.fB = fB;
	newtext.bR = bR;
	newtext.bG = bG;
	newtext.bB = bB;
	newtext.bB = bB;

	text_queue.push(newtext);
}

void text_system_class::DrawQueuedTexts()
{
	queuedtext *p;

	while(!text_queue.empty()) {
		p = &text_queue.front();
		DrawText(p->text,p->size,p->X,p->Y,p->fR,p->fG,p->fB,p->bR,p->bG,p->bB,255);
		text_queue.pop();
	}
}

void text_system_class::DrawText(long number,int size,int X,int Y,int fR,int fG,int fB,int bR,int bG,int bB,int alpha)
{
	//char text1[100];
	//itoa(number,text1,10);
	//char* text = text1;
	string newtxt = IntToString((int)number);
	DrawText(const_cast<char*>(newtxt.c_str()),size,X,Y,fR,fG,fB,bR,bG,bB,alpha);
}

void text_system_class::DrawText(const char* text,int size,int X,int Y,int fR,int fG,int fB,int bR,int bG,int bB,int alpha)
{
	SDL_Color fgcolor = { fR, fG, fB };
	SDL_Color bgcolor = { bR, bG, bB };

	// Searches cache for the requested text
	string textstr = text; 
	cachedtext ct;

	size_t keys_amount = cachedtexts.count(textstr);

	if(keys_amount == 1) {
		ctextsITR = cachedtexts.find(textstr);
		ct = ctextsITR->second;
		if(ct.fontname == Default_Font) {
			if( ct.size == size) {
				if(compareSDL_Color(fgcolor,ct.fG) && compareSDL_Color(bgcolor,ct.bG )) {
					// Found in cache...
					SDL_Rect textloc = { X, Y, ct.surface->w , ct.surface->h }; 

					SDL_BlitSurface(ct.surface, NULL, screen, &textloc);

					return;
				}
			}
		}
	} else if(keys_amount > 1) {
		pair<multimap<string,cachedtext>::iterator,multimap<string,cachedtext>::iterator> range_pair;
		range_pair = cachedtexts.equal_range(textstr);
		for(ctextsITR = range_pair.first;ctextsITR != range_pair.second;ctextsITR++) {
			ct = ctextsITR->second;
			if(ct.fontname == Default_Font) {
				if( ct.size == size) {
					if(compareSDL_Color(fgcolor,ct.fG) && compareSDL_Color(bgcolor,ct.bG )) {
						// Found in cache...
						SDL_Rect textloc = { X, Y, ct.surface->w , ct.surface->h }; 
						SDL_BlitSurface(ct.surface, NULL, screen, &textloc);

						return;
					}
				}
			}
		}
	}
	// Requested text not found in cache, rendering it...
	SetCurrentFont(Default_Font,size);

	SDL_Surface* textSurface2 = TTF_RenderText_Shaded(currentfont->font, text,fgcolor,bgcolor);

	if(fR == 0 && fG == 0 && fB == 0) {
		SDL_SetColorKey(textSurface2, SDL_SRCCOLORKEY, SDL_MapRGB(textSurface2->format, 255, 255, 255) );
	} else {
		SDL_SetColorKey(textSurface2, SDL_SRCCOLORKEY, SDL_MapRGB(textSurface2->format, 0, 0, 0) );
	}

	if(alpha < 255) {
		SDL_SetAlpha(textSurface2,SDL_SRCALPHA,(Uint8) alpha);
	}

	SDL_Surface* textSurface = SDL_DisplayFormat(textSurface2);
	SDL_Rect textLocation = { X, Y, textSurface->w , textSurface->h }; 
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

	// Adds the line that was drawn to cache
	cachedtext newtext;
	newtext.fG = fgcolor;
	newtext.bG = bgcolor;
	newtext.fontname = Default_Font;
	newtext.size = size;
	newtext.surface = textSurface;
	AddToCache(textstr,newtext);

	// Frees the used surfaces
	SDL_FreeSurface(textSurface2);
}
