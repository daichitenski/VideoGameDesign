#include "headers/BackgroundImage.h"

void BackgroundImage::init(string name, SDL_Surface *s){
		fname = name;
		screen = s;
		init();
	}
	void BackgroundImage::init(){
		bg = SDL_LoadBMP(fname.c_str());
		src.x = 0; src.y = 0; src.w = SCREENWIDTH; src.h = SCREENHEIGHT;
	}
	void BackgroundImage::draw(){
		SDL_BlitSurface(bg, &src, screen, &src);
	}
