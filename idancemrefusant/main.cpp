//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "game.h"

int main(int argc, char* args[])
{
	//Start up SDL and create window
	Game *game = new Game();
		
		//While application is running
		while(!game->GetisDone())
		{
			game->levelSelect();
		}

	//Free resources and close SDL
	delete game;
	
	return 0;
}
