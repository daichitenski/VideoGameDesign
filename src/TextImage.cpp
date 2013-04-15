#include "headers/TextImage.h"

	void TextImage::init(string fName, int size){
		TTF_Init();
		fontName = fName;
		font = TTF_OpenFont(fontName.c_str(),size);
		txtColor.r=txtColor.g=220;
		txtColor.b=120;
	}
	void TextImage::setSize(int size){
		font = TTF_OpenFont(fontName.c_str(),size);
	}
	void TextImage::setColor(SDL_Color fColor){
		txtColor = fColor;
	}
	void TextImage::setColor(int r, int g, int b){
		txtColor.r = r;
		txtColor.g = g;
		txtColor.b = b;
	}
	void TextImage::setText(string t){
		imgTxt = TTF_RenderText_Solid(font,t.c_str(),txtColor);
	}
	void TextImage::draw(SDL_Surface *screen, int x, int y){
		txtWindow.x = x;
		txtWindow.y = y;
		SDL_BlitSurface(imgTxt,NULL,screen,&txtWindow);
	}