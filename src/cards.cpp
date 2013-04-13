#include "headers/cards.h"

//Image Classes
class CardImage{
	string fname;
	SDL_Surface *cardSheet;
	SDL_Rect src, dest;
	bool small;

public:
	const static int OFFSET = 10;
	const static int OFFSET_SMALL = 3;
	void init(string name, SDL_Surface *screen, bool smallCards=false){
		fname=name;
		small = smallCards;
		init(screen);
	}

	void init(string name, int val, SDL_Surface *screen, bool smallCards = false){
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
	void init(string fName, int size){
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
	void init(string name, SDL_Surface *s){
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
	int getValue() const{
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
	void init(int numDecks){
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
		//this is awful, our positions for stuff is all in literal values	
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
	int numCards;
	int numConsecative;
	bool killed;
	
public:
	deque<Card> discardPile;
	void init(Deck *d){
		numCards = 0;
		numConsecative = 0;
		Card c = d->drawCard();
		c.flipCard();
		discardPile.push_front(c);
		numCards++;
		numConsecative++;
		killed = false;
		
	}
	void outputDiscard(){
		cout<<"Outputting Discard Pile List"<<endl;
		for(int i=0;i<numCards;i++){
			discardPile[i].outputCard();
		}
	}
	void draw(CardImage *c, SDL_Surface *screen){
		if( killed == false)
		{
			Card temp = discardPile.front();
			c->selectCard(temp.getValue());
			c->draw(screen,308,165);
		}
	}
	void killDiscard(){
		killed == true;
		numConsecative = 0;
		numCards = 0;
		discardPile.clear(); //Clears the que by destroying every member
	}
	int getTopCardValue(){
		if(!discardPile.empty())
		{
			Card c;
			c = discardPile.front();
			return c.getValue();
		}
		else
		{
			return 1; //because this is "2" and any value can be played on a 2
		}
	}
	void layCardPhase(const vector<Card> &playCards, int numDecks=1){//Vector needs to be in the order of first card to play in the front ie) 2, 3, 3 to play the 2 before the 3's
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
						for(int i=0; i<playCards.size(); i++)
						{
							numConsecative++;
							discardPile.insert(discardPile.begin(), playCards[i]);
							numCards++;
						}
					}
					else if(playCards[0].getValue() == 1){
						numConsecative =0;
						discardPile.insert(discardPile.begin(), playCards[0]);
						for(int i=1; i<playCards.size(); i++)
						{
							numConsecative++;
							discardPile.insert(discardPile.begin(), playCards[i]);
							numCards++;
						}
					}
					else{  //Needs check that all are same value or greater than
						numConsecative =0;
						for(int i=0; i<playCards.size(); i++)
						{
							numConsecative++;
							discardPile.insert(discardPile.begin(), playCards[i]);
							numCards++;
						}
					}
				else{
					numConsecative =0;
					for(int i=0; i<playCards.size(); i++)
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
	int numCards, viewMin;
	SDL_Surface *handSurface;
	SDL_Rect handSpace;
	static const int HAND_HEIGHT = 140;
	static const int HAND_WIDTH = 4000;
	static const int VIEW_WINDOW_WIDTH = 630;
	static const int VIEW_WINDOW_STEP = 45;

public:
	vector<Card> handList;
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
		return numCards;//return handList.size();
	}
	vector<Card> getHand()
	{
		return handList;
	}
	void remove(vector<Card> inCards){
		for(int i=0; i<inCards.size(); i++)
			remove(inCards[i]);
	}
	void remove(Card newCard){
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
		int i=0;
		bool sp2, sp10;
		vector<Card> ha = h.getHand();
		while(ha[i].getValue() < dis.getTopCardValue() && i < ha.size() ) i++;
		// if(i < ha.size())
			// if(ha.[i].getValue() == dis.getTopCard())
			// {
				// dis.
			// }
		// else
			// for(i=0; i<ha.size(); i++)
				// if(ha[i].get
		
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


int main(int argc, char* argv[]){
		Game game;
		game.init();
		game.run();
		game.end();
	return 0;
}
