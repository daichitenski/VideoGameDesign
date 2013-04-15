#include "headers/CardImage.h"

	void CardImage::init(string name, SDL_Surface *screen, bool smallCards){
		fname=name;
		small = smallCards;
		init(screen);
	}

	void CardImage::init(string name, int val, SDL_Surface *screen, bool smallCards){
		fname=name;
		small = smallCards;
		init(screen);
		selectCard(val);
	}

	void CardImage::init(SDL_Surface *screen){
		SDL_Surface *image;
		int colorKey;
		image = SDL_LoadBMP(fname.c_str());
		cardSheet = SDL_ConvertSurface(image,screen->format, SDL_HWSURFACE);
		colorKey=SDL_MapRGB(screen->format,255,0,255);
		SDL_SetColorKey(cardSheet, SDL_SRCCOLORKEY,colorKey);

		SDL_FreeSurface(image);
		if(!small){
			src.x = OFFSET; src.y = OFFSET; src.w = CARDWIDTH; src.h = CARDHEIGHT;
			dest.x =0; dest.y = 0; dest.w = CARDWIDTH; dest.h = CARDHEIGHT;
		}
		else{
			src.x = OFFSET_SMALL; src.y = OFFSET_SMALL; src.w = CARDWIDTH_SMALL; src.h = CARDHEIGHT_SMALL;
			dest.x =0; dest.y = 0; dest.w = CARDWIDTH_SMALL; dest.h = CARDHEIGHT_SMALL;			
		}
	}
	void CardImage::selectCard(int val, bool selected, bool flipped){
		if(!small){
			if(!selected){
				src.x = OFFSET+(OFFSET*val) + CARDWIDTH*val;
				src.y = OFFSET;
			}
			else{
				src.x = OFFSET+1+(OFFSET*val) + CARDWIDTH*val;
				src.y = (OFFSET*3)+CARDHEIGHT;
			}
		}
		else{
			if(!flipped){
				src.x = OFFSET_SMALL+(OFFSET_SMALL*val) + CARDWIDTH_SMALL*val;
				src.y = OFFSET_SMALL;
			}
			else{
				int temp = OFFSET_SMALL+(OFFSET_SMALL*(val+1))+CARDWIDTH_SMALL*(val+1);
				src.x = CARDSHEET_WIDTH - temp;
				src.y = (4*OFFSET_SMALL)+CARDHEIGHT_SMALL;	
			}
		}
	}
	void CardImage::draw(SDL_Surface *s, int x, int y){
		dest.x = x; dest.y = y;
		SDL_BlitSurface(cardSheet,&src,s,&dest);
	}