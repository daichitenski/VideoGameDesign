#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include "Deck.h"
#include "CardImage.h"
#include "includes.h"
#include "Slider.h"
#include "SlidingCard.h"
#include "Board.h"
#include "Discard.h"

class Player{
	Hand h; //Hidden Play Hand
	/* I made these pointers for constructor purposes. I couldn't get it to work otherwise.
	   We might have to be careful about cleaning up the Boards if we start deleting players. */

	Board *upBoard; //Face up Board Hand Section
	Board *db; //Face down Board Hand section 
	int maxHand; //Number per hand based on deck
	int maxBoard; //Number for board cards based on deck
	bool main; // True if this is player 1
	int mine;

public:
	void init(Deck &d, bool mainPlayer, int deckNum=1, int myTurn = 0); //I still have to take into consideration the number of players playing
	void drawHand(CardImage *c, SDL_Surface *screen);
	void drawBoard(CardImage *c, SDL_Surface *screen,int turn);
	void draw(CardImage *cards, CardImage *smallCards, SDL_Surface *screen,int turn);
	void pickCard(int idx);
	void drawFromDeck(Deck *d);
	int getHandViewMin();
	int getNumCardsInHand();
	/*MY_STUFF*/
	bool isValid_Move(vector<Card> player_hand, Card pile); //returns true if the hand passed in can be played 
	void translateHandView(int offset);
	void handle_input(SDL_Event &event, bool &done, bool &mouseDown, SlidingCard &sc, Slider &slide, int &handPixelWidth, int &adjustment, Deck &d, Discard &discardPile, int &turn);
};

#endif