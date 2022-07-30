#include "sound.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>


//Initializes variables
Sounds::Sounds()
{
	mNote = NULL;
	
}
	
//Deallocates memory
Sounds::~Sounds()
{
	mNote = NULL;
    Mix_FreeChunk( mNote );
}

bool Sounds::loadFromFile(const char* fileName)
{
	mNote = Mix_LoadWAV(fileName);
	
	if( mNote == NULL )
	{
		printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	return true;
}

void Sounds::playSound()
{
	Mix_PlayChannel( -1, mNote, 0 );	
}
