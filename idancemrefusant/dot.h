#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>


class Dot
{
    public:
        //The dimensions of the dot
        static const int DOT_WIDTH = 5;
        static const int DOT_HEIGHT = 5;
		static const int tailLength = 15;
		
        //Maximum axis velocity of the dot
        static const int DOT_VEL = 5;

        //Initializes the variables
        Dot();
        
        ~Dot();

        
        void centreDot(void);
		
		void init(int passedX, int passedY, int passedVelX, int passedVelY);
		
		void initCamMove(int passedX, int passedY);

		void posInit(int passedX, int passedY);

		
        //Takes key presses and adjusts the dot's velocity
        void handleEvent( SDL_Event& e , bool checkingMovement);

        //Moves the dot
        void move(SDL_Rect* b, bool cameraOn);

		bool checkCollision(SDL_Rect* b);
		
		int checkCollisionNumber(bool turnToZero);
		Uint32 timeBefore = 0;		
		int checkMoveTrigger(bool turnToZero );

        //Shows the dot on the screen relative to the camera
        void render(SDL_Renderer* passedRenderer);
        
		int getWidth(void);
		
		int getHeight(void);
		
		int getPosX(void);
		
		int getPosY(void);
		
		int getVelX(void);
		
		int getVelY(void);
		
		int getDOT_VEL(void);
		
		SDL_Rect* getRect(void);
		
		SDL_Rect* getCamera(void);
		
		SDL_Rect* getCameraCentre(void);
    private:
    	const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;

        //The X and Y offsets of the dot
        SDL_Rect theDot[tailLength];
        

        //The velocity of the dot
        int velX, velY;
        
        SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_Rect cameraCentre = {SCREEN_WIDTH/2 - 5, SCREEN_HEIGHT/2 - 5, 29, 20};
		int collisionNumber = 0;
		int moveTrigger = 0;
       
};



#endif
