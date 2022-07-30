#ifndef GAME_H
#define GAME_H

#include <string>
#include "dot.h"
#include "dotb.h"
#include "text.h"
#include "sound.h"
#include <sstream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


class Game {
	public:
		//makes a call to reset
		Game(void);
		
		// makes a call to cleanup
		~Game(void);
		
		//Initializes SDL, TTF. Creates window, renderer, textures of play/quit, debug text, words text
		//uncomment to add image files
		bool init();
		
		//deletes dots, text, window, renderer, quits subsystems
		void cleanup(void); 
		
		//calls cleanup and init.
		void reset(void);
		
		//initializes an SDL_Event called "event" and passes it to dot, so as to instruct the dot to move
		//it passes checkingMovements to increment it
		void handleEvents(bool checkingMovements);
		
		//loads text
		bool loadMedia();
		
		//initializes an SDL_Event called "event" and deals with it
		//*******combine this with handleEvents using a bool query so as not to re-use SDL_events***********
		void handleMenuEvents(void);
		
		//renders "play" and "quit" and line beneath them
		void renderMenu();
		
		
		bool checkAllColliders(void);

		void gameLoop(SDL_Rect* b, bool cameraStatus, bool isColliding);
		
		void clear(void);
		
		void render(void);
		
		void update(void);
		
		void playSound();
				
		int sound = 0;
		
		std::string prevWordsA;
		std::string prevWordsA1; 
		std::string prevWordsA2;
		std::string prevWordsB;
		std::string prevWordsB1;
		std::string prevWordsB2;

		 			
		bool GetisDone(void);
		
		void renderDebug();
		void changeDebugFigures();
		
		void renderTheWords();
		void changeText(bool textA, std::string theWordsStringA, bool textA1, std::string theWordsStringA1, bool textA2, std::string theWordsStringA2, 
						  bool textB, std::string theWordsStringB, bool textB1, std::string theWordsStringB1, bool textB2, std::string theWordsStringB2);

		
		
		void setTimeVariables(void);
		
		bool hasTimePassed(Uint32 timePassed);
		
		//where all the business happens
		void levelSelect(void);

		void dotBIdle();
		void dotBDance(int xDirectionMultiplier, int yDirectionMultiplier);

		void renderCredits();

	private:
		//member variables
		bool playSelected = true;
		//Screen dimension constants
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;
		//Window to render to
		SDL_Window* gWindow = NULL;
		bool isDone = false;
		bool isFullScreen = false;
		//Surface contained by window
		SDL_Renderer* gRenderer = NULL;
		//Image to load
		Dot *dot;
		DotB *dotB;
		DotB *dotC;
		
		LTexture *play;
		LTexture *quit;
		LTexture *debugTextA;
		LTexture *debugTextB;
		LTexture *debugTextC;
		LTexture *debugTextD;
		LTexture *debugTextE;

		
		LTexture *dotAWords;
		LTexture *dotAWords1;
		LTexture *dotAWords2;

		LTexture *dotBWords;
		LTexture *dotBWords1;
		LTexture *dotBWords2;
		
		LTexture *poemWords;
		LTexture *poemWords1;
		LTexture *poemWords2;
		LTexture *poemWords3;
		LTexture *poemWords4;
		LTexture *poemWords5;
		LTexture *poemWords6;
		LTexture *poemWords7;
		LTexture *poemWords8;
		LTexture *poemWords9;
		LTexture *poemWords10;
		LTexture *poemWords11;
		LTexture *poemWords12;
		LTexture *poemWords13;
		LTexture *poemWords14;
		LTexture *poemWords15;
		LTexture *poemWords16;
		LTexture *poemWords17;
		LTexture *poemWords18;
		LTexture *poemWords19;
		LTexture *poemWords20;
		LTexture *poemWords21;
		LTexture *poemWords22;
		LTexture *poemWords23;
		LTexture *poemWords24;
		LTexture *poemWords25;
		LTexture *poemWords26;
		LTexture *poemWords27;
		LTexture *poemWords28;
		LTexture *poemWords29;
		LTexture *poemWords30;
		LTexture *poemWords31;
		LTexture *poemWords32;
		LTexture *poemWords33;



		LTexture *creditText;

		
		std::stringstream dotATextStream;
		std::stringstream dotATextStream1;
		std::stringstream dotATextStream2;

		std::stringstream dotBTextStream;
		std::stringstream dotBTextStream1;
		std::stringstream dotBTextStream2;

		std::stringstream debugWordsA;
		std::stringstream debugWordsB;
		std::stringstream debugWordsC;
		std::stringstream debugWordsD;
		std::stringstream debugWordsE;
		
		
		//The music that will be played
		Mix_Music *gMusic = NULL;

		//The sound effects that will be used
		Sounds *Note1;
		Sounds *Note2;
		Sounds *Note3;
		Sounds *Note4;
		Sounds *Note5;
		Sounds *Note6;
		Sounds *Chord1;
		Sounds *Chord2;
		Sounds *Chord3;
		Sounds *Chord4;



		//23 & 27 (with uncommenting) and 12 are good departures for debug
		
		int level = 0;
		bool cameraOn = true;
		bool cameraOff = false;
		int prevVelX = 0;
		int prevVelY = 0;
		bool checkingMovement = false;
		int trigger = 0;
		SDL_Rect boundBox = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_Rect offScreen = {SCREEN_WIDTH*2,SCREEN_HEIGHT*2, 10, 10};
		Uint32 timeNow = 0;
		Uint32 timeBefore = 0;
		
		int idleVelX = 2;
		int idleVelY = 2;
		int idleSpeed = 2;
		int squareLength = 10;
		int prevMoveTrigger = 0;
		int colorFade = 255;
		int fontSize = 13;
		int lastSound = 0;

		int relativeX = 0;
		int relativeY = 0;

		bool showDebug = false;
		bool showCredits = false;
		
		int prevDOTX = 0;
		int prevDOTY = 0;
		int prevDOTBX = 0;
		int prevDOTBY = 0;
		int prevTRIGGER = 0;
		int prevMOVEMENTS = 0;
		int prevCOLLISIONS = 0;
		int wordsHeight = 15;


};



#endif
