#ifndef BOARD_H
#define BOARD_H

#include "Card.h"
#include "Deck.h"

class Board // The Board Hand Class
{
private:
	bool topLayer, main;
	
public:
	int numCards;
	vector<Card> boardList;
	Board(bool m);
	void drawFromDeck(Deck *d, bool up);
	void insert(vector<Card> inCards);
	void insert(Card newCard);
	void outputHand();
	void draw(CardImage *c, SDL_Surface *screen, int mine, int turn);
	bool isEmpty();
};

#endif