#ifndef SLIDINGCARD_H
#define SLIDINGCARD_H

#include "includes.h"
#include "CardImage.h"

class SlidingCard{
	double x, y, xvel, yvel;
	bool done;
	long last;
public:
	void init(double xv, double yv);
	void setSpeeds(double xv, double yv);
	void update();
	void reset();
	void draw(CardImage *c, SDL_Surface *screen);
};

#endif