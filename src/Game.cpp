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
	players.push_back(p1);
	players.push_back(p2);
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
	string exitStateName = "";
	while(!done)
	{
		bg.draw();
		deck.draw(&cardImages,screen);
		discardPile.draw(&cardImages, screen);
		doneButton.draw(screen);
		menuButton.draw(screen);

		slide.draw(screen);
		for(int i=0; i<players.size(); i++)
		{
			players[i].draw(&cardImages, &smallCardImages, screen, turn);
		}

		sc.update();
		sc.draw(&cardImages, screen);
		
		if (turn == 0) {
		ss.str("");
		ss << "Cards: "<<players[0].getNumCardsInHand();
		bigText.setText(ss.str());
		bigText.draw(screen, 685,420);
		ss.str("");
		ss << "Player 2 :  "<<players[1].getNumCardsInHand()<<" cards";
		smallText.setText(ss.str());
		smallText.draw(screen,340,15);
		}
		
		else if (turn == 1) 
		{
		ss.str("");
		ss << "Cards: "<<players[1].getNumCardsInHand();
		bigText.setText(ss.str());
		bigText.draw(screen, 685,420);
		ss.str("");
		ss << "Player 1 :  "<<players[0].getNumCardsInHand()<<" cards";
		smallText.setText(ss.str());
		smallText.draw(screen,340,15);
		}
		exitStateName = handleInput();
		cout << "after event checking" << endl;
		SDL_Flip(screen);
	}
	return exitStateName;
}

void Game::pause(string exitStateName){};
void Game::exit(string exitStateName){};
string Game::handleInput()
{
	while (SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			done = true;
			return "EXIT";
		}
		
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(event.button.x > 401 && event.button.x < 401+CARDHEIGHT && 
				event.button.y > 165 && event.button.y <165+CARDWIDTH && 
				deck.getNumCards()>0)
			{
				if(players[turn].getHand()->getNumCards() < players[turn].getMaxHand())
				{
					players[turn].drawFromDeck(&deck);
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
				int clickPoint = players[turn].getHandViewMin()+event.button.x;
				cout<<"Point: "<<clickPoint<<" viewMin: "<<players[turn].getHandViewMin()<<" card number: "<<clickPoint/105<<endl;
				players[turn].pickCard(clickPoint/105);
			}
			
			else if(event.button.x>308 && event.button.x< (308 + CARDWIDTH) && event.button.y > 165 && event.button.y<(165 + CARDHEIGHT ))
			{
				vector<Card> playCards;
				for (int i = 0; i < players[turn].getHand()->getNumCards();i++) //What do I do?
				{
					if (players[turn].getHand()->handList[i].isSelected())
					{
						playCards.push_back(players[turn].getHand()->handList[i]);
						players[turn].getHand()->remove(players[turn].getHand()->handList[i]);
						i--; //what is this all about?
					}
				}					
				if (playCards.size() != 0 && players[turn].isValid_Move(playCards, discardPile.getTopCardValue()))
				{
					cout << "Valid Move \n";
					discardPile.layCardPhase(playCards);
					(turn == 0) ? turn = 1: turn = 0;
				} //This doesn't match the function definition in Discard.cpp wtf!?
				//this line of code doesn't scale to lots of players
				else
				{
					cout << "invalid move \n";
					players[turn].getHand()->insert(playCards);
				}
			}
			
			else if(event.button.x>675 && event.button.x<780 && event.button.y>470 && event.button.y<525)
			{
				players[turn].getHand()->pickUpPile(discardPile.discardPile);
				discardPile.killDiscard();
				players[turn].getHand()->unSelectAll();
				//discardPile.draw();
				(turn == 0) ? turn = 1: turn = 0;
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
				handPixelWidth = players[turn].getNumCardsInHand()*CARDWIDTH_WITH_OFFSET;
				adjustment = (handPixelWidth / slide.MAX_SLIDER)*event.motion.xrel;
				players[turn].translateHandView(adjustment);
			}
		}
	}
	return "";
}