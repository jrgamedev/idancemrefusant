#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>

class LTexture{
	public:
		//Initializes variables
		LTexture();
		
		//Deallocates memory
		~LTexture();
		
		//Loads image at specified path
		bool loadFromFile(std::string textureText, SDL_Renderer* passedRenderer, int fontSize, bool chooseColor);
		
		//Deallocates texture
		void free();	
		
		//Renders texture at a given point
		void render(int x, int y, SDL_Renderer* passedRenderer);
		
		//Gets image dimenstions
		int getWidth();
		int getHeight();
		
		//The actual hardware texture
		SDL_Texture* mTexture;

	private:

		//Image dimensions
		int mWidth;
		int mHeight;
		
		SDL_Color white = {255,255,255};
		SDL_Color black = {0, 0, 0};
		TTF_Font *gFont = NULL;
	
};

#endif
