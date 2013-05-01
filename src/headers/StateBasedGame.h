#ifndef STATE_BASED_GAME_H
#define STATE_BASED_GAME_H

#include "includes.h"
#include "cards.h"
#include <map>
#include "GameState.h"

class StateBasedGame 
{
	SDL_Surface *screen;
	std::map<std::string, GameState*> states;
	
	public:
		StateBasedGame(GameState *firstState);
		SDL_Surface* getScreen();
		GameState* getState(string stateName);
		void addState(GameState *newState);
		void start();
};

#endif