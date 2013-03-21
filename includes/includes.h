#ifndef INCLUDES_H
#define INCLUDES_H

	#ifdef __linux__
		#include "../includes/linux/SDL.h"
		#include "../includes/linux/SDL_ttf.h"
	#endif

	#ifdef _WIN32
		#include "../includes/windows/SDL.h"
		#include "../includes/windows/SDL_ttf.h"
	#endif

	#include <iostream>
	#include <sstream>
	#include <string>
	#include <deque>
	#include <time.h>
	#include <vector>
	#include <algorithm>

	using namespace std;
	
#endif
