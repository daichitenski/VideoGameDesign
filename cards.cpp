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
const int CARDHEIGHT_SMALL = 48;
const int CARDWIDTH_SMALL = 37;
string SPRITESHEET = "cardfaces.bmp";
string BG_IMAGE = "background.bmp";
string SPRITESHEET_S = "cardfaces_s.bmp";

class CardImage{
	string fname;
	SDL_Surface *cardSheet;
	SDL_Rect src, dest;
	bool small;

public:
	const static int OFFSET = 10;
	const static int OFFSET_SMALL = 3;
	CardImage(string name, SDL_Surface *screen, bool smallCards=false){
		fname=name;
		small = smallCards;
		init(screen);
	}

	CardImage(string name, int val, SDL_Surface *screen, bool smallCards = false){
		fname=name;
		small = smallCards;
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
		if(!small){
			src.x = OFFSET; src.y = OFFSET; src.w = CARDWIDTH; src.h = CARDHEIGHT;
			dest.x =0; dest.y = 0; dest.w = CARDWIDTH; dest.h = CARDHEIGHT;
		}
		else{
			src.x = OFFSET_SMALL; src.y = OFFSET_SMALL; src.w = CARDWIDTH_SMALL; src.h = CARDHEIGHT_SMALL;
			dest.x =0; dest.y = 0; dest.w = CARDWIDTH_SMALL; dest.h = CARDHEIGHT_SMALL;			
		}
	}
	void selectCard(int val){
		if(!small){
			src.x = OFFSET+(OFFSET*val) + CARDWIDTH*val;
			src.y = OFFSET;
		}
		else{
			src.x = OFFSET_SMALL+(OFFSET_SMALL*val) + CARDWIDTH_SMALL*val;
			src.y = OFFSET_SMALL;
		}
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
		if(newVal == 2-1 || newVal == 10-1)
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
			cout << i << " ";
			deckList[i].outputCard();
		}
	}
	void draw(CardImage *c, SDL_Surface *screen){
		c->selectCard(13);
		c->draw(screen,401,165);
		//c->selectCard(0);
		//c->draw(screen,308,165);
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
	static const int HAND_WIDTH = 600;
	static const int VIEW_WINDOW_WIDTH = 650;
	static const int VIEW_WINDOW_STEP = 45;

public:
	Hand(){
		numCards=0;
		handSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,VIEW_WINDOW_WIDTH,HAND_HEIGHT,32,0,0,0,0);
		
		handSpace.x = 10; handSpace.y = 475; handSpace.h = HAND_HEIGHT; handSpace.w = VIEW_WINDOW_WIDTH;
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
		SDL_Rect viewWindow;
		int colorKey=SDL_MapRGB(screen->format,255,0,255);
		SDL_SetColorKey(handSurface, SDL_SRCCOLORKEY,colorKey);
		SDL_FillRect(handSurface,NULL,SDL_MapRGB(screen->format,255,0,255));
		

		for(int i=0;i<numCards;i++){
			c->selectCard(handList[i].getValue());
			c->draw(handSurface, (105*i)+10, 0);
		}
		
		//------ THERE IS A BUG HERE WITH LESS THAN 6 CARDS -------
		// if(viewMin >= 0 && viewMin < ((numCards*110) - VIEW_WINDOW_WIDTH)){
		// 	viewWindow.x = viewMin; viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
		// 	cout<<"case 1: "<<"winx: "<<viewWindow.x<<" winy: "<<viewWindow.y<<" width: "<<viewWindow.w<<" height: "<<viewWindow.h<<endl;
		// }
		// else if(viewMin >=0 && viewMin < VIEW_WINDOW_WIDTH){
		// 	viewWindow.x = viewMin; viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
		// 	cout<<"case 2: "<<"winx: "<<viewWindow.x<<" winy: "<<viewWindow.y<<" width: "<<viewWindow.w<<" height: "<<viewWindow.h<<endl;
		// }
		// else if(viewMin< 0 && viewMin < ((numCards*110) - VIEW_WINDOW_WIDTH)){
		// 	viewWindow.x = 0; viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
		// 	cout<<"case 3: "<<"winx: "<<viewWindow.x<<" winy: "<<viewWindow.y<<" width: "<<viewWindow.w<<" height: "<<viewWindow.h<<endl;
		// }
		// else{
		// 	viewWindow.x = ((numCards*110) - VIEW_WINDOW_WIDTH); viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
		// 	cout<<"case 4: "<<"winx: "<<viewWindow.x<<" winy: "<<viewWindow.y<<" width: "<<viewWindow.w<<" height: "<<viewWindow.h<<endl;
		// }
		viewWindow.x = viewMin; viewWindow.y = 0; viewWindow.w = VIEW_WINDOW_WIDTH; viewWindow.h = HAND_HEIGHT;
		SDL_BlitSurface(handSurface, &viewWindow, screen, &handSpace);
	}
	bool isEmpty(){
		return handList.empty();
	}
	int incrementViewWindow(int prev){
		int answer = 0;
		if(numCards*110 < VIEW_WINDOW_WIDTH)
			answer = 0;
		else if(prev+VIEW_WINDOW_STEP > ((numCards*110) - VIEW_WINDOW_WIDTH))
			answer = ((numCards*110) - VIEW_WINDOW_WIDTH);
		else
			answer = prev+VIEW_WINDOW_STEP;

		cout<<"View Min: "<<answer<<endl;
		return answer;
	}
	int decrementViewWindow(int prev){
		int answer = 0;
		if(prev-VIEW_WINDOW_STEP < 0)
			answer = 0;
		else
			answer = prev-VIEW_WINDOW_STEP;

		cout<<"View Min: "<<answer<<endl;
		return answer;
	}
};

