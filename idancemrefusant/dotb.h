#ifndef DOTB_H
#define DOTB_H

#include <SDL2/SDL.h>


class DotB
{
    public:
        //The dimensions of the dot
        static const int DOT_WIDTH = 5;
        static const int DOT_HEIGHT = 5;
        static const int COLLIDER_WIDTH = 40;
        static const int COLLIDER_HEIGHT = 40;
		static const int tailLength = 15;
		
        //Maximum axis velocity of the dot
        static const int DOT_VEL = 4.9;

        //Initializes the variables
        DotB();
        
        ~DotB();


        //Takes key presses and adjusts the dot's velocity
        //void handleEvent( bool triggerOne, bool triggerTwo);

        //Moves the dot
        void move(bool isColliding);
		
		void init(int passedX, int passedY, int passedVelX, int passedVelY);
		
		//void initt(int passedX, int passedY, int passedVelX, int passedVelY);
		
		void freezeDot();

		void initCamMove(int passedX, int passedY);


        //Shows the dot on the screen relative to the camera
        void render(SDL_Renderer* passedRenderer);
        
        void renderDiffColor(SDL_Renderer* passedRenderer, int colorFade);

        
        void centreDot(SDL_Rect *passedCamera);
        
        //void repel(SDL_Rect dotBox, bool isCollision);
        
		int getWidth(void);
		
		int getHeight(void);
		
		int getPosX(void);
		
		int getPosY(void);
		
		int getVelX(void);
		
		int getVelY(void);
		
		int getDOT_VEL(void);
		
		SDL_Rect* getRect(void);
		SDL_Rect* getCollider(int i);


    private:
    	const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;

        //the dot's rect
        SDL_Rect theDot[tailLength];
        
        //The velocity of the dot
        int velX, velY;
        SDL_Rect collisionBoxes[tailLength];

};



#endif
