#ifndef BUTTON_H
#define BUTTON_H

#include "UiElement.h"
#include "includes.h"

class Button: public UIElement{
	
public:
	Button(){};
	Button(int newX, int newY, int width, int height, string spriteName, SDL_Surface *screen);
	void draw(SDL_Surface *screen);
	void clicked();
	void released();
	bool active;
};

#endif