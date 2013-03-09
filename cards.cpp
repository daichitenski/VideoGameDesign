#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <iostream>
#include <sstream>
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
const int CARDWIDTH_WITH_OFFSET = 110;
const int CARDHEIGHT_SMALL = 48;
const int CARDWIDTH_SMALL = 37;
string SPRITESHEET = "cardfaces.bmp";
string BG_IMAGE = "background.bmp";
string SPRITESHEET_S = "cardfaces_s.bmp";
const int CARDSHEET_WIDTH = 564;


//Image Classes
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
	void selectCard(int val, bool selected=false, bool flipped = false){
		if(!small){
			if(!selected){
				src.x = OFFSET+(OFFSET*val) + CARDWIDTH*val;
				src.y = OFFSET;
			}
			else{
				src.x = OFFSET+1+(OFFSET*val) + CARDWIDTH*val;
				src.y = (OFFSET*3)+CARDHEIGHT;
			}
		}
		else{
			if(!flipped){
				src.x = OFFSET_SMALL+(OFFSET_SMALL*val) + CARDWIDTH_SMALL*val;
				src.y = OFFSET_SMALL;
			}
			else{
				int temp = OFFSET_SMALL+(OFFSET_SMALL*(val+1))+CARDWIDTH_SMALL*(val+1);
				src.x = CARDSHEET_WIDTH - temp;
				src.y = (4*OFFSET_SMALL)+CARDHEIGHT_SMALL;	
			}
		}
	}
	void draw(SDL_Surface *s, int x, int y){
		dest.x = x; dest.y = y;
		SDL_BlitSurface(cardSheet,&src,s,&dest);
	}

};

