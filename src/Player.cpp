#include "headers/Player.h"

	void Player::init(Deck &d, bool mainPlayer, int deckNum, int myTurn) //I still have to take into consideration the number of players playing
	{
	mine = myTurn;
		switch (deckNum) //Determines the number of cards to deal
		{
		case 1:
		case 2: 
			maxHand = 5;
			maxBoard = 3;
			break;
		case 3:
		case 4:
			maxHand = 7;
			maxBoard = 4;
			break;
		case 5:
		case 6:
			maxHand = 13;
			maxBoard = 5;
			break;
		default:
			maxHand = 6;
			maxBoard = 4;
			break;
		}
		for(int i=0;i<maxHand;i++){ //Generates Hand
			h.drawFromDeck(&d);
		}
		h.sortHand();
		upBoard = new Board(mainPlayer);
		db = new Board(mainPlayer);
		for(int i=0;i<maxBoard;i++){ //Generates Board Cards
			upBoard->drawFromDeck(&d, true);
			db->drawFromDeck(&d, false);
		}
		main = mainPlayer;
		cout<<endl;
		h.outputHand();
		cout<<endl;
		upBoard->outputHand();
		cout<<endl;
		db->outputHand();
	}
	void Player::drawHand(CardImage *c, SDL_Surface *screen){
		h.draw(c,screen);
	}
	void Player::drawBoard(CardImage *c, SDL_Surface *screen,int turn){
		db->draw(c,screen,mine,turn);
		upBoard->draw(c,screen, mine, turn);
	}
	void Player::draw(CardImage *cards, CardImage *smallCards, SDL_Surface *screen,int turn){
		if(turn == mine){
			h.draw(cards,screen);	
		}
		db->draw(smallCards,screen,mine, turn);
		upBoard->draw(smallCards,screen,mine, turn);

	}
	void Player::pickCard(int idx){
		h.highlightCard(idx);
	}
	void Player::drawFromDeck(Deck *d){
		if(h.getNumCards() < maxHand)
			h.drawFromDeck(d);
	}
	int Player::getHandViewMin(){
		return h.getViewMin();
	}
	Hand* Player::getHand(){
		return &h;
	}
	int Player::getMaxHand(){
		return maxHand;
	}
	int Player::getMaxBoard(){
		return maxBoard;
	}
	int Player::getNumCardsInHand(){
		return h.getNumCards();
	}
	
	bool Player::Is_Lowest(vector<Card> &test, int val) //if val is the lowest value in the players hand return true
	{
		int min = 9999;
		int this_card = -1;
		cout << "Is_Lowest running: " << test.size() << " loops" << endl;
		for(unsigned int i=0; i<test.size(); i++) //save the lowest value in the players hand 
		{
			this_card = test[i].getCardValue();
			if(this_card < min) min = this_card; //if this card is lower then min then it is the new min
		}
		if(val > min)return false;
		return true;
	}
	
	bool Player::Is_Last(int val, int pile_card) //return true if the player can make no other moves then the value passed into the function
	{
		vector<Card> player_hand = h.getHand(); //Get the players hand
		cout << "Is Last\n";
		for(unsigned int i=0; i<player_hand.size(); i++)
		{
			if(player_hand[i].getCardValue() == 10) return false; //10s are always playable
			else if(player_hand[i].getCardValue() < val)
			{
				if(player_hand[i].getCardValue() != 2) return false; //there is another valid move
			}
		}
		return true;
	}
	
	bool Player::Validate_Two(vector<Card> &test, int pile_card) //finish me to check that any other cards played are the lowest in players hand
	{
		int last_card = -1;
		int this_card = test[0].getCardValue();
		vector<Card> player_hand = h.getHand();
		cout << "Validate Two\n";
		
		if(test.size() == 1) //if they just played a single 2 and they have no other valid moves
		{
			if(Is_Last(this_card, pile_card)) return true;
			else return false;
		}
		else
		{
			for(unsigned int i=1; i<test.size(); i++)
			{
				this_card = test[i].getCardValue();
				if(i==1)
				{
					if(this_card == 2); //continue
					else if(Is_Last(this_card, 2));
					{
						if(!Is_Lowest(player_hand, this_card)) return false; //Test that the 2nd card is lowest in the players hand if isn't then this move is invalid
					}	
				}
				else
				{
					if(this_card != last_card) return false; //if they try to play more then two different cards that aren't the same the move is invalid 
				}
				last_card = test[i].getCardValue(); //save the value of the card for later comparison
			}
		}
		return true;
	}

	bool Player::isValid_Move(vector<Card> &play_sel, int pile_card) //returns true if the hand passed in can be played 
	{
		bool is_valid = true;
		unsigned int last_card = -1;
		unsigned int this_card = play_sel[0].getCardValue();
		cout << "First card played " << this_card << " card on pile " << pile_card << " First card selected " << endl;
		if(play_sel.size() == 1) //player is trying to play a single card
		{
			//Christina: 2 is only valid by itself if it is the last card the player can play
			if((this_card == 10)) return true; //A single 10 is always valid
			else if(this_card == 2) return Validate_Two(play_sel, pile_card);
			else if(this_card < pile_card) 
			{
				cout << "Comparing " << this_card << " with " << pile_card << endl;
				is_valid = false; //a hand smaller then the value of the deck card is invalid
			}
		}
		else //player is trying to play more then one card
		{
			cout << "Testing full hand\n";
			for(unsigned int i=0; i<play_sel.size(); i++)
			{	
				this_card = play_sel[i].getCardValue(); //save the value of first card
				if(this_card == 10) is_valid = true; //killzed it as long as they didn't try to play any other cards
				else if(this_card == 2) return Validate_Two(play_sel, pile_card); //any single card played after this true playing more cards after this is valid
				else if(this_card < pile_card) //Cards less then value then the pile card (that are not special) are not valid
				{
					cout << this_card << " < " << pile_card << endl;
					return false;
				}
				else if(i > 0 && this_card != last_card) //Playing 2 or more cards of different values is not a valid move
				{
					cout << this_card << " != " << last_card << endl;
					return false;
				}
				last_card = play_sel[i].getCardValue(); //update last card for next iteration of loop
			}	
		}	
		return is_valid; //if we get this far its true
	}

	void Player::translateHandView(int offset){
		h.translateView(offset);
	}