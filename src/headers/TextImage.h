#ifndef TEXTIMAGE_H
#define TEXTIMAGE_H

#include "cards.h"

using namespace std;

class TextImage{
	TTF_Font *font;
	SDL_Surface *imgTxt;
	SDL_Rect txtWindow;
	SDL_Color txtColor;
	string fontName;

public:
	void init(string fName, int size);
	void setSize(int size);
	void setColor(SDL_Color fColor);
	void setColor(int r, int g, int b);
	void setText(string t);
	void draw(SDL_Surface *screen, int x, int y);
};

#endif