class TextImage{
	TTF_Font *font;
	SDL_Surface *imgTxt;
	SDL_Rect txtWindow;
	SDL_Color txtColor;
	string fontName;

public:
	TextImage(string fName, int size){
		TTF_Init();
		fontName = fName;
		font = TTF_OpenFont(fontName.c_str(),size);
		txtColor.r=txtColor.g=220;
		txtColor.b=120;
	}
	void setSize(int size){
		font = TTF_OpenFont(fontName.c_str(),size);
	}
	void setColor(SDL_Color fColor){
		txtColor = fColor;
	}
	void setColor(int r, int g, int b){
		txtColor.r = r;
		txtColor.g = g;
		txtColor.b = b;
	}
	void setText(string t){
		imgTxt = TTF_RenderText_Solid(font,t.c_str(),txtColor);
	}
	void draw(SDL_Surface *screen, int x, int y){
		txtWindow.x = x;
		txtWindow.y = y;
		SDL_BlitSurface(imgTxt,NULL,screen,&txtWindow);
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



//Card Structures
class Card{
	int value;
	bool faceUp;
	bool special;
	bool selected;

public:
	Card(){
		value = 0;
		special = false;
		faceUp = false;
		selected = false;
	}
	Card(int newVal, bool facing){
		value = newVal;
		if(newVal == 2-1 || newVal == 10-1)
			special = true;
		else
			special = false;
		//image = newImage;
		faceUp = facing;
		selected=false;
	}
	int getValue(){
		return value;
	}
	bool isSpecial()
	{
		return special;
	}
	bool isSelected(){
		return selected;
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
	void toggleSelected(){
		selected = !selected;
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
	void outputDeck(){
		cout<<"Outputting Deck List"<<endl;
		for(int i=0;i<numCards;i++){
			cout << i << " ";
			deckList[i].outputCard();
		}
	}
	void draw(CardImage *c, SDL_Surface *screen){
		if(numCards>0)
			c->selectCard(13);
		else
			c->selectCard(14);
		c->draw(screen,401,165);

		//c->selectCard(0);
		//c->draw(screen,308,165);
	}

	Card drawCard(){
		if(numCards>0){
			Card c = deckList.front();
			deckList.pop_front();
			numCards--;
			return c;
		}
		else
			cout<<"No cards left in deck"<<endl;
	}
	int getNumCards(){
		return numCards;
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
	int numCards, viewMin;
	SDL_Surface *handSurface;
	SDL_Rect handSpace;
	static const int HAND_HEIGHT = 140;
	static const int HAND_WIDTH = 4000;
	static const int VIEW_WINDOW_WIDTH = 630;
	static const int VIEW_WINDOW_STEP = 45;
public:
	Hand(){
		numCards=0;
		handSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,HAND_WIDTH,HAND_HEIGHT,32,0,0,0,0);
		handSpace.x = 10; handSpace.y = 472; handSpace.h = HAND_HEIGHT; handSpace.w = VIEW_WINDOW_WIDTH;
		viewMin = 0;
	}
	void drawFromDeck(Deck *d){
		if(d->getNumCards()>0){
			Card c = d->drawCard();
			c.flipCard();
			//insert(c);
			handList.insert(handList.end(), c);
			numCards++;
			sortHand();
		}
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
	void sortHand(){
		sort(handList.begin(),handList.end(),compare);
	}
	void outputHand(){
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
	void highlightCard(int idx){
		handList[idx].toggleSelected();
	}
	void draw(CardImage *c, SDL_Surface *screen){
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
	bool isEmpty(){
		return handList.empty();
	}
	int getViewMin(){
		return viewMin;
	}
	void translateView(int offset){
		int temp = offset+viewMin;
		if(temp<0 || (numCards*110 < VIEW_WINDOW_WIDTH)) viewMin = 0;
		else if(temp>((numCards*CARDWIDTH_WITH_OFFSET)-VIEW_WINDOW_WIDTH)) viewMin = (numCards*CARDWIDTH_WITH_OFFSET)-VIEW_WINDOW_WIDTH;
		else{
			viewMin = temp;
		}
	}	
	int getNumCards(){
		if(numCards>=35){
			outputHand();
		}
		return numCards;
	}
	void remove(vector<Card> inCards)
	{
		for(int i=0; i<inCards.size(); i++)
			remove(inCards[i]);
	}
	void remove(Card newCard)
	{
		cout << "REMOVAL of : " << newCard.getValue() << endl;
		int i = 0, l = handList.size();
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
};

class Board // The Board Hand Class
{
private:
	vector<Card> boardList;
	bool topLayer, main;
	int numCards;

public:
	Board(bool m)
	{
		main = m;
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
		cout<<"Outputting Board with "<<numCards<<" cards:"<<endl;
		for(int i=0;i<numCards;i++){
			boardList[i].outputCard();
		}
		cout<<endl;
	}

	void draw(CardImage *c, SDL_Surface *screen){
		if(main){
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
	bool isEmpty(){
		return boardList.empty();
	}
};


//UI Classes
class UIElement{
public:
	bool clicked(int x, int y){

	}
	bool draw(){

	}
	void execute(){

	}
};

class Slider : public UIElement {
private:
	int xpos;
	bool active;
	SDL_Rect src, dest;
	SDL_Surface *buttonSheet;
public:
	static const int SLIDER_WIDTH = 84;
	static const int SLIDER_HEIGHT = 37;
	static const int SLIDER_YPOS = 430;
	static const int MAX_SLIDER = 570;
	static const int OFFSET = 5;

	Slider(SDL_Surface *screen){
		xpos=0;
		active=true;

		SDL_Surface *image;
		int colorKey;
		image = SDL_LoadBMP("buttons.bmp");
		buttonSheet = SDL_ConvertSurface(image,screen->format, SDL_HWSURFACE);
		colorKey=SDL_MapRGB(screen->format,255,0,255);
		SDL_SetColorKey(buttonSheet, SDL_SRCCOLORKEY,colorKey);
		
		SDL_FreeSurface(image);

		//row in the sprite sheet
		src.y=120;
		if(active)
			src.x=OFFSET;
		else
			src.x=(OFFSET*2)+SLIDER_WIDTH;

		src.h=SLIDER_HEIGHT; src.w=SLIDER_WIDTH;
		dest.x = xpos; dest.y=SLIDER_YPOS; dest.h=SLIDER_HEIGHT; dest.w=SLIDER_WIDTH;

	}

	bool clicked(int x, int y){
		bool answer= false;
		if(active){
			if(x>=xpos+40 && x<xpos+40+SLIDER_WIDTH && y>SLIDER_YPOS && y<SLIDER_YPOS+SLIDER_HEIGHT)
				answer= true;
		}
		return answer;
	}
	void translate(int xOffset){
		xpos+=xOffset;
		if(xpos < 0) xpos=0;
		if(xpos > (MAX_SLIDER-SLIDER_WIDTH)) xpos=(MAX_SLIDER-SLIDER_WIDTH);
	}
	void draw(SDL_Surface *s, int x){
		dest.x=x;
		SDL_BlitSurface(buttonSheet,&src,s,&dest);
	}
	void draw(SDL_Surface *s){
		dest.x = xpos + 40;
		SDL_BlitSurface(buttonSheet,&src,s,&dest);	
	}
	void execute(){
		cout<<"Slider clicked"<<endl;
	}
	int getX(){
		return xpos;
	}
};

class Button: public UIElement{

	//680x530
private:
	int xpos, ypos, w, h;
	bool active;
	SDL_Surface *buttonSheet;
	SDL_Rect src, dest;

public:
	static const int BUTTON_WIDTH = 105;
	static const int BUTTON_HEIGHT = 55;
	static const int Y_OFFSET = 2;
	static const int X_OFFSET = 4;
	Button(SDL_Surface *screen, int inx, int iny, int inw, int inh, bool newactive, int row){
		xpos = inx;
		ypos = iny;
		w = inw;
		h = inh;
		active=newactive;

		SDL_Surface *image;
		int colorKey;
		image = SDL_LoadBMP("buttons.bmp");
		buttonSheet = SDL_ConvertSurface(image,screen->format, SDL_HWSURFACE);
		colorKey=SDL_MapRGB(screen->format,255,0,255);
		SDL_SetColorKey(buttonSheet, SDL_SRCCOLORKEY,colorKey);
		
		SDL_FreeSurface(image);
		
		if(row==0 || row==1)
			src.y = BUTTON_HEIGHT*row+2+Y_OFFSET*row;
		else
			src.y=2;
		if(active)
			src.x = 1;
		else
			src.x = 1+X_OFFSET+BUTTON_WIDTH;
		src.w = BUTTON_WIDTH; src.h = BUTTON_HEIGHT;
		dest.x = xpos; dest.y =ypos; dest.w = w; dest.h = h;				
	}
	void draw(SDL_Surface *s){
		SDL_BlitSurface(buttonSheet,&src,s,&dest);
	}
	int getXPos(){
		return xpos;
	}
	int getYPos(){
		return ypos;
	}
	int getW(){
		return w;
	}
	int getH(){
		return h;
	}
	bool getActive(){

	}
	void switchActive(){
		active = !active;
		if(active)
			src.x=1;
		else
			src.x = 1+X_OFFSET+BUTTON_WIDTH;
	}
	bool clicked(int clickX, int clickY){
		bool answer=false;
		if(active)
			if(clickX>xpos && clickX<xpos+w && clickY>ypos && clickY<ypos+h)
				answer=true;

		return answer;
	}
	void execute(){
		cout<<"Button clicked"<<endl;
	}
};


//Animation Classes
class SlidingCard{
	double x, y, xvel, yvel;
	bool done;
	long last;
public:
	SlidingCard(double xv, double yv){
		x=401;
		y=165;
		xvel=xv;
		yvel=yv;
		done = true;
	}
	void setSpeeds(double xv, double yv){
		xvel=xv;
		yvel=yv;	
	}
	void update(){
		long next = SDL_GetTicks();
		float deltaT = (float)(next-last);
		last=next;
		if(!done){
			x+=xvel/deltaT;
			y+=yvel/deltaT;
		}
		if(x<(-CARDWIDTH) || x>800 || y<(-CARDHEIGHT) || y>600){
			done=true;
		}
	}
	void reset(){
		x=401;
		y=165;
		done=false;
		last = SDL_GetTicks();
	}
	void draw(CardImage *c, SDL_Surface *screen){
		if(!done){
			c->selectCard(13);
			c->draw(screen,x,y);
		}
	}
};


//Player Class
class Player{
	Hand h; //Hidden Play Hand
	/* I made these pointers for constructor purposes. I couldn't get it to work otherwise.
	   We might have to be careful about cleaning up the Boards if we start deleting players. */

	Board *upBoard; //Face up Board Hand Section
	Board *db; //Face down Board Hand section 
	int maxHand; //Number per hand based on deck
	int maxBoard; //Number for board cards based on deck
	bool main; // True if this is player 1
		
public:
	Player(Deck &d, bool mainPlayer, int deckNum=1) //I still have to take into consideration the number of players playing
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
	void drawHand(CardImage *c, SDL_Surface *screen){
		h.draw(c,screen);
	}
	void drawBoard(CardImage *c, SDL_Surface *screen){
		db->draw(c,screen);
		upBoard->draw(c,screen);
	}
	void draw(CardImage *cards, CardImage *smallCards, SDL_Surface *screen){
		if(main){
			h.draw(cards,screen);	
		}
		db->draw(smallCards,screen);
		upBoard->draw(smallCards,screen);
		
	}
	void pickCard(int idx){
		h.highlightCard(idx);
	}
	void drawFromDeck(Deck *d){
		h.drawFromDeck(d);
	}
	int getHandViewMin(){
		return h.getViewMin();
	}
	int getNumCardsInHand(){
		return h.getNumCards();
	}
	void translateHandView(int offset){
		h.translateView(offset);
	}
	// void play(Deck &d, Discard &dis)
	// {
	// }
};
// class Computer:public Player
// {
// private:
	// Hand h; //Hidden Play Hand
	// Board *upBoard; //Face up Board Hand Section
	// Board *db; //Face down Board Hand section 
	// int maxHand; //Number per hand based on deck
	// int maxBoard; //Number for board cards based on deck
	// bool main; // True if this is player 1
	
// public:
	// Computer(Deck &d, int deckNum=1)
	// {
		// Player::Player(d, false, deckNum);
	// }
	// void play(Deck &d, Discard &dis)
	// {
		// int i = 0;
		// while(compare(h
		
		// while(h.getNumCards() < maxHand)
			// h.drawFromDeck(d);
			
	// }
// };


int main(int argc, char* argv[]){
	SDL_Event event;
	SDL_Surface *screen;
	bool done = false;
	TextImage bigText = TextImage("Sintony-Bold.ttf",20);
	TextImage smallText = TextImage("Sintony-Regular.ttf",15);
	SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT,16,
								SDL_ANYFORMAT|
								SDL_HWSURFACE|
								SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Lucky B", NULL);
	BackgroundImage bg = BackgroundImage(BG_IMAGE, screen);
	CardImage cardImages = CardImage(SPRITESHEET,screen);
	CardImage smallCardImages = CardImage(SPRITESHEET_S, screen, true);
	Deck d = Deck(1);
	d.outputDeck();
	Player p1 = Player(d,true);
	//Computer c1 = Computer(d, false);

	Player p2 = Player(d,false);
	Discard discardPile(&d);
	Button menuButton = Button(screen,675,530,105,55,true,2);
	Button doneButton = Button(screen,675,470,105,55,true,1);
	int windowMin = 0;
	
	vector<UIElement> ui;
	ui.push_back(menuButton);
	ui.push_back(doneButton);
	Slider slide = Slider(screen);
	bool mouseDown = false;
	int handPixelWidth;
	int adjustment;
	stringstream ss;

	//SlidingCard sc = SlidingCard(-1,-600);
	SlidingCard sc = SlidingCard(200,600);

	while(!done){
		bg.draw();

		d.draw(&cardImages,screen);
		discardPile.draw(&cardImages, screen);
		doneButton.draw(screen);
		menuButton.draw(screen);
		
		ss.str("");
		ss << "Cards: "<<p1.getNumCardsInHand();
		bigText.setText(ss.str());
		bigText.draw(screen, 685,420);
		ss.str("");
		ss << "Player 2 :  "<<p2.getNumCardsInHand()<<" cards";
		smallText.setText(ss.str());
		smallText.draw(screen,340,15);
		
		slide.draw(screen);
		p1.draw(&cardImages, &smallCardImages, screen);
		//c1.draw(&cardImages, &smallCardImages, screen);
		p2.draw(&cardImages, &smallCardImages, screen);
		sc.update();
		sc.draw(&cardImages, screen);

		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				done = true;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				cout<<"Click pos: ("<<event.button.x<<", "<<event.button.y<<")"<<endl;
	
				if(event.button.x > 401 && event.button.x < 401+CARDHEIGHT && event.button.y > 165 && event.button.y <165+CARDWIDTH && d.getNumCards()>0){
					p1.drawFromDeck(&d);
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
					int clickPoint = p1.getHandViewMin()+event.button.x;
					cout<<"Point: "<<clickPoint<<" viewMin: "<<p1.getHandViewMin()<<" card number: "<<clickPoint/105<<endl;
					p1.pickCard(clickPoint/105);
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
					handPixelWidth = p1.getNumCardsInHand()*CARDWIDTH_WITH_OFFSET;
					adjustment = (handPixelWidth / slide.MAX_SLIDER)*event.motion.xrel;
					p1.translateHandView(adjustment);

				}
			}
		}
		SDL_Flip(screen);
	}
	SDL_Quit();
	return 0;
}