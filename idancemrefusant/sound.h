#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>



class Sounds{
	public:
	
		//Initializes variables
		Sounds();
			
		//Deallocates memory
		~Sounds();
		
		bool loadFromFile(const char* fileName);

		Mix_Chunk* mNote;
				
		void playSound();


	private:
	
	
	
};

#endif
