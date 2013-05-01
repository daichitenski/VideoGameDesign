#include "headers/MainMenu.h"

MainMenu::MainMenu()
{
	name = "main";
}

void MainMenu::setName(string newName)
{
	name = newName;
}

bool MainMenu::enter(SDL_Surface *newScreen)
{
	screen = newScreen;
	//cout << "new screen set" << endl;
	bg.init(MAIN_BG, screen);
	//cout << "bg set" << endl;
	playButton.init(screen,675,530,105,55,true,2);
	//cout << "playbutton set" << endl;
	ui.push_back(playButton);
	//cout << "ui push set" << endl;
	return true;
}

string MainMenu::execute()
{
	done = false;
	string exitStateName = "";
	while(!done)
	{
		bg.draw();
		playButton.draw(screen);
		exitStateName = handleInput();
		SDL_Flip(screen);
	}
	cout << exitStateName << endl;
	return exitStateName;
}

void MainMenu::pause(string exitStateName)
{
}

void MainMenu::exit()
{
	
}

string MainMenu::handleInput()
{
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			done = true;
			return "EXIT";
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(event.button.x > playButton.getXPos() && 
					event.button.x < playButton.getXPos() + playButton.getW() &&
					event.button.y > playButton.getYPos() &&
					event.button.y < playButton.getYPos() + playButton.getH())
			{
				done = true;
				return "second";
			}
		}
	}
	return "";
}