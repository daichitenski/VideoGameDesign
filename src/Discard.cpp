#include "headers/Discard.h"

void Discard::init(Deck *d){
		numCards = 0;
		numConsecative = 0;
		Card c = d->drawCard();
		c.flipCard();
		discardPile.push_front(c);
		cout << "start value" << c.getValue();
		if (c.getValue() == 10-1) killDiscard();
		numCards++;
		numConsecative++;
		killed = false;
		
	}
	void Discard::outputDiscard(){
		cout<<"Outputting Discard Pile List"<<endl;
		for(int i=0;i<numCards;i++){
			discardPile[i].outputCard();
		}
	}
	void Discard::draw(CardImage *c, SDL_Surface *screen){
		if( killed == false)
		{
			Card temp = discardPile.front();
			c->selectCard(temp.getValue());
			c->draw(screen,308,165);
		}
	}
	void Discard::killDiscard(){
		killed == true; //RM because nothing should be displayed for the pile
		numConsecative = 0;
		numCards = 0;
		discardPile.clear(); //Clears the que by destroying every member
	}
	int Discard::getTopCardValue(){
		if(!discardPile.empty())
		{
			Card c;
			c = discardPile.front();
			return c.getCardValue();
		}
		else
		{
			return 1; //because this is "2" and any value can be played on a 2
		}
	}
	void Discard::layCardPhase(const vector<Card> &playCards, int numDecks){//Vector needs to be in the order of first card to play in the front ie) 2, 3, 3 to play the 2 before the 3's
		if(playCards.size() == 1)//if one card what card is it
			if(playCards[0].getValue() != 9)//If the card is the special Card 10
				if(killed == false)
					if(playCards[0].getValue() == getTopCardValue()){
						numConsecative++;
						discardPile.push_front(playCards[0]);
						numCards++;
					}
					else{//Expected check that for == values or greater values
						discardPile.push_front(playCards[0]);
						numCards++;
						numConsecative =0;
					}
				else{
					discardPile.push_front(playCards[0]);
					numCards++;
					numConsecative++;
					killed = false;
				}
			else
				killDiscard();
		else //if multiple cards (assuming valid cards from selection)
			if(playCards[0].getValue() != 9)//If the card is the special Card 10
				if(killed == false)
					if(playCards[0].getValue() == getTopCardValue()){//All vector values need to be the same
						for(unsigned int i=0; i<playCards.size(); i++)
						{
							numConsecative++;
							discardPile.insert(discardPile.begin(), playCards[i]);
							numCards++;
						}
					}
					else if(playCards[0].getValue() == 1){
						numConsecative =0;
						discardPile.insert(discardPile.begin(), playCards[0]);
						for(unsigned int i=1; i<playCards.size(); i++)
						{
							numConsecative++;
							discardPile.insert(discardPile.begin(), playCards[i]);
							numCards++;
						}
					}
					else{  //Needs check that all are same value or greater than
						numConsecative =0;
						for(unsigned int i=0; i<playCards.size(); i++)
						{
							numConsecative++;
							discardPile.insert(discardPile.begin(), playCards[i]);
							numCards++;
						}
					}
				else{
					numConsecative =0;
					for(unsigned int i=0; i<playCards.size(); i++)
					{
						numConsecative++;
						discardPile.insert(discardPile.begin(), playCards[i]);
						numCards++;
					}
					killed = false;
				}
			else
				killDiscard();
		if(numConsecative >= 4*numDecks) 
			killDiscard();
		if(discardPile.size() >= 1) killed = false;
		else killed = true;
	}