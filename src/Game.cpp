#include "headers/Game.h"

	void Game::init()
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
	}