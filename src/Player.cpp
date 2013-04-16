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
		h.drawFromDeck(d);
	}
	int Player::getHandViewMin(){
		return h.getViewMin();
	}
	int Player::getNumCardsInHand(){
		return h.getNumCards();
	}
	/*MY_STUFF*/
	bool Player::Is_Lowest(vector<Card> test,int val)
	{
		for(unsigned int i=0; i<test.size(); i++) 
		{
			if(test[i].getValue() == 2); //continue
			else if(test[i].getValue() > val) return false;
		}
		return true;
	}
	
	bool Player::Validate_Two(vector<Card> test)
	{
		int last_card = -1;
		int this_card = -1;
		
		for(unsigned int i=0; i<test.size(); i++)
		{
			this_card = test[i].getValue();
			if(i == 0) last_card = test[1].getValue();
			else
			{
				if(this_card != last_card) return false;
				else if(this_card == last_card)
				{
					if(this_card == 2); //continue
					else if(!Is_Lowest(test, this_card)) return false; //if the card played isn't the lowest card in the deck
				}
				else return false;
			}
			last_card = test[i].getValue();
		}
		return true;
	}
	
	bool Player::isValid_Move(vector<Card> player_hand, Card pile) //returns true if the hand passed in can be played 
	{
		bool is_valid = true;
		unsigned int last_card = -1;
		unsigned int this_card = player_hand[0].getValue();
		unsigned int pile_card = pile.getValue();
		cout << "Valid function test\n";
		if(player_hand.size() == 1)
		{
			if((this_card == 2 || this_card == 10)) is_valid = true; //A single special card is always a valid move
			else if(this_card < pile_card) is_valid = false; //a hand smaller then the value of the deck card is invalid 
		}
		else
		{
			last_card = player_hand[0].getValue(); //save the value of the first card for comparison
			for(unsigned int i=1; i<player_hand.size(); i++)
			{
				this_card = player_hand[i].getValue(); //save the value of first card
				if(this_card == 10) is_valid = true; //killzed it as long as they didn't try to play any other cards
				else if(this_card == 2)
				{
					if(!Validate_Two(player_hand)) return false; //any single card played after this true playing more cards after this is valid
				}
				else if(this_card < pile_card) //Cards greater in value then the card being pile card are not valid
				{
					return false;
				}
				else if(this_card != last_card) //Playing 2 or more cards of different values is not a valid move
				{
					return false;
				}
				last_card = player_hand[i].getValue(); //update last card for next iteration of loop
			}	
		}	
		return is_valid; //if we get this far its true
	}

	void Player::translateHandView(int offset){
		h.translateView(offset);
	}
	void Player::handle_input(SDL_Event &event, bool &done, bool &mouseDown, SlidingCard &sc, Slider &slide, int &handPixelWidth, int &adjustment, Deck &d, Discard &discardPile, int &turn)
	{
			while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				done = true;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				cout<<"Click pos: ("<<event.button.x<<", "<<event.button.y<<")"<<endl;

				if(event.button.x > 401 && event.button.x < 401+CARDHEIGHT && event.button.y > 165 && event.button.y <165+CARDWIDTH && d.getNumCards()>0){
					drawFromDeck(&d);
					sc.reset();
					cout<<"Drawing card from deck"<<endl;
				}
				if(slide.clicked(event.button.x,event.button.y)){
					cout<<"Slider clicked"<<endl;
					mouseDown = true;
				}
				//10,475	625,475
				//10,880	625,880
				if(event.button.x>10 && event.button.x<625 && event.button.y>475 && event.button.y<880){
					cout<<"Hand Area clicked"<<endl;
					int clickPoint = getHandViewMin()+event.button.x;
					cout<<"Point: "<<clickPoint<<" viewMin: "<<getHandViewMin()<<" card number: "<<clickPoint/105<<endl;
					pickCard(clickPoint/105);
				}
				//playcards svp
				if(event.button.x>308 && event.button.x< (308 + CARDWIDTH) && event.button.y > 165 && event.button.y<(165 + CARDHEIGHT ))
				{
					vector<Card> playCards;
					for (int i = 0; i < h.getNumCards();i++)
					{
						if (h.handList[i].isSelected())
						{
							playCards.push_back(h.handList[i]);
							h.remove(h.handList[i]);
							i--;
						}
					}
					if (playCards.size() != 0){ discardPile.layCardPhase(playCards);
					//this line of code doesn't scale to lots of players
					(turn == 0) ? turn = 1: turn = 0;}
				}

			}
			else if(event.type == SDL_MOUSEBUTTONUP){
				if(mouseDown ==true){	
					cout<<"Slider released"<<endl;
					mouseDown = false;
				}

			}
			else if(event.type == SDL_MOUSEMOTION){
				if(mouseDown == true){
					slide.translate(event.motion.xrel);
					handPixelWidth = getNumCardsInHand()*CARDWIDTH_WITH_OFFSET;
					adjustment = (handPixelWidth / slide.MAX_SLIDER)*event.motion.xrel;
					translateHandView(adjustment);

				}
			}
		}
	}