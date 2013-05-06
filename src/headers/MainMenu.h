#ifndef MAINMENU_H
#define MAINMENU_H

#include "includes.h"
#include "GameState.h"
#include "cards.h"
#include "BackgroundImage.h"
#include "Button.h"

class MainMenu: public GameState
{
	SDL_Event event;
	BackgroundImage bg;
	Button playButton;
	vector<UIElement> ui;
	
	public:
		MainMenu();
		void setName(string newName);
		bool enter(SDL_Surface *newScreen);
		string execute();
		void pause(string exitStateName);
		void exit(string exitStateName);
		string handleInput();
};

#endif