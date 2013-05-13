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
#include "GameState.h"

class Game: public GameState
{
private:
	SDL_Event event;
	bool done;
	TextImage bigText;
	TextImage smallText;
	bool pickedUp;
	BackgroundImage bg;
	CardImage cardImages;
	CardImage smallCardImages;
	Deck deck;
	
	//players should be at least an array, so we can have more than 2; probably a vector
	Player p1;
	Player p2;
	vector<Player> players;
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
	Game();
	void setName(string newName);
	bool enter(SDL_Surface *newScreen);
	int getNumCardsInDeck();
	string execute();
	void pause(string exitStateName);
	void exit(string exitStateName);
	string handleInput();
};

#endif