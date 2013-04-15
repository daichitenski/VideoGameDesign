#ifndef DISCARD_H
#define DISCARD_H

#include "Card.h"
#include "Deck.h"

class Discard{
	int numCards;
	int numConsecative;
	bool killed;
	
public:
	deque<Card> discardPile;
	void init(Deck *d);
	void outputDiscard();
	void draw(CardImage *c, SDL_Surface *screen);
	void killDiscard();
	int getTopCardValue();
	void layCardPhase(const vector<Card> &playCards, int numDecks=1);//Vector needs to be in the order of first card to play in the front ie) 2, 3, 3 to play the 2 before the 3's
};

#endif