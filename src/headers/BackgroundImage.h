#ifndef BACKGROUNDIMAGE_H
#define BACKGROUNDIMAGE_H

#include "cards.h"

using namespace std;

class BackgroundImage{
	SDL_Surface *bg, *screen;
	SDL_Rect src;
	string fname;
public:
	void init(string name, SDL_Surface *s);
	void init();
	void draw();
};

#endif