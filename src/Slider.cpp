#include "headers/Slider.h"

	void Slider::init(SDL_Surface *screen){
		xpos=0;
		active=true;

		SDL_Surface *image;
		int colorKey;
		image = SDL_LoadBMP("../images/buttons.bmp");
		buttonSheet = SDL_ConvertSurface(image,screen->format, SDL_HWSURFACE);
		colorKey=SDL_MapRGB(screen->format,255,0,255);
		SDL_SetColorKey(buttonSheet, SDL_SRCCOLORKEY,colorKey);

		SDL_FreeSurface(image);

		//row in the sprite sheet
		src.y=120;
		if(active)
			src.x=OFFSET;
		else
			src.x=(OFFSET*2)+SLIDER_WIDTH;

		src.h=SLIDER_HEIGHT; src.w=SLIDER_WIDTH;
		dest.x = xpos; dest.y=SLIDER_YPOS; dest.h=SLIDER_HEIGHT; dest.w=SLIDER_WIDTH;

	}

		//changed this to reduce code svp
	bool Slider::clicked(int x, int y){
		if(active){
			return (x>=xpos+40 && x<xpos+40+SLIDER_WIDTH && y>SLIDER_YPOS && y<SLIDER_YPOS+SLIDER_HEIGHT);
		}
		return false;
	}
	void Slider::translate(int xOffset){
		xpos+=xOffset;
		if(xpos < 0) xpos=0;
		if(xpos > (MAX_SLIDER-SLIDER_WIDTH)) xpos=(MAX_SLIDER-SLIDER_WIDTH);
	}
	void Slider::draw(SDL_Surface *s, int x){
		dest.x=x;
		SDL_BlitSurface(buttonSheet,&src,s,&dest);
	}
	void Slider::draw(SDL_Surface *s){
		dest.x = xpos + 40;
		SDL_BlitSurface(buttonSheet,&src,s,&dest);	
	}
	void Slider::execute(){
		cout<<"Slider clicked"<<endl;
	}
	int Slider::getX(){
		return xpos;
	}