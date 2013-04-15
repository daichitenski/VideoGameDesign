#ifndef SLIDER_H
#define SLIDER_H

#include "includes.h"
#include "UiElement.h"

class Slider: public UIElement{
private:
	int xpos;
	bool active;
	SDL_Rect src, dest;
	SDL_Surface *buttonSheet;
public:
	static const int SLIDER_WIDTH = 84;
	static const int SLIDER_HEIGHT = 37;
	static const int SLIDER_YPOS = 430;
	static const int MAX_SLIDER = 570;
	static const int OFFSET = 5;

	void init(SDL_Surface *screen);
		//changed this to reduce code svp
	bool clicked(int x, int y);
	void translate(int xOffset);
	void draw(SDL_Surface *s, int x);
	void draw(SDL_Surface *s);
	void execute();
	int getX();
};

#endif