#include "SDL/SDL.h"
#include <iostream>
#include <string>
#include <deque>
#include <time.h>
#include <vector>

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

public:
	Card(){
		value = 0;
		faceUp = false;
	}
	Card(int newVal, bool facing){
		value = newVal;
		//image = newImage;
		faceUp = facing;
	}
	int getValue(){
		return value;
	}
	void flipCard(){
		faceUp = !faceUp;
	}
	void setFacing(bool newFacing){
		faceUp = newFacing;
	}
	void outputCard(){
		cout<<"Value: "<<value;
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
		c->selectCard(12);
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

class Hand{
	vector<Card> handList;
	int numCards;
	static const int HAND_HEIGHT = 140;
	static const int HAND_WIDTH = 120;

public:
	Hand(){
		numCards=0;
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
	}
	void insert(Card newCard){
		handList.insert(handList.end(), newCard);
		numCards++;
	}
	void outputHand(){
		cout<<"Outputting Hand with "<<numCards<<" cards:"<<endl;
		for(int i=0;i<numCards;i++){
			handList[i].outputCard();
		}
		cout<<endl;
	}

	void draw(CardImage *c, SDL_Surface *screen){
		for(int i=0;i<numCards;i++){
			c->selectCard(handList[i].getValue());
			c->draw(screen, (105*i)+10, 476);
		}
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
	Hand h = Hand();

	for(int i=0;i<5;i++){
		h.drawFromDeck(&d);
	}
	cout<<endl;
	h.outputHand();
	
	while(!done){
		bg.draw();
		d.draw(&cardImages,screen);
		h.draw(&cardImages,screen);	
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				done = true;
			}
		}
		SDL_Flip(screen);
	}
	SDL_Quit();
	return 0;
}