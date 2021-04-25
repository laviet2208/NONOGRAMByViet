#pragma once
#include "bitmap.h"
#include <SDL_mixer.h>

void loadmixer(std::string path)
{
	Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
	if (sound != NULL)
		Mix_PlayChannel(-1, sound, 0);
	else
		cout << "ko load dc nhac" << endl;
}