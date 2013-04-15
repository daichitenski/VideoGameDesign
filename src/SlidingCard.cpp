#include "headers/SlidingCard.h"

	void SlidingCard::init(double xv, double yv){
		x=401;
		y=165;
		xvel=xv;
		yvel=yv;
		done = true;
	}
	void SlidingCard::setSpeeds(double xv, double yv){
		xvel=xv;
		yvel=yv;	
	}
	void SlidingCard::update(){
		long next = SDL_GetTicks();
		float deltaT = (float)(next-last);
		last=next;
		if(!done){
			x+=xvel/deltaT;
			y+=yvel/deltaT;
		}
		if(x<(-CARDWIDTH) || x>800 || y<(-CARDHEIGHT) || y>600){
			done=true;
		}
	}
	void SlidingCard::reset(){
		x=401;
		y=165;
		done=false;
		last = SDL_GetTicks();
	}
	void SlidingCard::draw(CardImage *c, SDL_Surface *screen){
		if(!done){
			c->selectCard(13);
			c->draw(screen,x,y);
		}
	}