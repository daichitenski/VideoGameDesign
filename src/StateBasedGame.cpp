#include "headers/StateBasedGame.h"

//Create the state based game, the first state passed in should have the name 'start'
StateBasedGame::StateBasedGame(GameState *firstState)
{
	SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT,16,
								SDL_ANYFORMAT|
								SDL_HWSURFACE|
								SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Lucky B", NULL);
	
	addState(firstState);
}

SDL_Surface* StateBasedGame::getScreen()
{
	return screen;
}

void StateBasedGame::addState(GameState *newState)
{
	states[newState->getName()] = newState;
}

GameState* StateBasedGame::getState(string stateName)
{
	return states[stateName];
}

void StateBasedGame::start()
{
	bool done = false;
	string nextStateName = "";
	GameState *starter = states["main"];
	while(!done)
	{
		if(starter->enter(screen))
		{
			cout << "justbefore execute" << endl;
			nextStateName = starter->execute();
			if(nextStateName.compare("EXIT") == 0)
			{
				done = true;
			}
			else if(nextStateName.size() > 0)
			{
				starter->exit(nextStateName);
				starter = states[nextStateName];
				nextStateName = "";
			}
		}
	}
	SDL_Quit();
}