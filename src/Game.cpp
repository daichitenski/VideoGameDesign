#include "headers/Game.h"

Game::Game()
{
	name = "game";
}

void Game::setName(string newName)
{
	name = newName;
}

bool Game::enter(SDL_Surface *newScreen)
{
	turn = 0;
	done = false;
	bigText.init("../fonts/Sintony-Bold.ttf",20);
	smallText.init("../fonts/Sintony-Regular.ttf",15);
	screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT,16,
							SDL_ANYFORMAT|
							SDL_HWSURFACE|
							SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Lucky B", NULL);
	bg.init(BG_IMAGE, screen);
	cardImages.init(SPRITESHEET,screen);
	smallCardImages.init(SPRITESHEET_S, screen, true);
	deck.init(1);
	deck.outputDeck();
	p1.init(deck,true, 1,0);
	p2.init(deck,false, 1,1);
	discardPile.init(&deck);
	menuButton = Button(675,530,105,55,"Menu", screen);
	doneButton = Button(675,470,105,55,"Done", screen);
	windowMin = 0;
	 
	ui.push_back(menuButton);
	ui.push_back(doneButton);
	 
	slide.init(screen);
	mouseDown = false;
	  
	sc.init(200,600);
}

string Game::execute()
{
	while(!done)
	{
		bg.draw();
		deck.draw(&cardImages,screen);
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
		p1.handle_input(event,done,mouseDown,sc,slide,handPixelWidth,adjustment,deck,discardPile,turn);
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
		p2.handle_input(event,done,mouseDown,sc,slide,handPixelWidth,adjustment,deck,discardPile,turn);
		}
		SDL_Flip(screen);
	}
}

void Game::pause(string exitStateName){};
void Game::exit(string exitStateName){};
string Game::handleInput()
{
	/*while (SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			done == true;
			return "EXIT";
		}
		
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(event.button.x > 401 && event.button.x < 401+CARDHEIGHT && 
				event.button.y > 165 && event.button.y <165+CARDWIDTH && 
				deck.getNumCards()>0)
			{
				if(h.getNumCards() < maxHand )
				{
					drawFromDeck(&d);
					sc.reset();
					cout<<"Drawing card from deck"<<endl;
				}
			}
			
			else if (slide.clicked(event.button.x,event.button.y))
			{
				cout<<"Slider clicked"<<endl;
				mouseDown = true;
			}
			
			else if(event.button.x>10 && event.button.x<625 && 
					event.button.y>475 && event.button.y<880)
			{
				cout<<"Hand Area clicked"<<endl;
				int clickPoint = getHandViewMin()+event.button.x;
				cout<<"Point: "<<clickPoint<<" viewMin: "<<getHandViewMin()<<" card number: "<<clickPoint/105<<endl;
				pickCard(clickPoint/105);
			}
			
			if(event.button.x>308 && event.button.x< (308 + CARDWIDTH) && event.button.y > 165 && event.button.y<(165 + CARDHEIGHT ))
			{
				vector<Card> playCards;
				for (int i = 0; i < h.getNumCards();i++) //What do I do?
				{
					if (h.handList[i].isSelected())
					{
						playCards.push_back(h.handList[i]);
						h.remove(h.handList[i]);
						i--; //what is this all about?
					}
				}					
				if (playCards.size() != 0 && isValid_Move(playCards, discardPile.getTopCardValue()))
				{
					cout << "Valid Move \n";
					discardPile.layCardPhase(playCards);
					(turn == 0) ? turn = 1: turn = 0;
				} //This doesn't match the function definition in Discard.cpp wtf!?
				//this line of code doesn't scale to lots of players
				else
				{
					cout << "invalid move \n";
					h.insert(playCards);
				}
			}

		}
		
		else if(event.type == SDL_MOUSEBUTTONUP){
			if(mouseDown == true){	
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
	}*/
}

/*void Game::init()
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
	 menuButton = Button(675,530,105,55,"Menu", screen);
	 doneButton = Button(675,470,105,55,"Done", screen);
	 windowMin = 0;
	 
	 ui.push_back(menuButton);
	 ui.push_back(doneButton);
	 
	 slide.init(screen);
	  mouseDown = false;
	  
	  sc.init(200,600);
}
void Game::run()
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
void Game::end()
{
	SDL_Quit();
}*/