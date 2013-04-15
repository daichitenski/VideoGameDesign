#ifndef CARDIMAGE_H
#define CARDIMAGE_H

#include "cards.h"

using namespace std;

class CardImage{
	string fname;
	SDL_Surface *cardSheet;
	SDL_Rect src, dest;
	bool small;

public:
	const static int OFFSET = 10;
	const static int OFFSET_SMALL = 3;
	
	void init(string name, SDL_Surface *screen, bool smallCards=false);
	void init(string name, int val, SDL_Surface *screen, bool smallCards = false);
	void init(SDL_Surface *screen);
	void selectCard(int val, bool selected=false, bool flipped = false);
	void draw(SDL_Surface *s, int x, int y);
};

#endif