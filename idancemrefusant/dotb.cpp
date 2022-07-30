#include "dotb.h"
#include <SDL2/SDL.h>
#include <stdio.h>

DotB::DotB()
{
	for(int i=0; i<tailLength; i++)
    {
		theDot[i] = {1000, 1000, DOT_WIDTH, DOT_HEIGHT};
	}
}

DotB::~DotB()
{
	
}

void DotB::init(int passedX, int passedY, int passedVelX, int passedVelY)
{
	
    theDot[0].x = passedX;
    theDot[0].y = passedY;
    //Initialize the velocity
    velX = passedVelX;
    velY = passedVelY;
}
/*
void DotB::initt(int passedX, int passedY, int passedVelX, int passedVelY)
{
	for (int i=0; i<tailLength; i++)
	{
		theDot[i].x += passedX;
		theDot[i].y += passedY;
	}
    //Initialize the velocity
    velX = passedVelX;
    velY = passedVelY;
}
*/
void DotB::freezeDot()
{
	for(int i=0;i<tailLength;i++)
	{
    theDot[i].x = theDot[i].x;
    theDot[i].y = theDot[i].y;
	}
    //Initialize the velocity
    velX = 0;
    velY = 0;
}

void DotB::move(bool isColliding)
{
	
		
		
	//save tail positions of previous frame
		int tempPosX[tailLength];
		int tempPosY[tailLength];

		for (int i = 0; i<tailLength; i++)
		{
			tempPosX[i] = theDot[i].x;
			tempPosY[i] = theDot[i].y;
		}
		
		//Move the front dot left or right
		theDot[0].x += velX;
		if(isColliding == true)
		{
			theDot[0].x -= velX;
		}

		//Move the front dot up or down
		theDot[0].y += velY;
		if(isColliding == true)
		{
			theDot[0].y -= velY;
		}
		

		//move the other dots closer to the front dot
		for(int i=1; i<tailLength; i++)
		{
			theDot[i].x = tempPosX[i-1];
			theDot[i].y = tempPosY[i-1];
		}
		for(int i=0; i<tailLength; i++)
		{
			collisionBoxes[i] = {theDot[i].x - COLLIDER_WIDTH/2, theDot[i].y - COLLIDER_HEIGHT/2, COLLIDER_WIDTH, COLLIDER_HEIGHT};
		}
		
		

}

void DotB::initCamMove(int passedX, int passedY)
{
	for (int i=0; i<tailLength; i++)
	{
		theDot[i].x += passedX;
		theDot[i].y += passedY;
	}
	for(int i=0; i<tailLength; i++)
		{
			collisionBoxes[i] = {theDot[i].x - COLLIDER_WIDTH/2, theDot[i].y - COLLIDER_HEIGHT/2, COLLIDER_WIDTH, COLLIDER_HEIGHT};
		}

}

void DotB::centreDot(SDL_Rect *passedCamera)
{
	int dotXOffset = passedCamera->x;
	int dotYOffset = passedCamera->y;
	for (int i = 0; i<tailLength; i++)
	{
	theDot[i].x -= dotXOffset;
	theDot[i].y -= dotYOffset;
	}
}

void DotB::render(SDL_Renderer* passedRenderer)
{
	  
	int colorFade = 255;
	//draw collider
	/*for(int i=0; i<tailLength; i++)
	{
		SDL_SetRenderDrawColor(passedRenderer, 0, 0, 50, 255);
		SDL_RenderFillRect(passedRenderer, &collisionBoxes[i]);
	}*/
		SDL_SetRenderDrawColor(passedRenderer, 0, 0, 255, 255);

	//draw player's tail
		for(int i=1; i<tailLength; i++)
		{

			SDL_RenderFillRect(passedRenderer, &theDot[i]);
			//fade tail
			if (colorFade-13*i>0)
			{
			SDL_SetRenderDrawColor(passedRenderer, 0, 0, colorFade-13*i, 255);
			}
		}
		
			//Draw front-most pixel
			SDL_SetRenderDrawColor(passedRenderer, 0, 0, 255, 255);
			SDL_RenderFillRect(passedRenderer, &theDot[0]);
	
}

void DotB::renderDiffColor(SDL_Renderer* passedRenderer, int colorFade )
{
		  
		
			//Draw front-most pixel
			SDL_SetRenderDrawColor(passedRenderer, 0, 0, colorFade, 255);
			SDL_RenderFillRect(passedRenderer, &theDot[0]);
	
}


int DotB::getWidth(void)
{
	return DOT_WIDTH;
}
		
int DotB::getHeight(void)
{
	return DOT_HEIGHT;
}

int DotB::getPosX(void)
{
	return theDot[0].x;
}
		
int DotB::getPosY(void)
{
	return theDot[0].y;
}

int DotB::getVelX(void)
{
	return velX;
}

int DotB::getVelY(void)
{
	return velY;
}

SDL_Rect* DotB::getRect(void)
{
	return 	&theDot[0];
}

SDL_Rect* DotB::getCollider(int i)
{
	return 	&collisionBoxes[i];
}

int DotB::getDOT_VEL(void)
{
	return DOT_VEL;
};


