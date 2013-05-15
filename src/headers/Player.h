#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "CardImage.h"
#include "Deck.h"
#include "Discard.h"
#include "Hand.h"
#include "includes.h"
#include "Slider.h"
#include "SlidingCard.h"
#include "Sound.h"

#define NUM_AUDIO_FILES 7

class Player{
	
	/* I made these pointers for constructor purposes. I couldn't get it to work otherwise.
	   We might have to be careful about cleaning up the Boards if we start deleting players. */

	bool main; // True if this is player 1
	int maxHand; //Number per hand based on deck
	int maxBoard; //Number for board cards based on deck
	int mine;
	Hand h; //Hidden Play Hand
	sound* FX;
	
private:
	void buffer_audio(); //Loads all the audio files into ram 
	void play_rnd();
	
public:
	void init(Deck &d, bool mainPlayer, int deckNum=1, int myTurn = 0); //I still have to take into consideration the number of players playing
	//~Player(); //destructor to free up audio resources
	Board *upBoard; //Face up Board Hand Section
	Board *db; //Face down Board Hand section 
	
	void drawHand(CardImage *c, SDL_Surface *screen);
	void drawBoard(CardImage *c, SDL_Surface *screen,int turn);
	void draw(CardImage *cards, CardImage *smallCards, SDL_Surface *screen,int turn);
	void pickCard(int idx);
	void drawFromDeck(Deck *d);
	int getHandViewMin();
	Hand* getHand();
	int getMaxHand();
	int getMaxBoard();
	int getNumCardsInHand();
	bool upBoardIsEmpty();
	bool downBoardIsEmpty();
	bool Is_Lowest(vector<Card> &test, int val); //Returns true if the value passed in is the lowest card in the deck
	bool Is_Lowest_Beat(vector<Card> &test, int pile_card, int val);
	bool Is_Last(int val, int pile_card); //Returns true if the value passed into the function is the only valid move the player can make
	bool Validate_Two(vector<Card> &test, int pile_card); //Validatates the conditions needed to determine if a hand containing the two special card was correctly played
	bool Validate_Ten(vector<Card> &test); //Return true if a single or multiple 10's are passed into the funcion also play a sound
	bool isValid_Move(vector<Card> &player_sel, int pile_card,bool playFromHand); //returns true if the hand passed in can be played 
	void translateHandView(int offset);
};

#endif