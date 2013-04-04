#include "headers/sound.h"

bool sound::init_audio()
{
	if(Mix_OpenAudio(AUDIOSAMPLERATE, AUDIO_S16SYS , STEREO, CHUNKSIZE) == -1) 
	{
		cerr << "Error initializing SDL_mixer: " << Mix_GetError() << endl;
		return false;
	}
	return true;
}

bool sound::load_fx(char* filepath)
{
	fx = Mix_LoadWAV(filepath); 
	if(fx == NULL) return false;
	return true;
}

bool sound::load_track(char* filepath)
{
	track = Mix_LoadMUS(filepath); 
	if(track == NULL) return false;
	return true;
}

bool sound::play_fx()
{
	if(Mix_PlayChannel(-1, fx, 1) == -1)
	{
		cerr << "Error playing audio effect\n";
		return false;
	}
	return true;
}

bool sound::play_track()
{
	if(Mix_PlayMusic(track, 1) == -1) 
	{
		return false;
	}
	return true;
}

bool sound::fade_fx(int channel)
{
	if(Mix_FadeOutChannel(channel, 300) == -1)
	{
		cerr << "Error fading out audio effect\n";
		return false;
	}
	return true;
}
