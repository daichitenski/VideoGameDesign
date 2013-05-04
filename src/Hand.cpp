#include "headers/Hand.h"

	Hand::Hand(){ //default constructor
		numCards=0;
		handSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,HAND_WIDTH,HAND_HEIGHT,32,0,0,0,0);
		handSpace.x = 10; handSpace.y = 472; handSpace.h = HAND_HEIGHT; handSpace.w = VIEW_WINDOW_WIDTH;
		viewMin = 0;
	}

	void Hand::drawFromDeck(Deck *d){
		if(d->getNumCards()>0){
			Card c = d->drawCard();
			c.flipCard();
			if(c.isSelected() == true) c.toggleSelected();
			//insert(c);
			handList.insert(handList.end(), c);
			numCards++;
			sortHand();
		}
	}
	void Hand::insert(vector<Card> inCards){
		for(int i=0; i<inCards.size(); i++) if(inCards[i].isSelected() == true) inCards[i].toggleSelected();
		handList.insert(handList.end(),inCards.begin(),inCards.end());
		numCards += inCards.size();
		sort(handList.begin(), handList.end(), compare);
	}
	void Hand::insert(Card newCard){
		if(newCard.isSelected() == true) newCard.toggleSelected();
		handList.insert(handList.end(), newCard);
		numCards++;
		sort(handList.begin(), handList.end(), compare);
	}
	void Hand::sortHand(){
		sort(handList.begin(),handList.end(),compare);
	}
	void Hand::sortHandLH(){
		sort(handList.begin(),handList.end(),compare2);
	}
	void Hand::outputHand(){
		cout<<"Outputting Hand with "<<numCards<<" cards:"<<endl;
		for(int i=0;i<numCards;i++){
			handList[i].outputCard();
		}
		cout<<endl;
		// cout<<"Outputting Hand with "<<handList.size()<<" cards:"<<endl;
		// for(int i=0;i<handList.size();i++){
			// handList[i].outputCard();
		// }
		// cout<<endl;
	}
	void Hand::highlightCard(int idx){
		handList[idx].toggleSelected();
	}
	void Hand::draw(CardImage *c, SDL_Surface *screen){
		SDL_Rect viewWindow;

		//This code fills the hand with transparency
		int colorKey=SDL_MapRGB(screen->format,255,0,255);
		SDL_SetColorKey(handSurface, SDL_SRCCOLORKEY,colorKey);
		SDL_FillRect(handSurface,NULL,SDL_MapRGB(screen->format,255,0,255));


		for(int i=0;i<numCards;i++){
			if(handList[i].isSelected()){
				c->selectCard(handList[i].getValue(),true);
				c->draw(handSurface, (105*i)+10, 1);
			}

			else{
				c->selectCard(handList[i].getValue());
				c->draw(handSurface, (105*i)+10, 0);
			}

		}

		viewWindow.x = viewMin; viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
		SDL_BlitSurface(handSurface, &viewWindow, screen, &handSpace);
	}
	bool Hand::isEmpty(){
		return handList.empty();
	}
	int Hand::getViewMin(){
		return viewMin;
	}
	void Hand::translateView(int offset){
		int temp = offset+viewMin;
		if(temp<0 || (numCards*110 < VIEW_WINDOW_WIDTH)) viewMin = 0;
		else if(temp>((numCards*CARDWIDTH_WITH_OFFSET)-VIEW_WINDOW_WIDTH)) viewMin = (numCards*CARDWIDTH_WITH_OFFSET)-VIEW_WINDOW_WIDTH;
		else{
			viewMin = temp;
		}
	}	
	int Hand::getNumCards(){
		if(numCards>=35){
			outputHand();
		}
		return numCards;//return handList.size();
	}
	vector<Card> Hand::getHand()
	{
		return handList;
	}
	
	int Hand::playHand()
	{
		return 1;
	}
	
	void Hand::remove(vector<Card> inCards){
		for(unsigned int i=0; i<inCards.size(); i++)
			remove(inCards[i]);
	}
	void Hand::remove(Card newCard){
		cout << "REMOVAL of : " << newCard.getValue() << endl;
		unsigned int i = 0, l = handList.size();
		while(l == handList.size() && i < l)//exit either when found or end of hand
		{
			cout << "Card # " << handList[i].getValue() << endl;
			if(handList[i].getValue() == newCard.getValue())
			{
				handList.erase(handList.begin()+i);
			}
			else
				i++;
		}
		numCards = handList.size();
	}