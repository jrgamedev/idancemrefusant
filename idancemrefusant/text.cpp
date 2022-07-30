#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

LTexture::LTexture()
{
	//Initialize

	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	

}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string textureText, SDL_Renderer* passedRenderer, int fontSize, bool chooseColor)
{
	SDL_Color textColor = white;
	if (chooseColor == false)
	{
		textColor = black;
	}
	
	//Get rid of preexisting texture
	free();
	//Open the font
	gFont = TTF_OpenFont("fontFiles/unifont-12.1.04.ttf", fontSize);
	
	if(gFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Load image at specified path
		
		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(gFont, textureText.c_str(), textColor);
		if(textSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", TTF_GetError());;
		}
		else
		{
			//Create texture from surface pixels
			mTexture = SDL_CreateTextureFromSurface(passedRenderer, textSurface);
			if(mTexture == NULL)
			{
				printf( "Unable to create texture from %s! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Get image dimenstions
				mWidth = textSurface->w;
				mHeight = textSurface->h;
			}	
			//Get rid of old loaded surface
			SDL_FreeSurface(textSurface);
		}
	}
	//Return success
	return mTexture != NULL;
} 

void LTexture::free()
{
	//Free texture if it exists
	if(mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
	if (gFont != NULL)
	{
		TTF_CloseFont(gFont);
		gFont = NULL;
	}
}


void LTexture::render(int x, int y, SDL_Renderer* passedRenderer)
{
	
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	SDL_RenderCopy(passedRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

