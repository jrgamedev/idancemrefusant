#include "dot.h"
#include <SDL2/SDL.h>
#include <stdio.h>

Dot::Dot()
{
    //Initialize the offsets
    for(int i=0; i<tailLength; i++)
    {
    theDot[i] = {160, 240, DOT_WIDTH, DOT_HEIGHT};
	}
    //Initialize the velocity
    velX = 0;
    velY = 0;
}

Dot::~Dot()
{
	
}

void Dot::centreDot(void)
{	
	theDot[0].x -= camera.x;
	theDot[0].y -= camera.y;
			
	camera.x = 0;
	camera.y = 0;
					
}

void Dot::posInit(int passedX, int passedY)
{
	for (int i=0; i<tailLength; i++)
	{
		theDot[i].x = passedX;
		theDot[i].y = passedY;
	}
	//velX = 0;
	//velY = 0;
}

void Dot::init(int passedX, int passedY, int passedVelX, int passedVelY)
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
void Dot::initCamMove(int passedX, int passedY)
{

		camera.x += passedX;
		camera.y += passedY;
}


//when key pressed, change velocity. when key released, return velocity to 0;
void Dot::handleEvent( SDL_Event& e, bool checkingMovement )
{

    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{

        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velY -= DOT_VEL;
            	if(checkingMovement == true)
				{
					moveTrigger++;
				} 
				break;
            case SDLK_DOWN: velY += DOT_VEL;
            	if(checkingMovement == true)
				{
					moveTrigger++;
				} 
				break;
            case SDLK_LEFT: velX -= DOT_VEL;
            	if(checkingMovement == true)
				{
					moveTrigger++;
				} 
				break;
            case SDLK_RIGHT: velX += DOT_VEL;
            	if(checkingMovement == true)
				{
					moveTrigger++;
				} 
				break;			
            
        }
        
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velY += DOT_VEL; break;
            case SDLK_DOWN: velY -= DOT_VEL; break;
            case SDLK_LEFT: velX += DOT_VEL; break;
            case SDLK_RIGHT: velX -= DOT_VEL; break;
        }
    
    }
	

}

int Dot::checkMoveTrigger(bool turnToZero)
{
	if(turnToZero == true)
	{
		moveTrigger = 0;
		return moveTrigger;
	}
	else
	{
		return moveTrigger;
	}
}


void Dot::move(SDL_Rect* b, bool cameraOn)
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
		
		//If the dot went too far to the left or right
		if( checkCollision(b) == true )
		{
			//Move back
			theDot[0].x -= velX;
			// +(2*velX/DOT_VEL);
		}
		//move the dot back to the centre of the camera
		if(cameraOn == false)
		{
			if(theDot[0].x >= camera.x + camera.w || theDot[0].x < camera.x)
			{
				theDot[0].x -= velX;
				collisionNumber++;
			}
		}
		
		//Move the front dot up or down
		theDot[0].y += velY;
		
		if( checkCollision(b) == true )
		{
			//Move back
			theDot[0].y -= velY;
			// + (2*velY/DOT_VEL);
		}
		//move the dot to the centre of the camera
		if(cameraOn == false)
		{
			if(theDot[0].y >= camera.y + camera.h || theDot[0].y < camera.y)
			{
				theDot[0].y -= velY;
				collisionNumber++;
			}
		}
		//move the other dots closer to the front dot
		for(int i=1; i<tailLength; i++)
		{
			theDot[i].x = tempPosX[i-1];
			theDot[i].y = tempPosY[i-1];
		}
		
		
		
		if (cameraOn == true)
		{
			//Camera nonsense
			
			//centres dot in camera
			
			camera.x = theDot[0].x - camera.w/2;
			camera.y = theDot[0].y - camera.h/2;
			
			//keeps camera on screen
			for(int i=1; i<tailLength; i++)
			{
				theDot[i].x -= camera.x;
				theDot[i].y -= camera.y;
			}
			//theDot[0].x -= camera.x;
			//theDot[0].y -= camera.y;
			
			//camera.x = theDot[0].x - camera.w/2;
			//camera.y = theDot[0].y - camera.h/2;
		}
		
		
	

	
}



void Dot::render(SDL_Renderer* passedRenderer)
{

		//initialize alpha
		int colorFade = 255;
		
		//render camera
		//SDL_SetRenderDrawColor(passedRenderer, 0, 50, 0, 0);
		//SDL_RenderFillRect(passedRenderer, &camera);
		
		//render camera centre
		//SDL_SetRenderDrawColor(passedRenderer, 0, 100, 0, 0);
		//SDL_RenderFillRect(passedRenderer, &cameraCentre);
			
		SDL_SetRenderDrawColor(passedRenderer, 255, 0, 0, 255);
		//draw player's tail
		for(int i=1; i<tailLength; i++)
		{

			SDL_RenderFillRect(passedRenderer, &theDot[i]);
			
			//fade tail
			if (colorFade-13*i>0)
			{
			SDL_SetRenderDrawColor(passedRenderer, colorFade-13*i, 0, 0, 255);
			}
	
		}
			//Draw front-most pixel
			SDL_SetRenderDrawColor(passedRenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(passedRenderer, &theDot[0]);
	
}

bool Dot::checkCollision(SDL_Rect* b)
{
	Uint32 timeNow = SDL_GetTicks();
	SDL_Rect tempRect{b->x, b->y, b->w, b->h};

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	
	//calculate the sides of rect A
	leftA = theDot[0].x;
	rightA = theDot[0].x + theDot[0].w;
	topA = theDot[0].y;
	bottomA = theDot[0].y + theDot[0].h;
	
	//calculate the sides of rect B
	
	leftB = tempRect.x;
    rightB = tempRect.x + tempRect.w;
    topB = tempRect.y;
    bottomB = tempRect.y + tempRect.h;
    
    if(bottomA < topB)
    {
		return false;
	}
	if(topA > bottomB)
	{
		return false;
	}
	if(rightA < leftB)
	{
		return false;
	}
	if (leftA > rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	if(timeNow > timeBefore + 300)
	{
		collisionNumber++;
		timeBefore = timeNow;
	}
	return true;
};

int Dot::checkCollisionNumber(bool turnToZero)
{
	if(turnToZero == true)
	{
		collisionNumber = 0;
		return collisionNumber;
	}
	else
	{
	return collisionNumber;
	}
	
};



int Dot::getWidth(void)
{
	return DOT_WIDTH;
}
		
int Dot::getHeight(void)
{
	return DOT_HEIGHT;
}

int Dot::getPosX(void)
{
	return theDot[0].x;
}
		
int Dot::getPosY(void)
{
	return theDot[0].y;
}

int Dot::getVelX(void)
{
	return velX;
}

int Dot::getVelY(void)
{
	return velY;
}

int Dot::getDOT_VEL(void)
{
	return DOT_VEL;
}

SDL_Rect* Dot::getRect(void)
{
	return 	&theDot[0];
}

SDL_Rect* Dot::getCamera(void)
{
	return 	&camera;
}

SDL_Rect* Dot::getCameraCentre(void)
{
		return &cameraCentre;
}
