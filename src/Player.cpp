#include "headers/Player.h"

	void Player::buffer_audio()
	{
		//init Audio and allocate memory for it
		bool error = false;
		char *s[]=
		{		//Hard coded for now
				"../sound/Demon_Killzed_It.wav","../sound/Electro_Killzed_It.wav","../sound/Girl_Killzed_It.wav","../sound/Kid_Killzed_It_Echo.wav"
				, "../sound/Kid_Killzed_It_Echo2.wav", "../sound/Kid_Killzed_It_PP.wav", "../sound/Kid_Killzed_It.wav"  
		}; 
		FX->init_audio();
		FX = new sound[NUM_AUDIO_FILES];
		
		//Load audio files
		for(int i=0; i<NUM_AUDIO_FILES; i++)
		{
			if(FX[i].load_fx(s[i]) == false) //loop through and load audio files into ram
			{
				error = true;
				cerr << "Error loading audio \"" << s[i] <<"\"\n";
			}
				if(error) cout << "Audio Succesfully loaded\n";
		}
	}
	
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
		
		//Init sound and load audio into ram
		buffer_audio();
	}
	
	/*
	Player::~Player() //RM why does this break everything?
	{
		for(int i=0; i<NUM_AUDIO_FILES; i++)
		{
			FX[i].clean_up();
		}
	}*/
	
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
	bool Player::isHandEmpty()
	{
		return h.handList.empty();
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
	
	void Player::play_rnd()
	{
		int fx_num = rand() % NUM_AUDIO_FILES; //select a buffered fx randomly
		if(FX[fx_num].play_fx() == false) cerr << "Error playing audio\n"; //play it
	}
	
	bool Player::upBoardIsEmpty(){return upBoard->isEmpty();}
	bool Player::downBoardIsEmpty(){return db->isEmpty();}
	vector<Card> Player::getUpBoard()
	{
		return upBoard->boardList;
	}
	bool Player::Is_Lowest(vector<Card> &test, int val) //returns true if the card passed in is the lowest (non special) in the players hand
	{
		cout << "Is_Lowest\n";
		int min = 9999;
		int this_card = -1;
		//cout << "Is_Lowest val: " << val << "num loops " << test.size() << endl;
		vector<Card> player_hand = h.getHand();
		
		//Save the lowest (non) special value in the players hand. Need to check both arrays as when you select a hand a play is removed from the default hand h.
		for(int i=test.size(); i>=0; --i)  
		{
			this_card = test[i].getCardValue();
			if(this_card < min && this_card != 2 && this_card != 10) min = this_card; //if this card is lower then min (and not 2) then it is the new min
		}
		//Check for remaining cards
		for(int j=player_hand.size(); j>=0; --j)
		{
			this_card = player_hand[j].getCardValue();
			if(this_card < min && this_card != 2 && this_card != 10) min = this_card;
		}
			//cout << "val: " << val << " min: " << min << endl;
			if(val > min)return false;
			return true;
	}
			
	bool Player::Is_Lowest_Beat(vector<Card> &test, int pile_card, int val) //FIX ME
	{ 
		//add functionality for 10
		cout << "Is Lowest Beat\n";
		int min = 9999;
		int this_card = -1;
		vector<Card> player_hand = h.getHand();
		//cout << "Loop 1 size of array: " << test.size() << "initial val " << val << " pile_card " << pile_card << endl;
		for(int i=test.size()-1; i>=0; --i) //count backwards lows are first save work
		{
			this_card = test[i].getCardValue();
			if((this_card < min && this_card >= pile_card) && (this_card > 2 && this_card != 10)) min = this_card; //Get the lowest (non two) value in the players hand that beats the value passed into it
			//cout << "this_card " << this_card << " comparing with " << pile_card << " min is " << min << endl;
		}
		//cout << "Loop 2 size of array: " << player_hand.size() << endl;
		for(int j=player_hand.size()-1; j>=0; --j)
		{
			this_card = player_hand[j].getCardValue();
			if((this_card < min && this_card >= pile_card) && (this_card > 2 && this_card != 10)) min = this_card; //Get the lowest (non two) value in the players hand that beats the value
			//cout << "this_card " << this_card << " comparing with " << pile_card << " min is " << min << endl;
		}
		//cout << "min: " << min << " val: " << val << endl;
		if(val == min)
		{
			cout << val << " is lowest beat of " << pile_card << endl;
			return true;
		}
		return false;
	}
			
		bool Player::Is_Last(int val, int pile_card) //return true if the player can make no other moves then the value passed into the function
		{
			cout << "Is_Last\n";
			vector<Card> player_hand = h.getHand(); //Get the players hand
			for(unsigned int i=0; i<player_hand.size(); i++)
			{
				//if(player_hand[i].getCardValue() == 10) return false; //10s are always playable, however we want to give the player the choice to play the 2 or 10
				if(player_hand[i].getCardValue() < val)
				{
					if(player_hand[i].getCardValue() != 2) return false; //there is another valid move
				}
			}
			return true;
		}
		
		bool Player::Validate_Two(vector<Card> &test, int pile_card) //finish me to check that any other cards played are the lowest in players hand
		{
			cout << "Validate 2\n";
			int last_card = -1;
			int this_card = test[0].getCardValue();
			
			cout << "Comparing " << this_card << " to " << pile_card << endl;
			
			if(test.size() == 1) //if they just played a single 2 and they have no other valid moves
			{
				if(Is_Last(this_card, pile_card)) return true;
				else return false;
			}
			else
			{
				//Invalid conditions 2 cards other then 2, A card after 2 that is not the lowest beat, multiple 2s if there is a lowest beat other then 2 
				//Valid conditions, multiple of the same lowest beat after a two, Multiple 2's if there is no lowest beat, a 2 and the lowest beat, a single 2 if there is no lowest beat
				last_card = test[test.size()-1].getCardValue(); //set last card to the first card in the hand
				if(!(last_card == 2)) return false; //if the first card isn't a 2 then this isn't a valid 2 play
				cout << "Before for loop\n";
				for(unsigned int i=1; i<test.size()-1; i++)
				{	
					this_card = test[i].getCardValue();
					cout << "this card " << this_card << endl;
					if(this_card == 2 && last_card == 2)
					{
						if(!(Is_Last(this_card, 2))) return false; //if this isn't the only move we can make return false;
					}
					else if(this_card > 2) //if there is another card
					{
						if(!(Is_Lowest(test, this_card))) return false;	//... the non two card the lowest this move is invalid 
					}
					last_card = test[i].getCardValue(); //save the value of the card for later comparison
				}
			}
			//cout << "Validate two is true\n";
			return true;
		}
			
	bool Player::Validate_Ten(vector<Card> &test) //Plays "Killzed It" FX when returning true
	{
		int this_card = 0;
		if(test.size() < 1) return false;
		if(test.size() == 1)
		{
			play_rnd();
			return true;
		}
		else 
		{
			for(int i=test.size()-1; i>=0; --i)
			{
				this_card = test[i].getCardValue();
				if(this_card != 10) return false;
				play_rnd();
			}
			return true;
		}
		return false; //catch all
	}
	
	bool Player::isValid_Move(vector<Card> &play_sel, int pile_card, bool playFromHand) //returns true if the hand passed in can be played 
	{ 
		//not calling validate two when it should when playing multiple cards
		bool is_valid = false;
		unsigned int last_card = -1;
		unsigned int this_card = play_sel[0].getCardValue();
		cout << "this_card initialized to " << this_card << endl;
		vector<Card> player_hand = h.getHand();
				
		if(play_sel.size() < 1) return true;
		//cout << "First card played " << this_card << " card on pile " << pile_card << " First card selected " << endl;
		if(play_sel.size() == 1) //player is trying to play a single card
		{
			cout << "single testing\n";
			if((this_card == 10)) return Validate_Ten(play_sel); //A single 10 is always valid
			else if(this_card == 2) return Validate_Two(play_sel, pile_card); //Christina: 2 is only valid by itself if it is the last card the player can play
			else if(this_card < pile_card) 
			{
				cout << "Comparing " << this_card << " with " << pile_card << endl;
				return false; //a hand smaller then the value of the deck card is invalid
			}
			if(this_card > pile_card) 
			{
				cout << "Comparing " << this_card << " with " << pile_card << endl;
				if(!Is_Lowest_Beat(play_sel, pile_card, this_card)) return false;
				return true;
			}
			else return true; //catch all
		}
		else //player is trying to play more then one card
		{
			cout << "Testing full hand\n";
			last_card = play_sel[0].getCardValue(); //store the last card once before the loop to prevent error
			cout << "size of loop " << play_sel.size() << endl;
			for(unsigned int j=play_sel.size()-1; j>0; --j)
			{
				this_card = play_sel[j].getCardValue();
				cout << "Updating this card to " << this_card << " index " << j << endl;
				if(this_card == 2) return Validate_Two(play_sel, pile_card);
				else if(this_card == 10) return Validate_Ten(play_sel); //Do Nothing //killzed it as long as they didn't try to play any other cards
				else if(this_card < pile_card) //Cards less then value then the pile card (that are not special) are not valid
				{
					cout << this_card << " < " << pile_card << endl;
					return false;
				}
				else if(j > 0 && this_card != last_card) //Playing 2 or more cards of different values is not a valid move
				{
					cout << this_card << " != " << last_card << endl;
					return false;
				}
				else if(this_card > pile_card) 
				{
					if(!Is_Lowest_Beat(play_sel, pile_card, this_card)) return false;
					cout << "returned true \n";
					//is_valid = true; otherwise continue testing
				}
			last_card = play_sel[j].getCardValue(); //update last card for next iteration of loop
			}
			cout << "Done\n";	
		}	
		return true; //if we get this far its true		
	}

	void Player::translateHandView(int offset){
		h.translateView(offset);
	}