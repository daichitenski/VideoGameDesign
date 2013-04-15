#include "headers/Board.h"

	Board::Board(bool m)
	{
		main = m;
		numCards =0;
		topLayer = false;
	}
	void Board::drawFromDeck(Deck *d, bool up){
		Card c = d->drawCard();
		if(up == true)
		{
			topLayer = true;
			c.flipCard();
		}
		boardList.insert(boardList.end(), c);
		numCards++;
		if(up == true)
		{
			sort(boardList.begin(), boardList.end(), compare);
		}

	}
	void Board::insert(vector<Card> inCards){
		boardList.insert(boardList.end(),inCards.begin(),inCards.end());
		numCards += inCards.size();
	}
	void Board::insert(Card newCard){
		boardList.insert(boardList.end(), newCard);
		numCards++;
	}
	void Board::outputHand(){
		cout<<"Outputting Board with "<<numCards<<" cards:"<<endl;
		for(int i=0;i<numCards;i++){
			boardList[i].outputCard();
		}
		cout<<endl;
	}

	void Board::draw(CardImage *c, SDL_Surface *screen, int mine, int turn){
		if(mine == turn){
			if(topLayer == true)
			{
				for(int i=0;i<numCards;i++){
					c->selectCard(boardList[i].getValue());
					c->draw(screen, (48*i)+320, 350);
				}
			}
			else {
				for(int i=0;i<numCards;i++){
					c->selectCard(13);
					c->draw(screen, (48*i)+340, 320);
				}
			}
		}
		else{
			if(topLayer == true)
			{
				for(int i=0;i<numCards;i++){
					c->selectCard(boardList[i].getValue());
					c->draw(screen, (48*i)+320, 80);
				}
			}
			else {
				for(int i=0;i<numCards;i++){
					c->selectCard(13);
					c->draw(screen, (48*i)+340, 50);
				}
			}
		}
	}
	bool Board::isEmpty(){
		return boardList.empty();
	}