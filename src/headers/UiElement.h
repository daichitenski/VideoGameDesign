#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "includes.h"

class UIElement
{ 
	protected:
		int posX, posY, width, height;
		SDL_Rect source, destination;
		SDL_Surface *spriteSheet;
	
	public:
		int getXPos(){return posX;};
		int getYPos(){return posY;};
		void setXPos(int newPosX){posX = newPosX;};
		void setYPos(int newPosY){posY = newPosY;};
		int getWidth(){return width;};
		int getHeight(){return height;};
		void setWidth(int newWidth){width = newWidth;};
		void setHeight(int newHeight){height = newHeight;};
		
		virtual void draw(SDL_Surface *screen){};
};

#endif