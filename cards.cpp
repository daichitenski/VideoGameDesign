#include "SDL/SDL.h"
#include <iostream>
#include <string>
#include <deque>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

const int SCREENWIDTH = 800;
const int SCREENHEIGHT= 600;
const int CARDHEIGHT = 120;
const int CARDWIDTH = 90;
string SPRITESHEET = "cardfaces.bmp";
string BG_IMAGE = "background.bmp";
string BACK_IMAGE = "cardback.bmp";

class CardImage{
	string fname;
	SDL_Surface *cardSheet;
	SDL_Rect src, dest;

public:
	const static int OFFSET = 10;
	CardImage(string name, SDL_Surface *screen){
		fname=name;
		init(screen);
	}

	CardImage(string name, int val, SDL_Surface *screen){
		fname=name;
		init(screen);
		selectCard(val);
	}

	void init(SDL_Surface *screen){
		SDL_Surface *image;
		int colorKey;
		image = SDL_LoadBMP(fname.c_str());
		cardSheet = SDL_ConvertSurface(image,screen->format, SDL_HWSURFACE);
		colorKey=SDL_MapRGB(screen->format,255,0,255);
		SDL_SetColorKey(cardSheet, SDL_SRCCOLORKEY,colorKey);
		
		SDL_FreeSurface(image);
		
		src.x = OFFSET; src.y = OFFSET; src.w = CARDWIDTH; src.h = CARDHEIGHT;
		dest.x =0; dest.y = 0; dest.w = CARDWIDTH; dest.h = CARDHEIGHT;
	}
	void selectCard(int val){
		src.x = OFFSET+(OFFSET*val) + CARDWIDTH*val;
		src.y = OFFSET;
	}
	void draw(SDL_Surface *s, int x, int y){
		dest.x = x; dest.y = y;
		SDL_BlitSurface(cardSheet,&src,s,&dest);
	}

};

class BackgroundImage{
	SDL_Surface *bg, *screen;
	SDL_Rect src;
	string fname;
public:
	BackgroundImage(string name, SDL_Surface *s){
		fname = name;
		screen = s;
		init();
	}
	void init(){
		bg = SDL_LoadBMP(fname.c_str());
		src.x = 0; src.y = 0; src.w = SCREENWIDTH; src.h = SCREENHEIGHT;
	}
	void draw(){
		SDL_BlitSurface(bg, &src, screen, &src);
	}
	
};

class Card{
	int value;
	bool faceUp;
	bool special;

public:
	Card(){
		value = 0;
		special = false;
		faceUp = false;
	}
	Card(int newVal, bool facing){
		value = newVal;
		if(newVal == 2 || newVal ==10)
			special = true;
		else
			special = false;
		//image = newImage;
		faceUp = facing;
	}
	int getValue(){
		return value;
	}
	bool isSpecial()
	{
		return special;
	}
	void flipCard(){
		faceUp = !faceUp;
	}
	void setFacing(bool newFacing){
		faceUp = newFacing;
	}
	void outputCard(){
		cout<<"Value: "<<value;
		cout<<" Special: " << special;
		if(faceUp)
			cout<<"  Face Up"<<endl;
		else
			cout<<"  Face Down"<<endl;
	}
};

class Deck{
	deque<Card> deckList;
	int numCards;

public:
	Deck(int numDecks){
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
				idx = rand() % (cardAvailable-1);
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
	void outputDeck(){
		cout<<"Outputting Deck List"<<endl;
		for(int i=0;i<numCards;i++){
			deckList[i].outputCard();
		}
	}
	void draw(CardImage *c, SDL_Surface *screen){
		c->selectCard(13);
		c->draw(screen,401,165);
		c->selectCard(0);
		c->draw(screen,308,165);
	}

	Card drawCard(){
		Card c = deckList.front();
		deckList.pop_front();
		numCards--;
		return c;
	}
};

bool compare(Card a, Card b)
{
	int tempa = a.getValue();
	int tempb = b.getValue();
	if(tempa == 0) tempa = 14;
	if(tempb == 0) tempb = 14;
	
	return (tempa > tempb);
}
class Hand{
	vector<Card> handList;
	int numCards;
	SDL_Surface *handSurface;
	SDL_Rect handSpace;
	static const int HAND_HEIGHT = 140;
	static const int HAND_WIDTH = 5000;
	static const int VIEW_WINDOW_WIDTH = 700;
	static const int VIEW_WINDOW_STEP = 45;

public:
	Hand(){
		numCards=0;
		handSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,HAND_WIDTH,HAND_HEIGHT,32,0,0,0,0);
		handSpace.x = 0; handSpace.y = 475; handSpace.h = HAND_HEIGHT; handSpace.w = VIEW_WINDOW_WIDTH;
	}

	void drawFromDeck(Deck *d){
		Card c = d->drawCard();
		c.flipCard();
		handList.insert(handList.end(), c);
		numCards++;
		
	}
	void insert(vector<Card> inCards){
		handList.insert(handList.end(),inCards.begin(),inCards.end());
		numCards += inCards.size();
		sort(handList.begin(), handList.end(), compare);
	}
	void insert(Card newCard){
		handList.insert(handList.end(), newCard);
		numCards++;
		sort(handList.begin(), handList.end(), compare);
	}
	void outputHand(){
		cout<<"Outputting Hand with "<<numCards<<" cards:"<<endl;
		for(int i=0;i<numCards;i++){
			handList[i].outputCard();
		}
		cout<<endl;
	}

