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
	bg.init(MAIN_BG, screen);
	playButton = Button(400, 300, 105, 55, "Menu", screen);
	ui.push_back(playButton);
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
					event.button.x < playButton.getXPos() + playButton.getWidth() &&
					event.button.y > playButton.getYPos() &&
					event.button.y < playButton.getYPos() + playButton.getHeight())
			{
				playButton.clicked();
				done = true;
				return "second";
			}
		}
		else if(event.type == SDL_MOUSEBUTTONUP && 
					event.button.x < playButton.getXPos() + playButton.getWidth() &&
					event.button.y > playButton.getYPos() &&
					event.button.y < playButton.getYPos() + playButton.getHeight())
		{
			playButton.released();
			return "";
		}
	}
	return "";
}