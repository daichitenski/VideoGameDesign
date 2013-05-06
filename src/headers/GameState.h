#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "includes.h"

class GameState
{
	protected:
		SDL_Surface *screen;
		std::string name;
		bool done = false;
	
	public:
		string getName(){return name;};
		virtual bool enter(SDL_Surface *newScreen){return false;};
		virtual string execute(){};
		virtual void pause(string exitStateName){};
		virtual void exit(string exitStateName){};
		virtual string handleInput(){};
		//virtual ~GameState(){};
};

#endif