	void draw(CardImage *c, SDL_Surface *screen, int viewMin){
		// for(int i=0;i<numCards;i++){
		// 	c->selectCard(handList[i].getValue());
		// 	c->draw(screen, (105*i)+10, 476);
		// }
		SDL_Rect viewWindow;
		for(int i=0;i<numCards;i++){
			c->selectCard(handList[i].getValue());
			c->draw(handSurface, (105*i)+10, 0);
		}
		cout<<"View MIN : "<<viewMin<<"  numcards: "<<numCards<<" numCards*110 = "<<(numCards*110)<<endl;
		//THERE IS A BUG HERE WITH LESS THAN 6 CARDS
		if(viewMin >= 0 && viewMin < ((numCards*110) - VIEW_WINDOW_WIDTH)){
			viewWindow.x = viewMin; viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
			cout<<"In case 1"<<endl;
		}
		else if(viewMin >=0 && viewMin < VIEW_WINDOW_WIDTH){
			viewWindow.x = viewMin; viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
			cout<<"In case 2"<<endl;
		}
		else if(viewMin< 0 && viewMin < ((numCards*110) - VIEW_WINDOW_WIDTH)){
			viewWindow.x = 0; viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
			cout<<"In case 3"<<endl;
		}
		else{
			viewWindow.x = ((numCards*110) - VIEW_WINDOW_WIDTH); viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
			cout<<"In case 4"<<endl;
		}

		SDL_BlitSurface(handSurface, &viewWindow, screen, &handSpace);
	}
	bool isEmpty(){
		return handList.empty();
	}
	int incrementViewWindow(int prev){
		int answer = 0;
		if(numCards*110 < VIEW_WINDOW_WIDTH)
			answer = prev;
		else if(prev+VIEW_WINDOW_STEP > ((numCards*110) - VIEW_WINDOW_WIDTH))
			answer = ((numCards*110) - VIEW_WINDOW_WIDTH);
		else
			answer = prev+VIEW_WINDOW_STEP;
		return answer;
	}
	int decrementViewWindow(int prev){
		int answer = 0;
		if(prev-VIEW_WINDOW_STEP < 0)
			answer = 0;
		else
			answer = prev-VIEW_WINDOW_STEP;
		return answer;
	}
};

class player{
	Hand h;
	int maxHand;
	//board hand
		
public:
	player(Deck *d, int deckNum=1)
	{
		switch (deckNum) //Determine the number of cards to deal
		{
		case 1:
		case 2: 
			maxHand = 5;
			for(int i=0;i<maxHand;i++){
				h.drawFromDeck(d);
			}
			break;
		case 3:
		case 4:
			maxHand = 7;
			for(int i=0;i<maxHand;i++){
				h.drawFromDeck(d);
			}
			break;
		case 5:
		case 6:
			maxHand = 13;
			for(int i=0;i<maxHand;i++){
				h.drawFromDeck(d);
			}
			break;
		default:
			maxHand = 6;
			for(int i=0;i<maxHand;i++){
				h.drawFromDeck(d);
			}
			break;
		}
		cout<<endl;
		h.outputHand();
	}
	void drawHand(CardImage *c, SDL_Surface *screen, int winMin){
		h.draw(c,screen,winMin);	//player class
	}
	int decHandWindow(int windowMin){
		return h.decrementViewWindow(windowMin);
	}
	int incHandWindow(int windowMin){
		return h.incrementViewWindow(windowMin);
	}
	void drawFromDeck(Deck *d){
		h.drawFromDeck(d);
	}
};

int main(int argc, char* argv[]){
	SDL_Event event;
	SDL_Surface *screen;
	bool done = false;

	SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT,16,
								SDL_ANYFORMAT|
								SDL_HWSURFACE|
								SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Lucky Bee", NULL);
	BackgroundImage bg = BackgroundImage(BG_IMAGE, screen);
	CardImage cardImages = CardImage(SPRITESHEET,screen);
	
	Deck d = Deck(1);
	d.outputDeck();

	//Player 1
		//Hand h = Hand();
		//for(int i=0;i<5;i++){
		//	h.drawFromDeck(&d);
		//}
		//cout<<endl;
		//h.outputHand();
	player p1(&d);
	int windowMin = 0;

	while(!done){
		bg.draw();
		d.draw(&cardImages,screen);
		//h.draw(&cardImages,screen,windowMin);	//player class
		p1.drawHand(&cardImages,screen,windowMin);
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				done = true;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				cout<<"Click pos: ("<<event.button.x<<", "<<event.button.y<<")"<<endl;
				if(event.button.y > 400 && event.button.x <60 && event.button.y < 475 && event.button.x > 0){
					windowMin=p1.decHandWindow(windowMin);
					cout<<"Moving hand window to the left"<<endl;
				}
				else if(event.button.y > 400 && event.button.x <800 && event.button.y < 475 && event.button.x > 710){
					windowMin=p1.incHandWindow(windowMin);
					cout<<"Moving hand window to the right"<<endl;
				}
				else if(event.button.x > 401 && event.button.x < 401+CARDHEIGHT && event.button.y > 165 && event.button.y <165+CARDWIDTH){
					p1.drawFromDeck(&d);
					cout<<"Drawing card from deck"<<endl;
				}
			}
		}
		SDL_Flip(screen);
	}
	SDL_Quit();
	return 0;
}