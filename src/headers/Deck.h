#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "CardImage.h"

class Deck{
	deque<Card> deckList;
	int numCards;
	int numDecks;

public:
	void init(int numDecks);
	void outputDeck();
	void draw(CardImage *c, SDL_Surface *screen);
	Card drawCard();
	int getNumCards();
	int getNumDecks();
	bool isEmpty();
};

#endif