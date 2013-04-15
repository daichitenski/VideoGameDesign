#include "headers/Deck.h"

	void Deck::init(int numDecks){
		numCards = numDecks * 52;
		vector<int> cardList;

		//Initialize List of Cards
		int cardAvailable = numCards, val, idx;
		for(int i=0;i<13;i++){
			for(int j=0;j<(numDecks*4);j++){
				cardList.insert(cardList.end(),i);
			}
		}

		//Shuffle the deck
		srand (time(NULL)); 
		for(int i=0;i<numCards;i++){
			if(cardAvailable >1 )
				idx = rand() % (cardAvailable);
			else
				idx = 0;
			val = cardList[idx];
			cardList.erase(cardList.begin()+idx);
			cardAvailable--;
			deckList.push_front(Card(val,false));
		}

		//Delete the cardlist
		vector<int>().swap(cardList);
	}
	void Deck::outputDeck(){
		cout<<"Outputting Deck List"<<endl;
		for(int i=0;i<numCards;i++){
			cout << i << " ";
			deckList[i].outputCard();
		}
	}
	void Deck::draw(CardImage *c, SDL_Surface *screen){
		if(numCards>0)
			c->selectCard(13);
		else
			c->selectCard(14);
		//this is awful, our positions for stuff is all in literal values	
		c->draw(screen,401,165);

		//c->selectCard(0);
		//c->draw(screen,308,165);
	}

	Card Deck::drawCard(){
		Card c;
		if(numCards>0){
			c = deckList.front();
			deckList.pop_front();
			numCards--;
			return c;
		}
		else
			cout << "No cards left in deck" << endl;
			return c; //RM have to return something (fixes compiler warning)
	}
	int Deck::getNumCards(){
		return numCards;
	}