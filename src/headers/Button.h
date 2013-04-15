#ifndef BUTTON_H
#define BUTTON_H

#include "UiElement.h"
#include "includes.h"

class Button: public UIElement{

	//680x530
private:
	int xpos, ypos, w, h;
	bool active;
	SDL_Surface *buttonSheet;
	SDL_Rect src, dest;

public:
	static const int BUTTON_WIDTH = 105;
	static const int BUTTON_HEIGHT = 55;
	static const int Y_OFFSET = 2;
	static const int X_OFFSET = 4;
	void init(SDL_Surface *screen, int inx, int iny, int inw, int inh, bool newactive, int row);
	void draw(SDL_Surface *s);
	int getXPos();
	int getYPos();
	int getW();
	int getH();
	void switchActive();
	bool clicked(int clickX, int clickY);
	void execute();
};

#endif