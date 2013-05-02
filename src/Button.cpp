#include "headers/Button.h"

Button::Button(int newX, int newY, int newWidth, int newHeight, string spriteName, SDL_Surface *screen)
{
	posX = newX;
	posY = newY;
	width = newWidth;
	height = newHeight;
	
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
	/*void Button::init(SDL_Surface *screen, int inx, int iny, int inw, int inh, bool newactive, int row){
		xpos = inx;
		ypos = iny;
		w = inw;
		h = inh;
		active=newactive;

		SDL_Surface *image;
		int colorKey;
		image = SDL_LoadBMP("../images/buttons.bmp");
		buttonSheet = SDL_ConvertSurface(image,screen->format, SDL_HWSURFACE);
		colorKey=SDL_MapRGB(screen->format,255,0,255);
		SDL_SetColorKey(buttonSheet, SDL_SRCCOLORKEY,colorKey);

		SDL_FreeSurface(image);

		if(row==0 || row==1)
			src.y = BUTTON_HEIGHT*row+2+Y_OFFSET*row;
		else
			src.y=2;
		if(active)
			src.x = 1;
		else
			src.x = 1+X_OFFSET+BUTTON_WIDTH;
		src.w = BUTTON_WIDTH; src.h = BUTTON_HEIGHT;
		dest.x = xpos; dest.y =ypos; dest.w = w; dest.h = h;				
	}
	void Button::draw(SDL_Surface *s){
		SDL_BlitSurface(buttonSheet,&src,s,&dest);
	}
	int Button::getXPos(){
		return xpos;
	}
	int Button::getYPos(){
		return ypos;
	}
	int Button::getW(){
		return w;
	}
	int Button::getH(){
		return h;
	}
	void Button::switchActive(){
		active = !active;
		if(active)
			src.x=1;
		else
			src.x = 1+X_OFFSET+BUTTON_WIDTH;
	}
	bool Button::clicked(int clickX, int clickY){
		bool answer=false;
		if(active)
			if(clickX>xpos && clickX<xpos+w && clickY>ypos && clickY<ypos+h)
				answer=true;

		return answer;
	}
	void Button::execute(){
		cout<<"Button clicked"<<endl;
	}*/