#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include "Deck.h"
#include "LuckyB.h"

class Hand{
	int numCards, viewMin;
	SDL_Surface *handSurface;
	SDL_Rect handSpace;
	static const int HAND_HEIGHT = 140;
	static const int HAND_WIDTH = 4000;
	static const int VIEW_WINDOW_WIDTH = 630;
	static const int VIEW_WINDOW_STEP = 45;

public:
	vector<Card> handList;
	Hand();
	void drawFromDeck(Deck *d);
	void insert(vector<Card> inCards);
	void insert(Card newCard);
	void sortHand();
	void outputHand();
	void highlightCard(int idx);
	void draw(CardImage *c, SDL_Surface *screen);
	bool isEmpty();
	int getViewMin();
	void translateView(int offset);
	int getNumCards();
	vector<Card> getHand();
	int playHand();
	void remove(vector<Card> inCards);
	void remove(Card newCard);
};

#endif