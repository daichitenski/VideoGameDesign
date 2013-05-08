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
	
/*	void init(SDL_Surface *screen, int inx, int iny, int inw, int inh, bool newactive, int row);
	void draw(SDL_Surface *s);
	int getXPos();
	int getYPos();
	int getW();
	int getH();
	void switchActive();
	bool clicked(int clickX, int clickY);
	void execute();*/
};

#endif