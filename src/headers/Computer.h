#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"
#include "Hand.h"
#include "Deck.h"
#include "Discard.h"
#include "Board.h"

class Computer:public Player
{
private:
	Hand h; //Hidden Play Hand
	Board *upBoard; //Face up Board Hand Section
	Board *db; //Face down Board Hand section 
	int maxHand; //Number per hand based on deck
	int maxBoard; //Number for board cards based on deck
	bool main; // True if this is player 1
	
public:
	void play(Deck &d, Discard &dis);
};

#endif