class Board // The Board Hand Class
{
private:
	vector<Card> boardList;
	bool topLayer;
	int numCards;
public:
	Board()
	{
		numCards =0;
		topLayer = false;
	}
	void drawFromDeck(Deck *d, bool up){
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
	void insert(vector<Card> inCards){
		boardList.insert(boardList.end(),inCards.begin(),inCards.end());
		numCards += inCards.size();
	}
	void insert(Card newCard){
		boardList.insert(boardList.end(), newCard);
		numCards++;
	}
	void outputHand(){
		cout<<"Outputting Hand with "<<numCards<<" cards:"<<endl;
		for(int i=0;i<numCards;i++){
			boardList[i].outputCard();
		}
		cout<<endl;
	}

	void draw(CardImage *c, SDL_Surface *screen){
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
	bool isEmpty(){
		return boardList.empty();
	}
};

class Discard{
	deque<Card> discardPile;
	int numCards;

public:
	Discard(Deck *d){
		numCards = 0;
		Card c = d->drawCard();
		c.flipCard();
		discardPile.push_front(c);
		numCards++;

	}
	void outputDiscard(){
		cout<<"Outputting Discard Pile List"<<endl;
		for(int i=0;i<numCards;i++){
			discardPile[i].outputCard();
		}
	}
	void draw(CardImage *c, SDL_Surface *screen){
		//c->selectCard(12);
		//c->draw(screen,401,165);
		Card temp = discardPile.front();
		c->selectCard(temp.getValue());
		c->draw(screen,308,165);
	}
};

class player{
	Hand h; //Hidden Play Hand
	Board upBoard; //Face up Board Hand Section
	Board db; //Face down Board Hand section
	int maxHand; //Number per hand based on deck
	int maxBoard; //Number for board cards based on deck
		
public:
	player(Deck &d, int deckNum=1) //I still have to take into consideration the number of players playing
	{
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
		for(int i=0;i<maxBoard;i++){ //Generates Board Cards
			upBoard.drawFromDeck(&d, true);
			db.drawFromDeck(&d, false);
		}
		cout<<endl;
		h.outputHand();
		cout<<endl;
		upBoard.outputHand();
		cout<<endl;
		db.outputHand();
	}
	// void draw(CardImage *c, SDL_Surface *screen, CardImage cardImages){
		// //Displays both the player's hand and board hand.
		// h.draw(&cardImages,screen);	//player class
		// db.draw(&cardImages, screen);
		// upBoard.draw(&cardImages, screen);
		
	// }
	void drawHand(CardImage *c, SDL_Surface *screen, int winMin){
		h.draw(c,screen,winMin);	//player class
	}
	void drawBoard(CardImage *c, SDL_Surface *screen){
		db.draw(c,screen);
		upBoard.draw(c,screen);
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
	CardImage smallCardImages = CardImage(SPRITESHEET_S, screen, true);
	Deck d = Deck(1);
	d.outputDeck();
	player p1(d);
	Discard discardPile(&d);
	int windowMin = 0;
	
	while(!done){
		bg.draw();
		d.draw(&cardImages,screen);
		discardPile.draw(&cardImages, screen);
//		p1.draw(&cardImages,screen, cardImages);	//player class
		p1.drawHand(&cardImages,screen,windowMin);
		p1.drawBoard(&smallCardImages,screen);
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