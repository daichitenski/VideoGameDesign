#include "headers/Button.h"

Button::Button(int newX, int newY, int newWidth, int newHeight, string spriteName, SDL_Surface *screen)
{
	posX = newX;
	posY = newY;
	width = newWidth;
	height = newHeight;
	active = false;
	
	SDL_Surface *image;
	int colorKey;
	string sheetPath = "../images/" + spriteName + ".bmp";
	image = SDL_LoadBMP(sheetPath.data());
	spriteSheet = SDL_ConvertSurface(image,screen->format, SDL_HWSURFACE);
	colorKey=SDL_MapRGB(screen->format,255,0,255);
	SDL_SetColorKey(spriteSheet, SDL_SRCCOLORKEY,colorKey);
	
	SDL_FreeSurface(image);
	
	source.x=0;
	source.y=0;
	source.w = width;
	source.h = height;
	
	destination.x = posX;
	destination.y = posY;
	destination.w = width;
	destination.h = height;
}

void Button::draw(SDL_Surface *screen)
{
	SDL_BlitSurface(spriteSheet,&source,screen,&destination);
}

void Button::clicked()
{
	active = true;
	source.x = source.w;
}

void Button::released()
{
	active = false;
	source.x = 0;
}