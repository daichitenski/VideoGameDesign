#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "TextImage.h"
#include "BackgroundImage.h"
#include "CardImage.h"
#include "Deck.h"
#include "Player.h"
#include "Discard.h"
#include "Button.h"
#include "Slider.h"
#include "SlidingCard.h"

class Game
{
private:
	SDL_Event event;
	SDL_Surface *screen;
	bool done;
	TextImage bigText;
	TextImage smallText;
	
	
	BackgroundImage bg;
	CardImage cardImages;
	CardImage smallCardImages;
	Deck d;
	
	//players should be at least an array, so we can have more than 2; probably a vector
	Player p1;
	Player p2;
	Discard discardPile;
	Button menuButton;
	Button doneButton;
	int windowMin;

	vector<UIElement> ui;
	
	Slider slide;
	bool mouseDown;
	int handPixelWidth;
	int adjustment;
	stringstream ss;

	//SlidingCard sc = SlidingCard(-1,-600);
	SlidingCard sc;
	int turn;
public:
	
	void init();
	void run();
	void end();
};

#endif