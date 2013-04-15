#include "headers/cards.h"
#include "headers/Deck.h"
#include "headers/CardImage.h"
#include "headers/TextImage.h"
#include "headers/BackgroundImage.h"
#include "headers/Discard.h"
#include "headers/Hand.h"
#include "headers/LuckyB.h"

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

	void draw(CardImage *c, SDL_Surface *screen, int mine, int turn){
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
	bool isEmpty(){
		return boardList.empty();
	}
};


//UI Classes
class UIElement{ //Just chilling here I don't do anything but everything else is derived from me, not quite sure why I exist.
public:
	
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

	void init(SDL_Surface *screen){
		xpos=0;
		active=true;

		SDL_Surface *image;
		int colorKey;
		image = SDL_LoadBMP("../images/buttons.bmp");
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

		//changed this to reduce code svp
	bool clicked(int x, int y){
		if(active){
			return (x>=xpos+40 && x<xpos+40+SLIDER_WIDTH && y>SLIDER_YPOS && y<SLIDER_YPOS+SLIDER_HEIGHT);
		}
		return false;
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
	void init(SDL_Surface *screen, int inx, int iny, int inw, int inh, bool newactive, int row){
		xpos = inx;
		ypos = iny;
		w = inw;
		h = inh;
		active=newactive;

		SDL_Surface *image;
		int colorKey;
		image = SDL_LoadBMP("../images/buttons.bmp");
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
	/*bool getActive(){

	}*/
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
	void init(double xv, double yv){
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
	int mine;

public:
	void init(Deck &d, bool mainPlayer, int deckNum=1, int myTurn = 0) //I still have to take into consideration the number of players playing
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
	void drawHand(CardImage *c, SDL_Surface *screen){
		h.draw(c,screen);
	}
	void drawBoard(CardImage *c, SDL_Surface *screen,int turn){
		db->draw(c,screen,mine,turn);
		upBoard->draw(c,screen, mine, turn);
	}
	void draw(CardImage *cards, CardImage *smallCards, SDL_Surface *screen,int turn){
		if(turn == mine){
			h.draw(cards,screen);	
		}
		db->draw(smallCards,screen,mine, turn);
		upBoard->draw(smallCards,screen,mine, turn);

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
	/*MY_STUFF*/
	bool isValid_Move(vector<Card> player_hand, Card pile) //returns true if the hand passed in can be played 
	{
		bool is_valid = true;
		unsigned int last_card = -1;
		unsigned int this_card = player_hand[0].getValue();
		unsigned int pile_card = pile.getValue();
		cout << "Valid function test\n";
		if(player_hand.size() == 1)
		{
			if((this_card == 2 || this_card == 10)) is_valid = true; //A single special card is always a valid move
			else if(this_card > pile_card) is_valid = false; //a hand bigger then the value of the deck card is invalid 
		}
		else
		{
			last_card = player_hand[0].getValue(); //save the value of the first card for comparison
			for(unsigned int i=1; i<player_hand.size(); i++)
			{
				this_card = player_hand[i].getValue(); //save the value of first card
				if(this_card == 2 || this_card == 10) is_valid = true; //card is a special playing special cards is always valid
				else if(this_card > pile_card) //Cards greater in value then the card being pile card are not valid
				{
					is_valid = false;
					break;
				}
				else if(this_card != last_card) //Playing 2 or more cards of different values is not a valid move
				{
					is_valid = false;
					break;
				}
				last_card = player_hand[i].getValue(); //update last card for next iteration of loop
			}
			//everything else not explicitly marked invalid is valid
		}	
		return is_valid;
	}

	void translateHandView(int offset){
		h.translateView(offset);
	}
	void handle_input(SDL_Event &event, bool &done, bool &mouseDown, SlidingCard &sc, Slider &slide, int &handPixelWidth, int &adjustment, Deck &d, Discard &discardPile, int &turn)
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
};
class Computer:public Player
{
private:
	Hand h; //Hidden Play Hand
	Board *upBoard; //Face up Board Hand Section
	Board *db; //Face down Board Hand section 
	int maxHand; //Number per hand based on deck
	int maxBoard; //Number for board cards based on deck
	bool main; // True if this is player 1
	
public:
	void play(Deck &d, Discard &dis)
	{
		unsigned int i=0,j;
		int sp2 = -1, sp10 = -1;
		//vector<Card> ha = h.getHand();
		while(i < h.handList.size() && h.handList[i].getValue() < dis.getTopCardValue()  ) i++;
		for(j=0; j<h.handList.size(); j++)
			if(h.handList[j].getValue() == 2-1) sp2 == j;
			else if (h.handList[j].getValue() == 10-1) sp10 == j;

		 if(i < h.handList.size())
			for(j=i; j<h.handList.size(); j++)//perhaps only let loop for the max number of cards for any value
				if(h.handList[j].getValue() == dis.getTopCardValue())
					if(h.handList[j].isSelected() == false)
						h.handList[j].toggleSelected();
				else if(h.handList[j].getValue() == h.handList[i].getValue())
					if(h.handList[j].isSelected() == false)
						h.handList[j].toggleSelected();
		else
		{
			if(sp10 > -1)
				if(h.handList[sp10].isSelected() == false)
					h.handList[sp10].toggleSelected();
			else if (sp2 > -1)
				if(h.handList[sp2].isSelected() == false)
				{
					h.handList[sp2].toggleSelected();
					int small = h.handList[0].getValue();
					int smallPos = -1;
					for(j=0; j<h.handList.size(); j++)//Get the smallest value in the hand
						if(h.handList[j].getValue() < small)
						{
							small = h.handList[j].getValue();
							smallPos = j;
						}
					if(smallPos > -1)
						for(j=smallPos; j<h.handList.size(); j++)
							if(h.handList[j].getValue() == small)
								if(h.handList[j].isSelected() == false)
									h.handList[j].toggleSelected();
				}
				else //Have to pick up the discard pile
				{
					for(j=0; j < dis.discardPile.size(); j++)
						h.insert(dis.discardPile[j]);
					dis.discardPile.clear();
				}
		}		
		while(h.getNumCards() < maxHand)
			h.drawFromDeck(&d);
	}
};

class Game
{
private:
	SDL_Event event;
	SDL_Surface *screen;
	bool done;
	TextImage bigText;
	TextImage smallText;
	
	
	BackgroundImage bg;
	CardImage cardImages;
	CardImage smallCardImages;
	Deck d;
	
	//players should be at least an array, so we can have more than 2; probably a vector
	Player p1;
	Player p2;
	Discard discardPile;
	Button menuButton;
	Button doneButton;
	int windowMin;

	vector<UIElement> ui;
	
	Slider slide;
	bool mouseDown;
	int handPixelWidth;
	int adjustment;
	stringstream ss;

	//SlidingCard sc = SlidingCard(-1,-600);
	SlidingCard sc;
	int turn;
public:
	
	void init()
	{
		turn = 0;
		done = false;
		bigText.init("../fonts/Sintony-Bold.ttf",20);
		smallText.init("../fonts/Sintony-Regular.ttf",15);
		SDL_Init( SDL_INIT_EVERYTHING );
		screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT,16,
								SDL_ANYFORMAT|
								SDL_HWSURFACE|
								SDL_DOUBLEBUF);
		SDL_WM_SetCaption("Lucky B", NULL);
		 bg.init(BG_IMAGE, screen);
		 cardImages.init(SPRITESHEET,screen);
		 smallCardImages.init(SPRITESHEET_S, screen, true);
		 d.init(1);
		 d.outputDeck();
		 p1.init(d,true, 1,0);
		 p2.init(d,false, 1,1);
		 discardPile.init(&d);
		 menuButton.init(screen,675,530,105,55,true,2);
		 doneButton.init(screen,675,470,105,55,true,1);
		 windowMin = 0;
		 
		 ui.push_back(menuButton);
		 ui.push_back(doneButton);
		 
		 slide.init(screen);
		  mouseDown = false;
		  
		  sc.init(200,600);
	}
	void run()
	{
		while(!done){
		bg.draw();
		d.draw(&cardImages,screen);
		discardPile.draw(&cardImages, screen);
		doneButton.draw(screen);
		menuButton.draw(screen);

		
		

		slide.draw(screen);
		p1.draw(&cardImages, &smallCardImages, screen, turn);
		p2.draw(&cardImages, &smallCardImages, screen, turn);

		sc.update();
		sc.draw(&cardImages, screen);
		if (turn == 0) {
		ss.str("");
		ss << "Cards: "<<p1.getNumCardsInHand();
		bigText.setText(ss.str());
		bigText.draw(screen, 685,420);
		ss.str("");
		ss << "Player 2 :  "<<p2.getNumCardsInHand()<<" cards";
		smallText.setText(ss.str());
		smallText.draw(screen,340,15);
		p1.handle_input(event,done,mouseDown,sc,slide,handPixelWidth,adjustment,d,discardPile,turn);
		}
		else if (turn == 1) 
		{
		ss.str("");
		ss << "Cards: "<<p2.getNumCardsInHand();
		bigText.setText(ss.str());
		bigText.draw(screen, 685,420);
		ss.str("");
		ss << "Player 1 :  "<<p1.getNumCardsInHand()<<" cards";
		smallText.setText(ss.str());
		smallText.draw(screen,340,15);
		p2.handle_input(event,done,mouseDown,sc,slide,handPixelWidth,adjustment,d,discardPile,turn);
		}
		SDL_Flip(screen);
		}
	}
	void end()
	{
		SDL_Quit();
	}
};


int main(int argc, char** argv){ //RM removed arguements since we aren't passing any to get rid of compiler warning
		Game lucky_B; //why not call it what it is?
		lucky_B.init();
		lucky_B.run();
		lucky_B.end();
	return 0;
}
