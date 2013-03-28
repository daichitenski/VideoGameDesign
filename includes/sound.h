#ifndef SOUND_H
#define SOUND_H

	#include "../includes/includes.h"

	#define AUDIOSAMPLERATE 44100
	#define CHUNKSIZE 2048
	#define STEREO 2

	class sound
	{
		private: //to simplify implimentation we will figure out exactly how many sounds we are going to play and put a ptr to each one here
		Mix_Chunk* fx;
		Mix_Music* track;
		
		public:
		bool init_audio();
		bool load_fx(char* filepath);
		bool load_track(char* filepath);
		bool play_fx();
		bool play_track();
		bool fade_fx(int channel);
	};

#endif