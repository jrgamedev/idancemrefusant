#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


#include "game.h"

Game::Game(void)
{
	reset();
};

Game::~Game(void)
{
	cleanup();
};

bool Game::init()
{
	//Initialization flag
	bool success = true;
	
	//Initialize SDL
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
		isDone = true;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("i dancem refusant", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
			isDone = true;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
				isDone = true;
			}
			else
			{
				//Initialize renderer colour
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
			
				/*
				//Initialize PNGloading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
					isDone = true;
				}
				*/
				
				//Initialize SDL_ttf
				if(TTF_Init()==-1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
					isDone = true;
				}	
				
				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
				
				
				//Load media
				if(!loadMedia())
				{
					printf("Failed to load media!\n");
					success = false;
					isDone = true;
				}
				dot = new Dot;
				dotB = new DotB;
				dotB->init(1000, 1000, 0, 0);
				boundBox = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};

			}
		}
	}
	isDone = false;
	
	
	return success;
	
}

void Game::cleanup(void) {
	//Free loaded image
	delete dot;
	delete dotB;
	delete play;
	delete quit;
	delete debugTextA;
	delete debugTextB;
	delete debugTextC;
	delete debugTextD;
	delete debugTextE;
	delete dotAWords;
	delete dotAWords1;
	delete dotAWords2;
	
	delete dotBWords;
	delete dotBWords1;
	delete dotBWords2;
	
	delete poemWords;
	delete poemWords1;
	delete poemWords2;
	delete poemWords3;
	delete poemWords4;
	delete poemWords5;
	delete poemWords6;
	delete poemWords7;
	delete poemWords8;
	delete poemWords9;
	delete poemWords10;
	delete poemWords11;
	delete poemWords12;
	delete poemWords13;
	delete poemWords14;
	delete poemWords15;
	delete poemWords16;
	delete poemWords17;
	delete poemWords18;
	delete poemWords19;
	delete poemWords20;
	delete poemWords21;
	delete poemWords22;
	delete poemWords23;
	delete poemWords24;
	delete poemWords25;
	delete poemWords26;
	delete poemWords27;
	delete poemWords28;
	delete poemWords29;
	delete poemWords30;
	delete poemWords31;
	delete poemWords32;
	delete poemWords33;

	delete creditText;

	//free sounds
	delete Note1;
	delete Note2;
	delete Note3;
	delete Note4;
	delete Note5;
	delete Note6;
	delete Chord1;
	delete Chord2;
	delete Chord3;
	delete Chord4;
	
    //Free the music
    Mix_CloseAudio();
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
	
	
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	
	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();

}

void Game::reset(void) {
	cleanup();
	init();
}


void Game::handleEvents(bool checkingMovements) {
	
	SDL_Event event;
	//Handle events on queue

	while(SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		if(event.type == SDL_QUIT)
		{
			isDone = true;
		}
		
		if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
		{
			switch( event.key.keysym.sym )		
			{
				case SDLK_F1:
					if (isFullScreen == false)
					{
						SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
						isFullScreen = true;
					}
					else
					{
						SDL_SetWindowFullscreen(gWindow, 0);
						isFullScreen = false;

					}
					break;
				case SDLK_r:
					
					level = 0;

					break;
				case SDLK_TAB:
					if(showDebug == false)
					showDebug = true;
					else
					showDebug = false;
					break;
					
				default: break;
			}
		}

		
		
		dot->handleEvent(event, checkingMovements );

	}

	
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	//the "play" text in the menu
	play = new LTexture();	
	std::string oneWords = "Play";
	play->loadFromFile(oneWords, gRenderer, 28, true);
	//the "quit" text in the menu
	quit = new LTexture();
	std::string twoWords = "Quit";
	quit->loadFromFile(twoWords, gRenderer, 28, true);
	
	//give the other text something to do so that I can test it works
	std::string testWords = "Test";
	debugTextA = new LTexture();
	debugTextA->loadFromFile(testWords, gRenderer, 28, true);
	debugTextB = new LTexture();
	debugTextB->loadFromFile(testWords, gRenderer, 28, true);
	debugTextC = new LTexture();	
	debugTextC->loadFromFile(testWords, gRenderer, 28, true);
	debugTextD = new LTexture();
	debugTextD->loadFromFile(testWords, gRenderer, 28, true);
	debugTextE = new LTexture();
	debugTextE->loadFromFile(testWords, gRenderer, 28, true);
	dotAWords = new LTexture();
	dotAWords->loadFromFile(testWords, gRenderer, 28, true);
	dotAWords1 = new LTexture();
	dotAWords1->loadFromFile(testWords, gRenderer, 28, true);
	dotAWords2 = new LTexture();
	dotAWords2->loadFromFile(testWords, gRenderer, 28, true);
	dotBWords = new LTexture();
	dotBWords->loadFromFile(testWords, gRenderer, 28, true);
	dotBWords1 = new LTexture();
	dotBWords1->loadFromFile(testWords, gRenderer, 28, true);
	dotBWords2 = new LTexture();
	dotBWords2->loadFromFile(testWords, gRenderer, 28, true);
	poemWords = new LTexture(); poemWords->loadFromFile(testWords, gRenderer, 28, true);
	poemWords1 = new LTexture(); poemWords1->loadFromFile(testWords, gRenderer, 28, true);
	poemWords2 = new LTexture(); poemWords2->loadFromFile(testWords, gRenderer, 28, true);
	poemWords3 = new LTexture(); poemWords3->loadFromFile(testWords, gRenderer, 28, true);
	poemWords4 = new LTexture(); poemWords4->loadFromFile(testWords, gRenderer, 28, true);
	poemWords5 = new LTexture(); poemWords5->loadFromFile(testWords, gRenderer, 28, true);
	poemWords6 = new LTexture(); poemWords6->loadFromFile(testWords, gRenderer, 28, true);
	poemWords7 = new LTexture(); poemWords7->loadFromFile(testWords, gRenderer, 28, true);
	poemWords8 = new LTexture(); poemWords8->loadFromFile(testWords, gRenderer, 28, true);
	poemWords9 = new LTexture(); poemWords9->loadFromFile(testWords, gRenderer, 28, true);
	poemWords10 = new LTexture(); poemWords10->loadFromFile(testWords, gRenderer, 28, true);
	poemWords11 = new LTexture(); poemWords11->loadFromFile(testWords, gRenderer, 28, true);
	poemWords12 = new LTexture(); poemWords12->loadFromFile(testWords, gRenderer, 28, true);
	poemWords13 = new LTexture(); poemWords13->loadFromFile(testWords, gRenderer, 28, true);
	poemWords14 = new LTexture(); poemWords14->loadFromFile(testWords, gRenderer, 28, true);
	poemWords15 = new LTexture(); poemWords15->loadFromFile(testWords, gRenderer, 28, true);
	poemWords16 = new LTexture(); poemWords16->loadFromFile(testWords, gRenderer, 28, true);
	poemWords17 = new LTexture(); poemWords17->loadFromFile(testWords, gRenderer, 28, true);
	poemWords18 = new LTexture(); poemWords18->loadFromFile(testWords, gRenderer, 28, true);
	poemWords19 = new LTexture(); poemWords19->loadFromFile(testWords, gRenderer, 28, true);
	poemWords20 = new LTexture(); poemWords20->loadFromFile(testWords, gRenderer, 28, true);
	poemWords21 = new LTexture(); poemWords21->loadFromFile(testWords, gRenderer, 28, true);
	poemWords22 = new LTexture(); poemWords22->loadFromFile(testWords, gRenderer, 28, true);
	poemWords23 = new LTexture(); poemWords23->loadFromFile(testWords, gRenderer, 28, true);
	poemWords24 = new LTexture(); poemWords24->loadFromFile(testWords, gRenderer, 28, true);
	poemWords25 = new LTexture(); poemWords25->loadFromFile(testWords, gRenderer, 28, true);
	poemWords26 = new LTexture(); poemWords26->loadFromFile(testWords, gRenderer, 28, true);
	poemWords27 = new LTexture(); poemWords27->loadFromFile(testWords, gRenderer, 28, true);
	poemWords28 = new LTexture(); poemWords28->loadFromFile(testWords, gRenderer, 28, true);
	poemWords29 = new LTexture(); poemWords29->loadFromFile(testWords, gRenderer, 28, true);
	poemWords30 = new LTexture(); poemWords30->loadFromFile(testWords, gRenderer, 28, true);
	poemWords31 = new LTexture(); poemWords31->loadFromFile(testWords, gRenderer, 28, true);
	poemWords32 = new LTexture(); poemWords32->loadFromFile(testWords, gRenderer, 28, true);
	poemWords33 = new LTexture(); poemWords33->loadFromFile(testWords, gRenderer, 28, true);

	creditText = new LTexture(); creditText->loadFromFile("A game by Jack Readman. Music by Ewan Knight. Thanks to: Adela, Emily, Ewan, Lewis.", gRenderer, fontSize, true);
	
	if(!poemWords->loadFromFile("Below are two shadows", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords word texture");
	}
	if(!poemWords1->loadFromFile("writing to and over each other in the dark.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords1 word texture");
	}
	if(!poemWords2->loadFromFile("Abraçades al buid:", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords2 word texture");
	}
	if(!poemWords3->loadFromFile("Embraced in the void:", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords3 word texture");
	}
	if(!poemWords4->loadFromFile("només la lluminosa imatge:", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords4 word texture");
	}
	if(!poemWords5->loadFromFile("just the luminous image: ", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords5 word texture");
	}
	if(!poemWords6->loadFromFile("el cos ardent peró, fos.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords6 word texture");
	}
	if(!poemWords7->loadFromFile("the ardent body but, melted", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords7 word texture");
	}
	if(!poemWords8->loadFromFile("here lies  a contradiction", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords8 word texture");
	}
	if(!poemWords9->loadFromFile("to translate, a speaking against", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords9 word texture");
	}
	if(!poemWords10->loadFromFile("a void: an image: then a body", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords10 word texture");
	}
	if(!poemWords11->loadFromFile("emending brings nothing to a person,", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords11 word texture");
	}
	if(!poemWords12->loadFromFile("a poet's lying.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords12 word texture");
	}
	if(!poemWords13->loadFromFile("Dos braços", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords13 word texture");
	}
	if(!poemWords14->loadFromFile("Two arms", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords14 word texture");
	}
	if(!poemWords15->loadFromFile("que s’allarguen sense arribar a encaixar.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords15 word texture");
	}
	if(!poemWords16->loadFromFile("that extend without arriving to fit.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords16 word texture");
	}
	if(!poemWords17->loadFromFile("Dues voluntats", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords17 word texture");
	}
	if(!poemWords18->loadFromFile("Two wills", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords18 word texture");
	}
	if(!poemWords19->loadFromFile("que es saluden.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords19 word texture");
	}
	if(!poemWords20->loadFromFile("that greet themselves.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords20 word texture");
	}
	if(!poemWords21->loadFromFile("here lies  an elegy", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords21 word texture");
	}
	if(!poemWords22->loadFromFile("as anything but", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords22 word texture");
	}
	if(!poemWords23->loadFromFile("recovering", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords23 word texture");
	}
	if(!poemWords24->loadFromFile("you reach across this threshold", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords24 word texture");
	}
	if(!poemWords25->loadFromFile("perhaps only to feel the strain", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords25 word texture");
	}
	if(!poemWords26->loadFromFile("in your own arms", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords26 word texture");
	}
	if(!poemWords27->loadFromFile("Llur esforç inunda l’ànima.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords27 word texture");
	}
	if(!poemWords28->loadFromFile("Their effort inundates the soul.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords28 word texture");
	}
	if(!poemWords29->loadFromFile("here lies  an effort", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords29 word texture");
	}
	if(!poemWords30->loadFromFile("to embrace the life of another", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords30 word texture");
	}
	if(!poemWords31->loadFromFile("in other words", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords31 word texture");
	}
	if(!poemWords32->loadFromFile("an effort to keep you alive", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords32 word texture");
	}
	if(!poemWords33->loadFromFile("in another's words.", gRenderer, fontSize, true))
	{
			printf("Unable to render poemWords33 word texture");
	}


	
	
	
	//Load music
	
	gMusic = Mix_LoadMUS( "soundFiles/Loop idea.wav" );
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	//Load sound effects
	Note1 = new Sounds();
	Note2 = new Sounds();
	Note3 = new Sounds();
	Note4 = new Sounds();
	Note5 = new Sounds();
	Note6 = new Sounds();
	Chord1 = new Sounds();
	Chord2 = new Sounds();
	Chord3 = new Sounds();
	Chord4 = new Sounds();

	Note1->loadFromFile("soundFiles/1.wav" );
	Note2->loadFromFile("soundFiles/2.wav" );
	Note3->loadFromFile("soundFiles/3.wav" );
	Note4->loadFromFile("soundFiles/4.wav" );
	Note5->loadFromFile("soundFiles/5.wav" );
	Note6->loadFromFile("soundFiles/6.wav" );
	Chord1->loadFromFile("soundFiles/Chord 1.wav" );
	Chord2->loadFromFile("soundFiles/Chord 2.wav" );
	Chord3->loadFromFile("soundFiles/Chord 3.wav" );
	Chord4->loadFromFile("soundFiles/Chord 4.wav" );

	
	//error testing
	if (play->mTexture, quit->mTexture, debugTextA->mTexture, debugTextB->mTexture, 
	debugTextC->mTexture, debugTextD->mTexture, debugTextE->mTexture, dotAWords->mTexture,
	dotAWords1->mTexture, dotAWords2->mTexture, dotBWords->mTexture, dotBWords1->mTexture, dotBWords2->mTexture, 
	poemWords->mTexture,poemWords1->mTexture,poemWords2->mTexture,poemWords3->mTexture, poemWords4->mTexture, poemWords5->mTexture, poemWords6->mTexture,
	poemWords7->mTexture, poemWords8->mTexture, poemWords9->mTexture, poemWords10->mTexture, poemWords11->mTexture, poemWords12->mTexture,
	poemWords13->mTexture, poemWords14->mTexture, poemWords15->mTexture, poemWords16->mTexture, poemWords17->mTexture, poemWords18->mTexture, poemWords19->mTexture,
	poemWords20->mTexture, poemWords21->mTexture, poemWords22->mTexture, poemWords23->mTexture, poemWords24->mTexture,
	poemWords25->mTexture, poemWords26->mTexture, poemWords27->mTexture, poemWords28->mTexture, poemWords29->mTexture,poemWords30->mTexture, poemWords31->mTexture,
	poemWords32->mTexture, poemWords33->mTexture, creditText->mTexture == NULL)
	{
		printf("Failed to load texture %s! SDL Error: %s\n", "fontFiles/unifont-12.1.04.ttf", TTF_GetError());
		success = false;
		isDone = true;
	}

	return success;
}

void Game::handleMenuEvents(void) {
SDL_Event event;
//Handle events on queue

while(SDL_PollEvent(&event) != 0)
{
	//User requests quit
	if(event.type == SDL_QUIT)
	{
		isDone = true;
	}
	 //If a key was pressed
	else if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
	{
		
		bool lightUp = true;
		//Adjust the velocity
		switch( event.key.keysym.sym )
		{
			
			case SDLK_LEFT: 

							playSelected = true;
							break;
			case SDLK_RIGHT: 

							 playSelected = false;
							 break;
			case SDLK_RETURN: 
				if (playSelected == true)
				{
					level = 33;
					dot->checkMoveTrigger(true);
					boundBox = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
					dot->checkCollisionNumber(true);
					dot->posInit(SCREEN_WIDTH/4, SCREEN_HEIGHT/2);
					dotB->init(dot->getPosX() + SCREEN_WIDTH, 0, 0, 0);

					changeText(false, ".",false, ".",false, ".",false, ".",false, ".",false, ".");

					break;
				}
				else if (playSelected == false)
				{
					isDone = true;
				}
				break;
			case SDLK_F1:
				if (isFullScreen == false)
				{
					SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
					isFullScreen = true;
				}
				else
				{
					SDL_SetWindowFullscreen(gWindow, 0);
					isFullScreen = false;

				}
				break;
			case SDLK_TAB:
					if (showCredits == false)
						showCredits = true;
					else
						showCredits = false;
				break;

				default: break;
			
			}
		}
		
	}
}

void Game::renderMenu()
{
	if (showCredits == true)
	{
		renderCredits();
	}
	play->render(SCREEN_WIDTH/2 - play->getWidth(), SCREEN_HEIGHT/2 - play->getHeight(), gRenderer);
	quit->render(SCREEN_WIDTH/2 + quit->getWidth(), SCREEN_HEIGHT/2 - quit->getHeight(), gRenderer);

	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	if (playSelected == true)
	{
		SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2) - 50, SCREEN_HEIGHT/2);
	}
	else if (playSelected != true)
	{
		SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH/2 + 70, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2) + 120, SCREEN_HEIGHT/2);
	}
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

};


void Game::playSound()
{ 

		switch(sound)
		{
		case 0:
			Note1->playSound();
			sound = 1;
			break;
		case 1:
			Note2->playSound();
			sound = 2;
			break;
		case 2:
			Note3->playSound();
			sound = 3;
			break;
		case 3:
			Note4->playSound();
			sound = 4;
			break;
		case 4:
			Note5->playSound();
			sound = 5;
			break;
		case 5:
			Note6->playSound();
			sound = 0;
			break;
		case 6:
			Chord1->playSound();
			sound = 0;
			break;
		case 7:
			Chord2->playSound();
			sound = 0;
			break;
		case 8:
			Chord3->playSound();
			sound = 0;
			break;
		case 9:
			Chord4->playSound();
			sound = 0;
			break;
		
			break;
		default:
			break;
		}
			
}


//b is b's collision box, camera on is panning, isColliding decides if B is colliding
void Game::gameLoop(SDL_Rect* b, bool cameraStatus, bool isColliding)
{
	handleEvents(checkingMovement);
	dot->move(b, cameraStatus);
	dotB->move(isColliding);
	if(cameraStatus == true)
	{ 
	dotB->centreDot(dot->getCamera());
	dot->centreDot();
	}
	
	if(showDebug == true)
	{
		changeDebugFigures();
	}
	
	clear();
	render();
	update();
	
}


void Game::clear()
{
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
	SDL_RenderClear(gRenderer);

	
};

void Game::render()
{	
	//render camera centre
	//SDL_SetRenderDrawColor(gRenderer, 0, 100, 0, 0);
	//SDL_RenderFillRect(gRenderer, &boundBox);
	dotB->render(gRenderer);
	dot->render(gRenderer);
	//Load media
	//
	if(showDebug == true)
	{
		renderDebug();
	}	//
	renderTheWords();

};


bool Game::checkAllColliders(void)
{
	for(int i=0; i<17;i++)
	{
		if(dot->checkCollision(dotB->getCollider(i))==true)
		{
			return true;
		}
		
	}
	return false;
}

void Game::update()
{
	//Update screen
	SDL_RenderPresent(gRenderer);
};

bool Game::GetisDone()
{
	return isDone;
};

void Game::renderDebug()
{


	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	debugTextA->render(SCREEN_WIDTH - debugTextA->getWidth(),0, gRenderer);
	debugTextB->render(SCREEN_WIDTH - debugTextB->getWidth(),debugTextA->getHeight(), gRenderer);
	debugTextC->render(SCREEN_WIDTH- debugTextC->getWidth(),debugTextA->getHeight()+debugTextB->getHeight(), gRenderer);
	debugTextD->render(SCREEN_WIDTH - debugTextD->getWidth(),debugTextA->getHeight()+debugTextB->getHeight()+debugTextC->getHeight(), gRenderer);
	debugTextE->render(SCREEN_WIDTH - debugTextE->getWidth(),debugTextA->getHeight()+debugTextB->getHeight()+debugTextC->getHeight()+debugTextD->getHeight(), gRenderer);



	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

	
};

void Game::renderCredits()
{


	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	creditText->render(SCREEN_WIDTH - creditText->getWidth(),0, gRenderer);
	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

	
};

void Game::changeDebugFigures()
{
	//make sure there is something that needs to change
	if (dot->getPosX() != prevDOTX || dot->getPosY() != prevDOTY || dotB->getPosX() != prevDOTBX || dotB->getPosY() != prevDOTY || trigger != prevTRIGGER 
	|| dot->checkCollisionNumber(false) != prevCOLLISIONS || dot->checkMoveTrigger(false) != prevTRIGGER)
	{
	
		
		debugWordsA.str("");
		debugWordsA<<"dotX: "<< dot->getPosX() << " dotY: " << dot->getPosY(); 
		debugWordsB.str("");
		debugWordsB<<"dotBX: "<< dotB->getPosX() << " dotBY: " << dotB->getPosY();
		debugWordsC.str("");
		debugWordsC<<"Collisions: "<< dot->checkCollisionNumber(false); 
		debugWordsD.str("");
		debugWordsD<<"Movements: "<< dot->checkMoveTrigger(false);
		debugWordsE.str("");
		debugWordsE<<"Trigger: "<< trigger;

		if(!debugTextA->loadFromFile(debugWordsA.str().c_str(), gRenderer, 20, true))
		{
			printf("Unable to render debug A texture");
		}	
		if(!debugTextB->loadFromFile(debugWordsB.str().c_str(), gRenderer, 20, true))
		{
			printf("Unable to render debug B texture");
		}	
		
		if(!debugTextC->loadFromFile(debugWordsC.str().c_str(), gRenderer, 20, true))
		{
			printf("Unable to render debug C texture");
		}	
		if(!debugTextD->loadFromFile(debugWordsD.str().c_str(), gRenderer, 20, true))
		{
			printf("Unable to render debug D texture");
		}	
		if(!debugTextE->loadFromFile(debugWordsE.str().c_str(), gRenderer, 20, true))
		{
			printf("Unable to render debug E texture");
		}

	}
	prevDOTBX = dotB->getPosX();
	prevDOTBY = dotB->getPosY();
	prevDOTX = dot->getPosX();
	prevDOTY = dot->getPosY();
	prevCOLLISIONS = dot->checkCollisionNumber(false);
	prevMOVEMENTS = dot->checkMoveTrigger(false);
	prevTRIGGER = trigger;


};

void Game::renderTheWords()
{


	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
	dotAWords->render(SCREEN_WIDTH/2,SCREEN_HEIGHT - wordsHeight*4, gRenderer);
	dotAWords1->render(SCREEN_WIDTH/2,SCREEN_HEIGHT - wordsHeight*3, gRenderer);
	dotAWords2->render(SCREEN_WIDTH/2,SCREEN_HEIGHT - wordsHeight*2, gRenderer);

	dotBWords->render(0,SCREEN_HEIGHT - wordsHeight*4, gRenderer); 
	dotBWords1->render(0,SCREEN_HEIGHT - wordsHeight*3, gRenderer); 
	dotBWords2->render(0,SCREEN_HEIGHT - wordsHeight*2, gRenderer); 


	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

	
};

void Game::changeText(bool textA, std::string theWordsStringA, bool textA1, std::string theWordsStringA1, bool textA2, std::string theWordsStringA2, 
						  bool textB, std::string theWordsStringB, bool textB1, std::string theWordsStringB1, bool textB2, std::string theWordsStringB2 )
{
		if(prevWordsA != theWordsStringA || prevWordsA1 != theWordsStringA1 || prevWordsA2 != theWordsStringA2 || prevWordsB != theWordsStringB ||
		prevWordsB1 != theWordsStringB1 || prevWordsB2 != theWordsStringB2)
		{
			dotATextStream.str("");
			dotATextStream<<theWordsStringA;
			dotATextStream1.str("");
			dotATextStream1<<theWordsStringA1;
			dotATextStream2.str("");
			dotATextStream2<<theWordsStringA2;
		
			if(!dotAWords->loadFromFile(dotATextStream.str().c_str(), gRenderer, fontSize, textA))
			{
				printf("Unable to render dotA word texture");
			}
			if(!dotAWords1->loadFromFile(dotATextStream1.str().c_str(), gRenderer, fontSize, textA1))
			{
				printf("Unable to render dotA word texture 1");
			}		
			if(!dotAWords2->loadFromFile(dotATextStream2.str().c_str(), gRenderer, fontSize, textA2))
			{
				printf("Unable to render dotA word texture 2");
			}	
		
			dotBTextStream.str("");
			dotBTextStream<<theWordsStringB;
			dotBTextStream1.str("");
			dotBTextStream1<<theWordsStringB1;
			dotBTextStream2.str("");
			dotBTextStream2<<theWordsStringB2;
		
		
		
			if(!dotBWords->loadFromFile(dotBTextStream.str().c_str(), gRenderer, fontSize, textB))
			{
				printf("Unable to render dotB word texture");
			}	
			if(!dotBWords1->loadFromFile(dotBTextStream1.str().c_str(), gRenderer, fontSize, textB1))
			{
				printf("Unable to render dotB word texture 1");
			}	
			if(!dotBWords2->loadFromFile(dotBTextStream2.str().c_str(), gRenderer, fontSize, textB2))
			{
				printf("Unable to render dotB word texture 2");
			}	
			//if there is some new text, play a new sound


				playSound();
		}
				
			
			prevWordsA = theWordsStringA;
			prevWordsA1 = theWordsStringA1;
			prevWordsA2 = theWordsStringA2;
			prevWordsB = theWordsStringB;
			prevWordsB1 = theWordsStringB1;
			prevWordsB2 = theWordsStringB2;
		

};

void Game::dotBIdle()
{
			if(idleVelX > 0 && idleVelY > 0)
		{
			for(int i = 0; i<squareLength; i++)
			{
				dotB->init(dotB->getPosX(),dotB->getPosY(), idleVelX, idleVelY);
				gameLoop(dotB->getRect(), cameraOn, false);

			}
			idleVelX = -idleSpeed;
		}
			if(idleVelX > 0 && idleVelY < 0)
		{
			for(int i = 0; i<squareLength; i++)
			{
				dotB->init(dotB->getPosX(),dotB->getPosY(), idleVelX, idleVelY);
				gameLoop(dotB->getRect(), cameraOn, false);

			}
			idleVelY = idleSpeed;
		}
			if(idleVelX < 0 && idleVelY > 0)
		{
			for(int i = 0; i<squareLength; i++)
			{
				dotB->init(dotB->getPosX(),dotB->getPosY(), idleVelX, idleVelY);
						gameLoop(dotB->getRect(), cameraOn, false);

			}
			idleVelY = -idleSpeed;
		}
			if(idleVelX < 0 && idleVelY < 0)
		{
			for(int i = 0; i<squareLength; i++)
			{
				dotB->init(dotB->getPosX(),dotB->getPosY(), idleVelX, idleVelY);
						gameLoop(dotB->getRect(), cameraOn, false);

			}
			idleVelX = idleSpeed;
		}
	
}

void Game::dotBDance(int xDirectionMultiplier, int yDirectionMultiplier)
{
		if(idleVelX > 0 && idleVelY > 0)
		{
			for(int i = 0; i<squareLength; i++)
			{
				dotB->init(dotB->getPosX(),dotB->getPosY(), idleVelX, idleVelY);
				handleEvents(checkingMovement);
				//dot->move(dotB->getRect(), false);
				dotB->move(false);
				clear();
				render();
				update();
			}
			idleVelX = -idleSpeed * xDirectionMultiplier;
		}
		if(idleVelX > 0 && idleVelY < 0)
		{
			for(int i = 0; i<squareLength; i++)
			{
				dotB->init(dotB->getPosX(),dotB->getPosY(), idleVelX, idleVelY);
				handleEvents(checkingMovement);
				//dot->move(dotB->getRect(), false);
				dotB->move(false);
				clear();
				render();
				update();
			}
			idleVelY = idleSpeed*yDirectionMultiplier;
		}
			if(idleVelX < 0 && idleVelY > 0)
		{
			for(int i = 0; i<squareLength; i++)
			{
				dotB->init(dotB->getPosX(),dotB->getPosY(), idleVelX, idleVelY);
				handleEvents(checkingMovement);
				//dot->move(dotB->getRect(), false);
				dotB->move(false);
				clear();
				render();
				update();
			}
			idleVelY = -idleSpeed*yDirectionMultiplier;
		}
		if(idleVelX < 0 && idleVelY < 0)
		{
			for(int i = 0; i<squareLength; i++)
			{
				dotB->init(dotB->getPosX(),dotB->getPosY(), idleVelX, idleVelY);
				handleEvents(checkingMovement);
				//dot->move(dotB->getRect(), false);
				dotB->move(false);
				clear();
				render();
				update();
			}
			idleVelX = idleSpeed* xDirectionMultiplier;
		}
	
	
	
	

}


void Game::setTimeVariables(void)
{
	timeBefore = SDL_GetTicks();
};

bool Game::hasTimePassed(Uint32 timePassed)
{
	timeNow = SDL_GetTicks();
	if(timeNow > timeBefore + timePassed)
	{
		timeBefore = timeNow;
		return true;
	}
	return false;
};

void Game::levelSelect(void)
{
	switch( level )
	{	
	case 0:
		handleMenuEvents();
		clear();
		renderMenu();
		update();
		break;
	case 33:
	checkingMovement = true;
	changeText(false, ",",false, ",",false, ",",false, ",",false, ",",false, ",");
		gameLoop(dotB->getRect(), cameraOff, false);
		if(dot->checkMoveTrigger(false) > 20)
		{
			if(dot->getPosX() > SCREEN_WIDTH/2 - 15 && dot->getPosX() < SCREEN_WIDTH/2 + 15 && dot->getPosY() > SCREEN_HEIGHT/2 - 15 && dot->getPosY() < SCREEN_HEIGHT/2 + 15)
			{
				dot->checkMoveTrigger(true);
				dot->checkCollisionNumber(true);
				changeText(true, "you stop at the threshold of a door", false, ".", false, ".",  false, ".", false, ".", false, ".");

				level = 1;
			}
		}
		break;

	case 1:
		checkingMovement = true;
		gameLoop(dotB->getRect(), cameraOn, false);
		
		dotB->init(dot->getPosX() + SCREEN_WIDTH, 0, 0, 0);
	
		if (dot->checkMoveTrigger(false) > 5 && dot->checkMoveTrigger(false) < 14)
		{
			changeText(true, "you stop at the threshold of a door", true, "on the other side you", false, ".",  false, ".", false, ".", false, ".");

		}
		if (dot->checkMoveTrigger(false) > 15 && dot->checkMoveTrigger(false) < 20)
		{
			changeText(true, "you stop at the threshold of a door", true, "on the other side you", true, "expect some encounter",  false, ".", false, ".", false, ".");
		}
		if (dot->checkMoveTrigger(false) > 21 && dot->checkMoveTrigger(false) < 25)
		{
			changeText(true, "a boss or beloved or", false, ".", false, ".",  false, ".", false, ".", false, ".");

		}
		if (dot->checkMoveTrigger(false) > 26 && dot->checkMoveTrigger(false) < 30)
		{
			changeText(true, "a boss or beloved or", true, "something or other", false, ".",  false, ".", false, ".", false, ".");
			
		}
		if (dot->checkMoveTrigger(false) > 31 && dot->checkMoveTrigger(false) < 35)
		{
			changeText(false, ".", false, ".", false, ".",  false, ".", false, ".", false, ".");
			
		}
		if (dot->checkMoveTrigger(false) > 36 && dot->checkMoveTrigger(false) < 40)
		{
		
			changeText(true, "Concepcio Casanova was a Catalan writer", false, ".", false, ".",  false, ".", false, ".", false, ".");
		}
		if (dot->checkMoveTrigger(false) > 41 && dot->checkMoveTrigger(false) < 45)
		{
			changeText(true, "Concepcio Casanova was a Catalan writer", true, "whose poetry and essays appeared in numerous", false, ".", false, ".", false, ".", false, ".");
		

		}
		if (dot->checkMoveTrigger(false) > 46 && dot->checkMoveTrigger(false) < 50)
		{
			changeText(true, "Concepcio Casanova was a Catalan writer", true, "whose poetry and essays appeared in numerous", true, "magazines between 1924 and 1936.", false, ".",  false, ".", false, ".");

		}
		if (dot->checkMoveTrigger(false) > 51 && dot->checkMoveTrigger(false) < 55)
		{
						changeText(true, "Largely forgotten since, to read her is to re", false, ".", false, ".",  false, ".", false, ".", false, ".");

		}
		if (dot->checkMoveTrigger(false) > 56 && dot->checkMoveTrigger(false) < 60)
		{
						changeText(true, "Largely forgotten since, to read her is to re",true, "cover her. In the first poem of her only", false, ".",  false, ".", false, ".", false, ".");

		}
		if (dot->checkMoveTrigger(false) > 61 && dot->checkMoveTrigger(false) < 65)
		{
			changeText(true, "Largely forgotten since, to read her is to re",true, "cover her. In the first poem of her only", true, "collection, Poemes en el Temps, her speaker's", false, ".",  false, ".", false, ".");

		}
		if (dot->checkMoveTrigger(false) > 66 && dot->checkMoveTrigger(false) < 70)
		{
						changeText(true, "arms get tired pushing together", false, ".", false, ".",  false, ".", false, ".", false, ".");


		}
		if (dot->checkMoveTrigger(false) > 71 && dot->checkMoveTrigger(false) < 75)
		{
					changeText(true, "arms get tired pushing together", true, "the eternal and the fleeting.", false, ".",  false, ".", false, ".", false, ".");

		}
				if (dot->checkMoveTrigger(false) > 76 && dot->checkMoveTrigger(false) < 80)
		{
				changeText(false, ".", false, ".", false, ".",  false, ".", false, ".", false, ".");


		}
		

		
		if (dot->checkMoveTrigger(false) > 81)
		{
			
			level = 2;
			dot->checkMoveTrigger(true);
			checkingMovement = false;

		};
		break;
	case 2:
	//spawn dotb
		if(dot->getVelX() > 0 && dot->getVelY() == 0 )
		{
			dotB->init(dot->getPosX() + SCREEN_WIDTH ,dot->getPosY(), 0, 0);
		}
		else if(dot->getVelX() < 0 && dot->getVelY() == 0 )
		{
			dotB->init(dot->getPosX() - SCREEN_WIDTH,dot->getPosY(), 0, 0);
		}
		else if(dot->getVelX() == 0 && dot->getVelY() > 0 )
		{
			dotB->init(dot->getPosX(),dot->getPosY() + SCREEN_HEIGHT, 0, 0);
		}
		else if(dot->getVelX() == 0 && dot->getVelY() < 0 )
		{
			dotB->init(dot->getPosX(),dot->getPosY() - SCREEN_HEIGHT, 0, 0);
		}
		else if (dot->getVelX() > 0 && dot->getVelY() > 0)
		{
			dotB->init(dot->getPosX() + SCREEN_WIDTH, dot->getPosY() + SCREEN_HEIGHT, 0, 0);
		}
		else if (dot->getVelX() > 0 && dot->getVelY() < 0)
		{
			dotB->init(dot->getPosX() + SCREEN_WIDTH, dot->getPosY() - SCREEN_HEIGHT, 0, 0);
		}
		else if (dot->getVelX() < 0 && dot->getVelY() > 0)
		{
			dotB->init(dot->getPosX() - SCREEN_WIDTH, dot->getPosY() + SCREEN_HEIGHT, 0, 0);
		}
		else if (dot->getVelX() < 0 && dot->getVelY() < 0)
		{
			dotB->init(dot->getPosX() - SCREEN_WIDTH, dot->getPosY() - SCREEN_HEIGHT, 0, 0);
		}
		else
		{
			dotB->init(dot->getPosX() + SCREEN_WIDTH ,dot->getPosY(), 0, 0);
		}
		gameLoop(dotB->getRect(), cameraOn, false);
		level = 3;
		
		break;
	case 3:
		//if dotb is onscreen, idle
		if(dotB->getPosX() < SCREEN_WIDTH || dotB->getPosX() > 0 || dotB->getPosY() > 0 || dotB->getPosY() < SCREEN_HEIGHT)
		{ 
			dotBIdle();
			checkingMovement = true;
		}
		dotB->init(dotB->getPosX(), dotB->getPosY(),0, 0);

		gameLoop(dotB->getRect(), cameraOn, false);

		if (dot->checkMoveTrigger(false) > 0 && dot->checkMoveTrigger(false) < 5)
		{
			changeText(true, "I", false, ".", false, ".",  true, "I", false, ".", false, ".");
		}
		if (dot->checkMoveTrigger(false) > 5 && dot->checkMoveTrigger(false) < 12)
		{
			changeText(true, "I", true, "I that have enervated the arms to unite", false, ".",  true, "I", true, "Jo que he enervat els braços per unir", false, ".");
		}
		if (dot->checkMoveTrigger(false) > 12 && dot->checkMoveTrigger(false) < 16)
		{
			changeText(true, "I that have enervated the arms to unite", true, "the star that lingers,", false, ".", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", false, ".");
		}
		if (dot->checkMoveTrigger(false) > 16 && dot->checkMoveTrigger(false) < 21)
		{
			changeText(true, "I that have enervated the arms to unite", true, "the star that lingers,", true, "and the wind that has to die.", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 21 && dot->checkMoveTrigger(false) < 24)
		{
			changeText(true, "Her speaker sits at the boundary", false, ".", false, ".", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 24 && dot->checkMoveTrigger(false) < 28)
		{
			changeText(true, "Her speaker sits at the boundary", true, "of two vast irresolvable concepts", false, ".", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 28 && dot->checkMoveTrigger(false) < 32)
		{
			changeText(true, "Her speaker sits at the boundary", true, "of two vast irresolvable concepts", true, "and attempts to push them together.", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 32 && dot->checkMoveTrigger(false) < 36)
		{
			changeText(true, "The manoeuvre does not necessarily succeed.", false, ".", false, ".", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 36 && dot->checkMoveTrigger(false) < 40)
		{
			changeText(true, "The manoeuvre does not necessarily succeed.", true, "The 'Jo' enervates the arms with the", false, ".", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 40 && dot->checkMoveTrigger(false) < 44)
		{
			changeText(true, "The manoeuvre does not necessarily succeed.", true, "The 'Jo' enervates the arms with the", true, "intention of uniting the star and the wind,", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 44 && dot->checkMoveTrigger(false) < 48)
		{
			changeText(true, "whether they do unite is ambiguous.", false, ".", false, ".", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 48 && dot->checkMoveTrigger(false) < 52)
		{
			changeText(true, "whether they do unite is ambiguous.", true, "Her poems often play with this incipient action,", false, ".", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 52 && dot->checkMoveTrigger(false) < 56)
		{
			changeText(true, "whether they do unite is ambiguous.", true, "Her poems often play with this incipient action,", true, "whereby effort towards something", true, "Jo que he enervat els braços per unir", true, "l'estrella que perdura,", true, "i el vent que ha de morir.");
		}
		if (dot->checkMoveTrigger(false) > 56 && dot->checkMoveTrigger(false) < 60)
		{
			changeText(true, "does not mean reaching it.", false, ".",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 60 && dot->checkMoveTrigger(false) < 64)
		{
			changeText(true, "An image in the collection's penultimate", false, ".", false, ".", false, ".", false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 64 && dot->checkMoveTrigger(false) < 68)
		{
			changeText(true, "An image in the collection's penultimate", true, "poem captures this, its pauses and line", false, ".", false, ".", false, ".", false, ".");
		}
		if (dot->checkMoveTrigger(false) > 68 && dot->checkMoveTrigger(false) < 72)
		{
			changeText(true, "An image in the collection's penultimate", true, "poem captures this, its pauses and line", true, "breaks force a stunted, jerking rhythm:", false, ".", false, ".", false, ".");
		}
		if (dot->checkMoveTrigger(false) > 72 && dot->checkMoveTrigger(false) < 76)
		{
			changeText(true, "and we dance refusing", false, ".", false, ".", true, "i dancem refusant", false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 76 && dot->checkMoveTrigger(false) < 80)
		{
			changeText(true, "and we dance refusing", true, "the gesture, continuously", false, ".", true, "i dancem refusant", true, "el gest, continuament",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 80 && dot->checkMoveTrigger(false) < 84)
		{
			changeText(false, ".", false, ".", false, ".", false, ".", false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 84 && dot->checkMoveTrigger(false) < 88)
		{
			changeText(true, "without crossing the threshold", false, ".", false, ".", false, ".", false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 92 && dot->checkMoveTrigger(false) < 96)
		{
			changeText(true, "without crossing the threshold", true, "an encounter never happens", false, ".", false, ".", false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 96 && dot->checkMoveTrigger(false) < 100)
		{
			changeText(true, "without crossing the threshold", true, "an encounter never happens", true, "you may idle at arm's reach", false, ".", false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 100 && dot->checkMoveTrigger(false) < 104)
		{
			changeText(true, "without crossing the threshold", true, "an encounter never happens", true, "you may idle at arm's reach patiently", false, ".", false, ".",false, ".");
			dot->checkCollisionNumber(true);
		}
		if (dot->checkMoveTrigger(false) > 104 && dot->checkMoveTrigger(false) < 108)
		{
			changeText(true, "without crossing the threshold", true, "an encounter never happens", true, "you may idle at arm's reach patiently forever", false, ".", false, ".",false, ".");
		}

		
		

		if (dot->checkMoveTrigger(false) > 104)
		{
			//if dotB gets within 1/20 of the screen from dot
			if(dotB->getPosX() > SCREEN_WIDTH/2 - SCREEN_WIDTH/20 && dotB->getPosX() < SCREEN_WIDTH/2 + SCREEN_WIDTH/20 && dotB->getPosY() > SCREEN_HEIGHT/2 -SCREEN_HEIGHT/20 && dotB->getPosY() < SCREEN_HEIGHT/2 + SCREEN_HEIGHT/20)
			{
				changeText(true, "XXXI", false, ".", false, ".", true, "XXXI", false, ".", false, ".");
				sound = 6;
				playSound();
				level = 4;
			}
		}
		//respawn dotB if it has left
		if (dot->getPosX() > dotB->getPosX() + 1.5*SCREEN_WIDTH || dot->getPosX() < dotB->getPosX() - 1.5*SCREEN_WIDTH 
		|| dot->getPosY() > dotB->getPosY() + 1.5*SCREEN_HEIGHT || dot->getPosY() < dotB->getPosY() - 1.5*SCREEN_HEIGHT)
		{
			level = 2;
		}	
		if(dot->checkMoveTrigger(false) < 104)
		{
			//if dotB gets within 1/6 of the screen size from dot...
			if(dotB->getPosX() > SCREEN_WIDTH/6 && dotB->getPosX() < SCREEN_WIDTH*5/6 && dotB->getPosY() > SCREEN_HEIGHT/6 && dotB->getPosY() < SCREEN_HEIGHT*5/6)
			{
				level = 32;
			} 
		}
		dot->checkCollisionNumber(false);
		break;
	case 32:
		//dotB escapes to nearest screen edge
		checkingMovement = false;
		gameLoop(dotB->getRect(), cameraOn, false);
		if(dotB->getPosX() > SCREEN_WIDTH/2)
		{
			dotB->init(dotB->getPosX(), dotB->getPosY(), dotB->getDOT_VEL()*2, 0);
		} 
		if(dotB->getPosX() < SCREEN_WIDTH/2)
		{
			dotB->init(dotB->getPosX(), dotB->getPosY(), dotB->getDOT_VEL()*-2, 0);
		} 
		if(dotB->getPosY() > SCREEN_HEIGHT/2)
		{
			dotB->init(dotB->getPosX(), dotB->getPosY(), 0 , dotB->getDOT_VEL()*2);
		} 
		if(dotB->getPosY() < SCREEN_HEIGHT/2)
		{
			dotB->init(dotB->getPosX(), dotB->getPosY(), 0, dotB->getDOT_VEL()*-2);
		} 
		//respawn dotB if player leaves
		if (dot->getPosX() > dotB->getPosX() + 1.5*SCREEN_WIDTH || dot->getPosX() < dotB->getPosX() - 1.5*SCREEN_WIDTH 
		|| dot->getPosY() > dotB->getPosY() + 1.5*SCREEN_HEIGHT || dot->getPosY() < dotB->getPosY() - 1.5*SCREEN_HEIGHT)
		{
			level = 2;
		}
		break;
	case 4:
		//dotB moves right quickly
		dotB->init(dotB->getPosX(), dotB->getPosY(), dot->getDOT_VEL()*1.3, 0);
		for (int i=0; i<100; i++)
		{
			gameLoop(dotB->getRect(), cameraOn, false);
		}
				changeText(true, "XXXI", true, "This irremediable loss drains me...", false, ".", true, "XXXI", true, "Irremeiable pèrdua que m’enerva...", false, ".");
		dot->checkCollisionNumber(true);
		level = 5;
		break;
	case 5:
		//dotB moves right slowly
		dotB->init(dotB->getPosX(), dotB->getPosY(), dot->getDOT_VEL()*0.99, 0);
		gameLoop(dotB->getRect(), cameraOn, false);
		level = 6;
		break;
	case 6:
		//keeps dotB onscreen
		if(dotB->getPosX() > dot->getPosX() + SCREEN_WIDTH)
		{
			dotB->init(dot->getPosX() + SCREEN_WIDTH, dot->getPosY(), dot->getVelX()*0.99, 0);
		}
		//check collisions
		if (dot->checkCollisionNumber(false) == 1 )
		{
				changeText(true, "This irremediable loss drains me...", true, "-Hush you, if he came back now would you", false, ".", true, "Irremeiable pèrdua que m’enerva...", true, "-Tu, digues baix, però, si ara tornés", false, ".");
		}
		if (dot->checkCollisionNumber(false) == 3 )
		{
			changeText(true, "This irremediable loss drains me...", true, "-Hush you, if he came back now would you", true, "give him your heart or just your mind?", true, "Irremeiable pèrdua que m’enerva...", true, "-Tu, digues baix, però, si ara tornés", true, "el cor li donaries, o el pensament, només?");

		}

		if (dot->checkCollisionNumber(false) == 5)
		{
				changeText(true, "Another manoeuvre in her work is for", false, ".", false, ".",true, "Irremeiable pèrdua que m’enerva...", true, "—Tu, digues baix, però, si ara tornés", true, "el cor li donaries, o el pensament, només?");
		}
		if (dot->checkCollisionNumber(false) == 7)
		{
				changeText(true, "Another manoeuvre in her work is for", true, "her speaker's voice to split in two,", false, ".",true, "Irremeiable pèrdua que m’enerva...", true, "—Tu, digues baix, però, si ara tornés", true, "el cor li donaries, o el pensament, només?");
		}
		if (dot->checkCollisionNumber(false) == 9)
		{
				changeText(true, "Another manoeuvre in her work is for", true, "her speaker's voice to split in two,", true, "one voice arguing with the other in a",true, "Irremeiable pèrdua que m’enerva...", true, "—Tu, digues baix, però, si ara tornés", true, "el cor li donaries, o el pensament, només?");
		}
		if (dot->checkCollisionNumber(false) == 11)
		{
				changeText(true, "struggle to synthesise two conflicting ideas.", false, ".", false, ".",true, "Irremeiable pèrdua que m’enerva...", true, "—Tu, digues baix, però, si ara tornés", true, "el cor li donaries, o el pensament, només?");
		}
		if (dot->checkCollisionNumber(false) == 13)
		{
				changeText(true, "struggle to synthesise two conflicting ideas.", true, "Over a line her 'me' is berated by a sudden", false, ".",true, "Irremeiable pèrdua que m’enerva...", true, "—Tu, digues baix, però, si ara tornés", true, "el cor li donaries, o el pensament, només?");
		}
		if (dot->checkCollisionNumber(false) == 15)
		{
				changeText(true, "struggle to synthesise two conflicting ideas.", true, "Over a line her 'me' is berated by a sudden", true, "'tu' that disrupts the self-serious",true, "Irremeiable pèrdua que m’enerva...", true, "—Tu, digues baix, però, si ara tornés", true, "el cor li donaries, o el pensament, només?");
		}
		if (dot->checkCollisionNumber(false) == 17)
		{
				changeText(true, "egotism of the singular, lyric voice.", false, ".", false, ".",true, "Irremeiable pèrdua que m’enerva...", true, "—Tu, digues baix, però, si ara tornés", true, "el cor li donaries, o el pensament, només?");
		}


		
		//change direction
		if (dot->checkCollisionNumber(false) > 19)
		{
			level = 7;
			sound = 7;
			dot->checkCollisionNumber(true);
			changeText(true, "But her plural voices are argumentative.", false, ".", false, ".", false, ".", false,  ".", false, ".");

			break;
		}
		//dotB runs away
		if((checkAllColliders() == true) || dot->getPosX() > dotB->getPosX())
		{
			dotB->init(dotB->getPosX(), dotB->getPosY(), dot->getVelX()*1.5, dot->getVelY()*0.7);
			for(int i=0;i<30; i++)
			{
				gameLoop(dotB->getRect(), cameraOn, false);
			}
			break;
		}
		//returns dotB to lower speed
		if (dotB->getVelX() != dot->getDOT_VEL()*0.99)
		{
			level = 5;
			break;
		}
		dot->checkCollisionNumber(false);
		break;
	case 7:
		//dotb moves down quickly
		dotB->init(dotB->getPosX(), dotB->getPosY(), 0, dot->getDOT_VEL()*1.2);
		
	
		for (int i=0; i<100; i++)
		{

			gameLoop(dotB->getRect(), cameraOn, false);
		}
		level = 8;
		break;
	case 8:
		//dotb slows
		dotB->init(dotB->getPosX(), dotB->getPosY(), 0, dot->getDOT_VEL()*0.99);
		gameLoop(dotB->getRect(), cameraOn, false);
		
		level = 9;
		break;
	case 9:
		if(dotB->getPosY() > dot->getPosY() + SCREEN_HEIGHT)
		{
			dotB->init(dot->getPosX(), dot->getPosY() + SCREEN_HEIGHT, 0, dot->getVelY()*0.99);
		}
		if (dot->checkCollisionNumber(false) == 1 )
		{
			changeText(true, "But her plural voices are argumentative.", false, ".", false, ".", false, ".", false,  ".", false, ".");
		}
		if (dot->checkCollisionNumber(false) == 3 )
		{
			changeText(true, "But her plural voices are argumentative.", true, "Even her essays take the form of dialogues", false, ".", false, ".", false,  ".", false, ".");
		}
		if (dot->checkCollisionNumber(false) == 4)
		{
			changeText(true, "But her plural voices are argumentative.", true, "Even her essays take the form of dialogues", true, "that read like bickering. ", false, ".", false,  ".", false, ".");
		}
		if (dot->checkCollisionNumber(false) == 5)
		{
			changeText(true,"In one she compares Dostoyevsky, the", true, "'semi-barbarian' to Tolstoy the ", false, ".",false, ".",true, "semibàrbar",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 7)
		{
			changeText(true,"In one she compares Dostoyevsky, the", true, "'semi-barbarian' to Tolstoy the", true, "'superior European', but stops abruptly",false, ".",true, "semibàrbar",true, "la superioritat europea");
		}
		if (dot->checkCollisionNumber(false) == 9)
		{
			changeText(true, "mid-sentence due seemingly to a second", false, ".",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 11)
		{
			changeText(true, "mid-sentence due seemingly to a second", true, "voice sniggering in the background",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 13)
		{
			changeText(true,"Well, what are you laughing at now?", false, ".", false, ".",true, "Bé, de qué rieu ara?",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 15)
		{
			changeText(true,"Well, what are you laughing at now?", true, "Isn't that at all right?", false, ".",true, "Bé, de qué rieu ara?",true, "No és ben bé aixó?",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 17)
		{
			changeText(true, "To which the second voice replies,", false, ".",false, ".",false, ".",false, ".",false, ".");
		}
		
		if (dot->checkCollisionNumber(false) == 19)
		{
			changeText(true, "To which the second voice replies,",true,"What can I tell you!", false, ".", false, ".", true, "Qué us diré!",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 21)
		{
			changeText(true, "To which the second voice replies,",true,"What can I tell you!", true, "I'm amused...", false, ".", true, "Qué us diré!",true, "Em fa gracia...");
		}
		if (dot->checkCollisionNumber(false) == 23)
		{
			changeText(true,"Later the second voice expounds on Hamlet and", false, ".", false, ".",false, ".", false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 25)
		{
			changeText(true,"Later the second voice expounds on Hamlet and", true, "the tragic hero's 'fear of the infinite.'", false, ".",false, ".", true, "esglai de l’infinit",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 27)
		{
			changeText(true,"Later the second voice expounds on Hamlet and", true, "the tragic hero's 'fear of the infinite.'", true, "The first voice cuts in",false, ".", true, "esglai de l’infinit",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 29)
		{
			changeText( true, "No need to ramble on!", false, ".",false, ".",true, "No s’hi val a divagar!",false, ".", false, ".");
		}
		if (dot->checkCollisionNumber(false) == 31)
		{
			changeText(true,"She writes, refusing. Reverence for lofty,", false, ".", false, ".",false, ".",false, ".", false, ".");
		}
		if (dot->checkCollisionNumber(false) == 33)
		{
			changeText(true,"She writes, refusing. Reverence for lofty,", true,"male writers collapses into irony,", false, ".", false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 35)
		{
			changeText(true,"She writes, refusing. Reverence for lofty,", true,"male writers collapses into irony,", true, "but she is checking her own habit for obsequy.", false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 37)
		{
			changeText(true,"Revealed is her own composition process,", false, ".", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 39)
		{
			changeText(true,"Revealed is her own composition process,", true, "to read her is to read with her", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 41)
		{
			changeText(true,"Revealed is her own composition process,", true, "to read her is to read with her", true, "as she lingers at the margins ready to",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 43)
		{
			changeText(true , "correct herself. This also means that", false, ".", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 45)
		{
			changeText(true , "correct herself. This also means that", true, "her essays resist singular conclusions- they", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 47)
		{
			changeText(true , "correct herself. This also means that", true, "her essays resist singular conclusions- they", true, "always end in questions or vacillation.",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 49)
		{
			changeText(true , "Fragmentary and ironic, quick to", false, ".", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 51)
		{
			changeText(true , "Fragmentary and ironic, quick to", true, "mock her own profuseness, any", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkCollisionNumber(false) == 53)
		{
			changeText(true , "Fragmentary and ironic, quick to", true, "mock her own profuseness, any", true, "subjectivity is always unstable.",false, ".",false, ".",false, ".");
		}
		
		
		
		//this will advance the level
		if (dot->checkCollisionNumber(false) > 55)
		{
			level = 10;
			dot->checkCollisionNumber(true);
			break;
		}
		//if dot collides with dotb, dotb evades
		if((checkAllColliders() == true) || dot->getPosY() > dotB->getPosY())
		{
			dotB->init(dotB->getPosX(), dotB->getPosY(), dot->getVelX()*0.7, dot->getVelY()*1.5);
			for(int i=0;i<30; i++)
			{
			gameLoop(dotB->getRect(), cameraOn, false);
			}
			break;
		}
		//dotB returns to normal velocity
		if (dotB->getVelY() != dot->getDOT_VEL()*0.99)
		{
			level = 8;
			break;
		}
	case 10:
	//dotB speeds up 
			changeText(true,"So that her work often escapes", false, ".", false, ".",false, ".",false, ".",false, ".");
			dotB->init(dotB->getPosX(), dotB->getPosY() , 0, dot->getDOT_VEL()*1.5);
			gameLoop(dotB->getRect(), cameraOn, false);
			
			level = 11;
			break;
	case 11:
	//dotB leaves screen, camera becomes static
			if (dotB->getPosY() > dot->getPosY() + SCREEN_HEIGHT/2)
			{
				
				changeText(true,"So that her work often escapes", true, "                         me.", false, ".",false, ".",false, ".",false, ".");
				sound = 8;
				playSound();
				level = 12;
				setTimeVariables();
				dotB->init(10000,10000, 0, 0);


			}
			gameLoop(dotB->getRect(), cameraOn, false);
			break;
			//BEGIN DEBUG HERE
	case 12:
			if(hasTimePassed(2000) )
			{
				level = 13;
				dot->checkCollisionNumber(true);
				dot->checkMoveTrigger(true);
				checkingMovement = true;
			}
			gameLoop(dotB->getRect(), cameraOff, false);
			
			break;
	case 13:
		gameLoop(dotB->getRect(), cameraOff, false);
		if (dot->checkMoveTrigger(false) > 5 && dot->checkMoveTrigger(false) < 8)
		{
			changeText(true,"patience", false, ".", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 8 && dot->checkMoveTrigger(false) < 13)
		{
			changeText(true,"patience", true, "sometimes called solitaire", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 14 && dot->checkMoveTrigger(false) < 19)
		{
			changeText(true,"patience", true, "sometimes called solitaire", true, "a game for one player",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 20 && dot->checkMoveTrigger(false) < 23)
		{
			changeText(true,"by shuffling the cards", false, ".", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 23 && dot->checkMoveTrigger(false) < 27)
		{
			changeText(true,"by shuffling the cards", true, "chance produces a new challenge each game", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 27 && dot->checkMoveTrigger(false) < 32)
		{
			changeText(true,"by shuffling the cards", true, "chance produces a new challenge each game", true, "complexity can also produce a challenge",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 32 && dot->checkMoveTrigger(false) < 35)
		{
			changeText(true,"like the limited solutions of peg solitaire", false, ".", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 35 && dot->checkMoveTrigger(false) < 38)
		{
			changeText(true,"like the limited solutions of peg solitaire",true,"without knowing a solution ", false, ".", false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 38 && dot->checkMoveTrigger(false) < 43)
		{
			changeText(true,"like the limited solutions of peg solitaire",true,"without knowing a solution", true, "your repeated efforts to solve the puzzle seem like", false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 43 && dot->checkMoveTrigger(false) < 46)
		{
			changeText(true,"individual rounds against the game designer",false, ".",false, ".",false, ".", false, ".", false, ".");
		}
		if (dot->checkMoveTrigger(false) > 46 && dot->checkMoveTrigger(false) < 51)
		{
			changeText(true,"individual rounds against the game designer",true, "who beats you every time",false, ".",false, ".", false, ".", false, ".");
		}
		if (dot->checkMoveTrigger(false) > 51 && dot->checkMoveTrigger(false) < 54)
		{
			changeText(true,"you play against this designer", true, "until you find a solution", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 54 && dot->checkMoveTrigger(false) < 59)
		{
			changeText(true,"you play against this designer", true, "until you find a solution", true, "after which the game stops being a game at all",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 59 && dot->checkMoveTrigger(false) < 62)
		{
			changeText(true,"as you sit alone", false, ".", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 62 && dot->checkMoveTrigger(false) < 65)
		{
			changeText(true,"as you sit alone", true, "a second player is conjured", false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 65 && dot->checkMoveTrigger(false) < 70)
		{
			changeText(true,"as you sit alone", true, "a second player is conjured", true, "from the game's rules",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 70 && dot->checkMoveTrigger(false) < 76)
		{
			changeText(true, "of chance or complexity",false, ".",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 76 && dot->checkMoveTrigger(false) < 79)
		{
			changeText(true, "with no player two you play against nothing",false, ".",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 79 && dot->checkMoveTrigger(false) < 82)
		{
			changeText(true, "with no player two you play against nothing",true, "solitaire",true, "patience",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 82 && dot->checkMoveTrigger(false) < 85)
		{
			changeText(true, "with no player two you play against nothing",true, "solitaire from solus",true, "patience from patientia",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 85 && dot->checkMoveTrigger(false) < 89)
		{
			changeText(true, "with no player two you play against nothing",true, "solitaire from solus  alone",true, "patience from patientia  suffering",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 89 && dot->checkMoveTrigger(false) < 93)
		{
			changeText(false, ".",false, ".",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 94 && dot->checkMoveTrigger(false) < 107)
		{
			changeText(true, "In the longest poem of the collection, her",false, ".",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 108 && dot->checkMoveTrigger(false) < 111)
		{
			changeText(true, "In the longest poem of the collection, her",true, "speaker oscillates between lust and faith.",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 112 && dot->checkMoveTrigger(false) < 117)
		{
			changeText(true, "In the longest poem of the collection, her",true, "speaker oscillates between lust and faith.",true, "Two ways of reaching out to an other,",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 117 && dot->checkMoveTrigger(false) < 119)
		{
			changeText(true, "whom the speaker follows like a shadow",false, ".",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 120 && dot->checkMoveTrigger(false) < 123)
		{
			changeText(true, "whom the speaker follows like a shadow",true, "lingering at the poem's edge",false, ".",false, ".",false, ".",false, ".");
		}
		if (dot->checkMoveTrigger(false) > 124 && dot->checkMoveTrigger(false) < 127)
		{
			changeText(true, "whom the speaker follows like a shadow",true, "lingering at the poem's edge",true, "feigning offence.",false, ".",false, ".",false, ".");
			dot->checkCollisionNumber(true);
			trigger = 0;
		}


		if(dot->checkMoveTrigger(false) > 130)
		{
			if(dot->checkCollisionNumber(false) > 40)
			{
				dot->checkCollisionNumber(true);
				trigger++;	
				//dotB projected from opposite side of screen
				if(dot->getPosX() > dot->getCamera()->w/2 && dot->getPosY() > dot->getCamera()->h/2)
				{
					//dot in bottom right
					dotB->init(SCREEN_WIDTH,SCREEN_HEIGHT/4 , -dotB->getDOT_VEL(), -1-rand()%dotB->getDOT_VEL());
				}
				else if(dot->getPosX() > dot->getCamera()->w/2 && dot->getPosY() < dot->getCamera()->h/2)
				{
					//..top right
					dotB->init(SCREEN_WIDTH, SCREEN_HEIGHT *3/4,-dotB->getDOT_VEL(), 1+rand()%dotB->getDOT_VEL() );
				}
				else if(dot->getPosX() < dot->getCamera()->w/2 && dot->getPosY() > dot->getCamera()->h/2)
				{
					//..bottom left
					dotB->init(0, SCREEN_HEIGHT/4, dotB->getDOT_VEL(), -1-rand()%dotB->getDOT_VEL() );
				}
				else if(dot->getPosX() < dot->getCamera()->w/2 && dot->getPosY() < dot->getCamera()->h/2)
				{
					//..top left
					dotB->init(0, SCREEN_HEIGHT*3/4, dotB->getDOT_VEL(), 1+rand()%dotB->getDOT_VEL());
				}
				prevVelX = dotB->getVelX();
				prevVelY = dotB->getVelY();
			
				if (trigger == 1)
				{
					sound = 9;
					playSound();
					changeText(true, "XL",true, "I move",false, ".",true, "XL",true, "Em moc",false, ".");
				}
				if (trigger == 2)
				{
					changeText(true, "XL",true, "I move",true, "between faith and lust",true, "XL",true, "Em moc",true, "entre la fe i la voluptat");
				}
				if (trigger == 3)
				{
					changeText(true, "I move",true, "between faith and lust",true, "attracted by the desire to catch you.", true,"Em moc",true, "entre la fe i la voluptat", true, "atreta pel desig d'aconseguir-te.");
				}
				if (trigger > 3)
				{
					playSound();
				}
				level = 14;

			}
				
		}
		break;
	case 14:
		gameLoop(dotB->getRect(), cameraOff, false);
		if (dotB->getPosX() > SCREEN_WIDTH+ SCREEN_WIDTH/2  ||
			dotB->getPosX() < -SCREEN_WIDTH/2 ||
			dotB->getPosY() > SCREEN_HEIGHT+SCREEN_HEIGHT/2 ||
			dotB->getPosY() < -SCREEN_HEIGHT/2)
		{
			//if dotB exceeds screen limits, stop velocity
			dotB->init(dotB->getPosX(), dotB->getPosY(), 0, 0);
			level = 13;
			break; 
		}

			if(checkAllColliders() == true)
			{
				//if dot collides with dotb, dotb repels
				
					dotB->init(dotB->getPosX(), dotB->getPosY(), dotB->getVelX()*1.5, dotB->getVelY()*1.5);
					for(int i=0;i<30; i++)
					{
						gameLoop(dotB->getRect(), cameraOff, false);
					}
					
				if(trigger > 4)
				{	
						sound = 6;
						playSound();
						setTimeVariables();
						trigger = 0;
						//prevVelX = dotB->getVelX()*0.8;
						//prevVelY = dotB->getVelY()*0.8;
						level = 15;
						changeText(true,"O, like a wandering star" ,false, ".", false, ".", true, "Ai, com estrella errant",false, ".",false, ".");
						dotB->init(dotB->getPosX(), dotB->getPosY(), prevVelX, prevVelY);

				}
					
			}
			break;
		
		
	case 15:
			//return to prevVel for when dots collide
			dotB->init(dotB->getPosX(), dotB->getPosY(), prevVelX, prevVelY);

			
			//shrink boundBox

		 if(boundBox.x < dot->getCameraCentre()->x) 
		 {
		 
			if(hasTimePassed(100) == true)
			{
			boundBox.x += 8;
			boundBox.w -= 16;
			boundBox.y += 6;
			boundBox.h -= 12;
			}

		}
		else
		{
			dot->checkCollisionNumber(true);
			level = 16;
			break;
		}
		
		//stop dot from escaping boundbox
		if(dot->getPosX() < boundBox.x ) 
		{
			dot->init(boundBox.x - dot->getPosX(),0, dot->getVelX(),dot->getVelY());
		}
		if(dot->getPosX() > boundBox.x + boundBox.w )
		{
			dot->init(boundBox.x + boundBox.w - dot->getPosX(),0,dot->getVelX(),dot->getVelY());
		}
		if(dot->getPosY() < boundBox.y )
		{
			dot->init(0,boundBox.y - dot->getPosY(),dot->getVelX(),dot->getVelY());
		}
		if(dot->getPosY() > boundBox.y + boundBox.h )
		{
			dot->init(0,boundBox.y + boundBox.h - dot->getPosY(),dot->getVelX(),dot->getVelY());
		}
		//stop dotB from escaping entirely
		if(dotB->getPosX() < -SCREEN_WIDTH/4 ) 
		{
			dotB->init(0,dotB->getPosY(), prevVelX, prevVelY);
			dot->checkCollisionNumber(true);

		}
		if(dotB->getPosX() > SCREEN_WIDTH + SCREEN_WIDTH/4 )
		{
			dotB->init(SCREEN_WIDTH,dotB->getPosY(),prevVelX, prevVelY);
			dot->checkCollisionNumber(true);

		}
		if(dotB->getPosY() < -SCREEN_HEIGHT/4 )
		{
			dotB->init(dotB->getPosX(),0,prevVelX, prevVelY);
			dot->checkCollisionNumber(true);

		}
		if(dotB->getPosY() > SCREEN_HEIGHT+SCREEN_HEIGHT/4 )
		{
			dotB->init(dotB->getPosX(),SCREEN_HEIGHT,prevVelX, prevVelY);
			dot->checkCollisionNumber(true);

		}
		
		//dotB evade
		if(checkAllColliders() == true)
		{
			dotB->init(dotB->getPosX(), dotB->getPosY(), dotB->getVelX()*1.2, dotB->getVelY()*0.7);
		}
		handleEvents(checkingMovement);
		dot->move(dotB->getRect(), cameraOff);
		dot->initCamMove( dot->getVelX(), dot->getVelY());
		dotB->move(false);
		dotB->centreDot(dot->getCamera());
		dot->initCamMove( -dot->getVelX(), -dot->getVelY());
		clear();
		render();
		update();
						
		break;

	case 16:
		//set dotB going at *0.8 of dot's collision velocity
		dotB->init(dotB->getPosX(),dotB->getPosY(), prevVelX, prevVelY);
		
		gameLoop( dotB->getRect(), cameraOn, false);
		
		//stop dotB from disappearing offscreen
		
		if(dotB->getPosX() < -SCREEN_WIDTH/4 ) 
		{
			dotB->init(-SCREEN_WIDTH/8,dotB->getPosY(), prevVelX, prevVelY);
		}
		if(dotB->getPosX() > SCREEN_WIDTH + SCREEN_WIDTH/4 )
		{
			dotB->init(SCREEN_WIDTH + SCREEN_WIDTH/8 ,dotB->getPosY(),prevVelX, prevVelY);
		}
		if(dotB->getPosY() < -SCREEN_HEIGHT/4 )
		{
			dotB->init(dotB->getPosX(),-SCREEN_HEIGHT/8,prevVelX, prevVelY);
		}
		if(dotB->getPosY() > SCREEN_HEIGHT+SCREEN_HEIGHT/4 )
		{
			dotB->init(dotB->getPosX(),SCREEN_HEIGHT+SCREEN_HEIGHT/8,prevVelX, prevVelY);
		}
		
		
		//accelerate dotB on collision with dot
		
		if(checkAllColliders() == true)
		{	
			//repel from dot		
		/*	dotB->init(dotB->getPosX(), dotB->getPosY(), dot->getVelX()*1.5, dot->getVelY()*1.5);
			for(int i=0;i<10; i++)
			{
				gameLoop(dotB->getRect(), cameraOn, false);
			}*/
			dotB->init(dotB->getPosX(), dotB->getPosY(), prevVelX*1.5, prevVelY*1.5);
			for(int i=0;i<30; i++)
			{
				gameLoop(dotB->getRect(), cameraOn, false);
			}

			if(dot->checkCollisionNumber(false) > 24 && dot->checkCollisionNumber(false) < 37)
			{
				prevVelX *= -1;
				trigger++;
				
			}
			else
			{
				prevVelY *= -1;
				trigger++;
				
			}

			if (trigger == 1)
			{
				changeText(true,"O, like a wandering star" ,true, "one could become", false, ".", true, "Ai, com estrella errant",true, "pogués tornar-se",false, ".");
			}
			if (trigger == 3)
			{
				changeText(true,"O, like a star, errant" ,true, "one could become", true, "your mind thus to enchant", true, "Ai, com estrella errant",true, "pogués tornar-se",true, "per captivar el teu front");
			}
			if (trigger == 7)
			{
				changeText(true,"with my bullshit." ,false, ".", false, ".", true, "la meva falsedat.",false, ".",false, ".");
			}
			if (trigger == 10)
			{
				changeText(true,"-But just when the effort runs out" ,false, ".", false, ".", true, "—Però quan ja l’esforç se’t decandeixi",false, ".",false, ".");
			}
			if (trigger == 13)
			{
				changeText(true,"-But just when the effort runs out" ,true, "And you leave me like a toy in disenchantment", false, ".", true, "—Però quan ja l’esforç se’t decandeixi",true, "i em deixis com joguina en desencís",false, ".");
			}
			if (trigger == 15)
			{
				changeText(true,"-But just when the effort runs out" ,true, "And I am abandoned like a toy in the pile", true, "I will strangle the fountain of my smile.", true, "—Però quan ja l’esforç se’t decandeixi",true, "i em deixis com joguina en desencís",true, "estroncaré la font del meu somrís.");
			}
			if (trigger == 17)
			{
				changeText(true,"I'll stretch in fixed shadow" ,false, ".", false, ".", true, "M’allargaré en ombra clavada",false, ".",false, ".");
			}
			if (trigger == 19)
			{
				changeText(true,"I'll stretch in fixed shadow" ,false, ".", true, "Faithfulness.", true, "M’allargaré en ombra clavada",false, ".",true, "Fidelitat.");
			}
			if (trigger == 21)
			{
				changeText(true,"Do not forget that I am now your shadow" ,false, ".", false, ".", true, "No oblidis que sóc ara la teva ombra. ",false, ".",false, ".");
			}
			if (trigger == 23)
			{
				changeText(true,"Do not forget that I am now your shadow" ,true, "If you carry me in the forest", false, ".", true, "No oblidis que sóc ara la teva ombra. ", true, "Si em portes dintre el bosc",false, ".");
			}
			if (trigger == 25)
			{
				sound = 7;
				changeText(true,"Do not forget that I am now your shadow" ,true, "If you carry me in the forest-", false, ".", true, "No oblidis que sóc ara la teva ombra. ", true, "Si em portes dintre el bosc",false, ".");
			}
			if (trigger == 27)
			{
				changeText(true,"Do not forget that I am now your shadow" ,true, "If you carry me in the forest-", true, "Why are you offended", true, "No oblidis que sóc ara la teva ombra. ", true, "Si em portes dintre el bosc",true, "¿per què t’ofens");
			}
			if (trigger == 29)
			{
				changeText(true,"Do not forget that I am now your shadow" ,true, "If you carry me in the forest-", true, "Why are you offended", true, "No oblidis que sóc ara la teva ombra. ", true, "Si em portes dintre el bosc",true, "¿per què t’ofens");
			}
			if (trigger == 31)
			{
				changeText(true,"that I find myself stretched among the others?" ,false, ".", false, ".", true, "que em trobi estirgassada entre les altres?",false, ".",false, ".");
			}
			if (trigger == 33)
			{
				changeText(true,"that I find myself stretched among the others?" ,true, "-you always want just me?- Then walk in", false, ".", true, "que em trobi estirgassada entre les altres?",true, "—Em vols única sempre?— Pel desert",false, ".");
			}
			if (trigger == 35)
			{
				changeText(true,"that I find myself stretched among the others?" ,true, "-you always want just me?- Then walk in", true, "the desert, and in the midday sun!", true, "que em trobi estirgassada entre les altres?",true, "—Em vols única sempre?— Pel desert",true, "camina i en la seca migdiada.");
			}
			if (trigger == 37)
			{
				sound = 8;
				changeText(true,"You'll never notice me. Truly yours." ,false, ".", false, ".", true, "No em sentiràs. Ben teva.",false, ".",false, ".");
			}
			if (trigger == 39)
			{
				changeText(true,"You'll never notice me. Truly yours." ,true, "Free and agile. You see? So", false, ".", true, "No em sentiràs. Ben teva.",true, "Lliure i àgil. Veus?, així",false, ".");
			}
			if (trigger == 41)
			{
				changeText(true,"You never notice me. Truly yours." ,true, "Free and agile. You see? Therefore", true, "destiny's obstacle will stop you no more.", true, "No em sentiràs. Ben teva.",true, "Lliure i àgil. Veus?, així",true, "no et pesarà l’obstacle del destí.");
			}
			if (trigger == 43)
			{
				changeText(true,"Shadow is your memory." ,false, ".", false, ".", true, "Ombra és el teu record.",false, ".",false, ".");
			}
			if (trigger == 45)
			{
				changeText(true,"Shadow is your memory." ,true, "Shadow your thought", false, ".", true, "Ombra és el teu record.",true, "Ombra el teu pensament",false, ".");
			}
			if (trigger == 47)
			{
				changeText(true,"Shadow is your memory." ,true, "Shadow your thought", true, "and your follower.", true, "Ombra és el teu record.",true, "Ombra el teu pensament",true, "i el teu seguici.");
			}

			
		
		
			if(trigger > 50)
			{
				sound = 9;
				playSound();
				//get dotB to a velocity to leave the screen
				changeText(true,"It will only be when you run from the light" ,false, ".", false, ".", true, "Només serà quan fugis de la llum",false, ".",false, ".");
				prevVelX *= 1.5;
				prevVelY *= 1.5; 
				dot->checkCollisionNumber(true);
				trigger = 0;
				level = 17;	
			}
		}
		break;
	case 17:
	//level 17-21 dotB infinite
		dotB->init(dotB->getPosX(),dotB->getPosY(), prevVelX, prevVelY);
		gameLoop( dotB->getRect(), cameraOn, false);
		if(checkAllColliders() == true)
		{
			dotB->init(dotB->getPosX(),dotB->getPosY(), prevVelX*1.5, prevVelY*1.5);

			for(int i = 0; i<60; i++)
			{
				gameLoop( dotB->getRect(), cameraOn, false);
			}
			
			if ( dot->checkCollisionNumber(false) < 2)
			{
				changeText(true,"It will only be when you run from the light" ,true, "that I shy will be able to precede you.", false, ".", true, "Només serà quan fugis de la llum",true, "que podré vergonyosa precedir-te.",false, ".");
			}
			if ( dot->checkCollisionNumber(false) == 3)
			{
				changeText(true,"Shadow: that has no life nor colour" ,false, ".", false, ".", true, "Ombra: que no té vida ni color",false, ".",false, ".");
			}
			if ( dot->checkCollisionNumber(false) == 4)
			{
				changeText(true,"Shadow: that has no life nor colour" ,true, "- slow deformation -", false, ".", true, "Ombra: que no té vida ni color",true, "—deformació lenta—",false, ".");
			}
			if ( dot->checkCollisionNumber(false) == 5)
			{
				changeText(true,"Shadow: that has no life nor colour" ,true, "- slow deformation -", false, ".", true, "Ombra: que no té vida ni color",true, "—deformació lenta—",false, ".");
			}
			if ( dot->checkCollisionNumber(false) == 6)
			{
				changeText(true,"Shadow: that has no life nor colour" ,true, "- slow deformation -", true, "for an instant that returns you beautifully", true, "Ombra: que no té vida ni color",true, "—deformació lenta—",true, "per un instant que et torni bellament");
			}
			if ( dot->checkCollisionNumber(false) == 7)
			{
				changeText(true,"How much anger and fright! Lift me" ,false, ".", false, ".", true, "quants d’enuigs i d’esglai! Alçar-me",false, ".",false, ".");
			}
			if ( dot->checkCollisionNumber(false) == 8)
			{
				changeText(true,"How much anger and fright! Lift me" ,true, "the ardency of your arms can't.", false, ".", true, "quants d’enuigs i d’esglai! Alçar-me",true, "no podran les frisances del teu braç.",false, ".");
			}
			if ( dot->checkCollisionNumber(false) == 9)
			{
				changeText(true,"How much anger and fright! Lift me" ,true, "the ardency of your arms can't.", true, "Only the bad omen of losing the road", true, "quants d’enuigs i d’esglai! Alçar-me",true, "no podran les frisances del teu braç.",true, "Sols el mal averany que és perdre via");
			}
			if ( dot->checkCollisionNumber(false) == 10)
			{
				changeText(true,"-rocks that enclose the span of the path-" ,false, ".", false, ".", true, "—penyes que tanquin l’hora del camí—",false, ".",false, ".");
			}
			if ( dot->checkCollisionNumber(false) == 11)
			{
				changeText(true,"-rocks that enclose the span of the path-" ,true, "And you will flee, and I will follow you again.", false, ".", true, "—penyes que tanquin l’hora del camí—",true, "I fugiràs, i et tornaré a seguir.",false, ".");
			}
			if ( dot->checkCollisionNumber(false) == 12)
			{
				sound = 6;
				changeText(true,"I will follow you when you run, when you rest" ,false, ".", false, ".", true, "Et seguiré quan corris, quan descansis",false, ".",false, ".");
				prevVelX *= -1;
			}
			if ( dot->checkCollisionNumber(false) == 13)
			{
				changeText(true,"I will follow you when you run, when you rest" ,true, "I will jump stones, meadows and marsh,", false, ".", true, "Et seguiré quan corris, quan descansis",true, "saltaré pedres, prades i aiguamolls,",false, ".");
			}
			if ( dot->checkCollisionNumber(false) == 14)
			{
				changeText(true,"I will follow you when you run, when you rest" ,true, "I will jump stones, meadows and marsh,", true, "seas where I tremble frightened", true, "Et seguiré quan corris, quan descansis",true, "saltaré pedres, prades i aiguamolls,",true, "mars on tremolaré d’esgarrifor");
			}
			if ( dot->checkCollisionNumber(false) == 15)
			{
				changeText(true, "I will jump stones, meadows and marsh,", true, "seas where I tremble frightened", true, "without understanding the deep or the precipice", true, "saltaré pedres, prades i aiguamolls,",true, "mars on tremolaré d’esgarrifor",true, "sense entendre el profund ni el precipici,");
			}
			if ( dot->checkCollisionNumber(false) == 16)
			{
				changeText(true, "seas where I tremble with a start", true, "without understanding the deep or the precipice", true, "hung forever blind upon your heart.",true, "mars on tremolaré d’esgarrifor",true, "sense entendre el profund ni el precipici,",true, "orba penjada eterna del teu cor.");
			}
			if(dot->checkCollisionNumber(false) > 16)
			{
				sound = 7;
				playSound();
				trigger = 0;
				dot->checkCollisionNumber(true);
				level = 22;
				break;
			}
		}
		if (dotB->getPosX() > SCREEN_WIDTH + SCREEN_WIDTH/8 )
		{
			level = 18;
			break;

		}
		if (dotB->getPosX() < - SCREEN_WIDTH/8 )
		{
			level = 19;
			break;
		}
		if(dotB->getPosY() > SCREEN_HEIGHT+ SCREEN_HEIGHT/8)
		{
			level = 20;
			break;
		}
		if(dotB->getPosY() < - SCREEN_HEIGHT/8)
		{
			level = 21;
		}
			break;
	case 18:
	//leaves right side, enters left side
		dotB->init(0,dotB->getPosY(), prevVelX, prevVelY);
		level = 17;
		break;
	case 19:
	//leaves left side, enters right side
		dotB->init(SCREEN_WIDTH,dotB->getPosY(), prevVelX, prevVelY);
		level = 17;
		break;	
	case 20:
	//leaves bottom, enters top
		dotB->init(dotB->getPosX(),0, prevVelX, prevVelY);
		level = 17;
		break;
	case 21:
	//leaves top, enters bottom
		dotB->init(dotB->getPosX(),SCREEN_HEIGHT, prevVelX, prevVelY);
		level = 17;
		break;
	case 22:
	//dotB disappears and reappears randomly on collision
		srand(SDL_GetTicks());
		gameLoop( dotB->getRect(), cameraOn, false);
		dotB->init(dotB->getPosX(), dotB->getPosY(), 0, 0);
		if(dotB->getPosX() > SCREEN_WIDTH/2 - SCREEN_WIDTH/20 && dotB->getPosX() < SCREEN_WIDTH/2 + SCREEN_WIDTH/20 && dotB->getPosY() > SCREEN_HEIGHT/2 -SCREEN_HEIGHT/20 && dotB->getPosY() < SCREEN_HEIGHT/2 + SCREEN_HEIGHT/20)
		{
			dot->checkCollisionNumber(true);
			dotB->init(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT, 0, 0);
			trigger++;
		}
		//dotb reappears elsewhere if player loses it
		if( dotB->getPosX() > SCREEN_WIDTH + SCREEN_WIDTH/2 ||
		dotB->getPosX() < -SCREEN_WIDTH/2 ||
		dotB->getPosY() > SCREEN_HEIGHT + SCREEN_HEIGHT/2 ||
		dotB->getPosY() < -SCREEN_HEIGHT/2)
		{
			dotB->init(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT, 0, 0);
		}
		if (trigger == 1)
		{
			changeText(true,"Shadow I must be so just when you rest" ,false, ".", false, ".", true, "Ombra he d’ésser així quan ja reposis",false, ".",false, ".");
		}
		if (trigger == 2)
		{
			changeText(true,"Shadow I must be so just when you rest" ,true, "for me also the paths will have melted.", false, ".", true, "Ombra he d’ésser així quan ja reposis",true, "per mi també les sendes s’hauran fos.",false, ".");
		}
		if (trigger == 3)
		{
			changeText(true,"Shadow I must be so just when you rest" ,true, "for me also the paths will have melted.", true, "Everyone will leave, and I will have you, alone,", true, "Ombra he d’ésser així quan ja reposis",true, "per mi també les sendes s’hauran fos.",true, "Et deixarà tothom, i et tindré, sola,");
		}
		if (trigger == 4)
		{
			changeText(true,"near the company of flowers" ,false, ".", false, ".", true, "vora la companyia de les flors.",false, ".",false, ".");
		}
		if (trigger == 5)
		{
			changeText(true,"near the company of flowers." ,true, "Will you want the divine voice to arrive?", false, ".", true, "vora la companyia de les flors.",true, "Voldràs que arribi la veu divina?",false, ".");
		}
		if (trigger == 6)
		{
			changeText(true,"near the company of flowers." ,true, "Will you want the divine voice to arrive?", true, "-awakening-", true, "vora la companyia de les flors.",true, "Voldràs que arribi la veu divina?",true, "—deixondiment—");
		}
		if (trigger == 7)
		{
			changeText(true,"Inseparable." ,false, ".", false, ".", true, "Inseparables.",false, ".",false, ".");
		}
		if (trigger == 8)
		{
			changeText(true,"Inseparable." ,true, "It was in the clarity", false, ".", true, "Inseparables.",true, "Fora en la claredat",false, ".");
		}
		if (trigger == 9)
		{
			changeText(true,"Inseparable." ,true, "It was in the clarity", true, "of You?", true, "Inseparables.",true, "Fora en la claredat",true, "de Tu?");
		}
		if (trigger == 10)
		{
			changeText(true,"Because if you are not," ,false, ".", false, ".", true, "Car si no ets,",false, ".",false, ".");
		}
		if (trigger == 11)
		{
			changeText(true,"Because if you are not," ,true, "I don't want to be anyone.", false, ".", true, "Car si no ets,",true, "no vull sê ningú.",false, ".");
		}
		/*
		if (trigger == 13)
		{
			changeText(false,"." ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}
		*/
		if(trigger > 11)
		{
			sound = 8;
			playSound();
			dotB->init(10000, 10000, 0, 0);
			level = 23;
			trigger = 0;
			dot->checkMoveTrigger(true);
		}
		break;
	case 23:
	//disappears dotA if it touches wall
		gameLoop( dotB->getRect(), cameraOff, false);
		// this part only necessary for debug
		//checkingMovement = true;
		//
		if(dot->checkMoveTrigger(false) == 2)
		{
			changeText(true,"an automated opponent can employ chance or" ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}		
		if(dot->checkMoveTrigger(false) == 4)
		{
			changeText(true,"an automated opponent can employ chance or" ,true, "complexity to imitate a real thinking player", false, ".", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 5)
		{
			changeText(true,"an automated opponent can employ chance or" ,true, "complexity to imitate a real thinking player", true, "but in most games there is a correct move", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 7)
		{
			changeText(true,"that only needs sufficient computation" ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 8)
		{
			changeText(true,"that only needs sufficient computation" ,true, "every move in noughts and crosses when", false, ".", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 9)
		{
			changeText(true,"that only needs sufficient computation" ,true, "every move in noughts and crosses when", true, "followed with the correct move ends in a draw", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 11)
		{
			changeText(true,"with all conditions known there is a best move" ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 12)
		{
			changeText(true,"with all conditions known there is a best move" ,true, "therefore when you make a move", false, ".", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 13)
		{
			changeText(true,"with all conditions known there is a best move" ,true, "therefore when you make a move", true, "your opponent's move is inevitable", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 15)
		{
			changeText(true,"a game against an optimised computer opponent" ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 16)
		{
			changeText(true,"a game against an optimised computer opponent" ,true, "is determined by your participation", false, ".", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 17)
		{
			changeText(true,"a game against an optimised computer opponent" ,true, "is determined by your participation", true, "moving black moves white", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 19)
		{
				changeText(true,"an ambidextrous two-hander" ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 20)
		{
				changeText(true,"an ambidextrous two-hander" ,true, "a nought and a cross are drawn at once", false, ".", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 21)
		{
				changeText(true,"an ambidextrous two-hander" ,true, "a nought and a cross are drawn at once", true, "you have absolute power", false, ".",false, ".",false, ".");
		}	
		if(dot->checkMoveTrigger(false) == 23)
		{
			changeText(true,"and none" ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) > 23)
		{
			changeText(true,"and none" ,true, "except the power to continue playing", false, ".", false, ".",false, ".",false, ".");
			
		}
		if(dot->checkMoveTrigger(false) > 28)
		{	
			if (prevMoveTrigger == dot->checkMoveTrigger(false))
			{
				if(hasTimePassed(5000))
				{
					dot->posInit(10000, 10000);
					changeText(true,"After 1936, her output ends." ,false, ".", false, ".", false, ".",false, ".",false, ".");
					sound = 9;
					playSound();
					level = 24;
					dot->checkMoveTrigger(true);
				}
			}
			else
				setTimeVariables();
			

		}
		prevMoveTrigger = dot->checkMoveTrigger(false);
	
		break;
	case 24:
		//dot->posInit(0, 0);
		handleEvents(checkingMovement);
		//dot->move(dotB->getRect(), false);
		dotB->move(false);
		clear();
		render();
		update();
		if(dot->checkMoveTrigger(false) == 3)
		{
				changeText(true,"After 1936, her output ends." ,true, "It is reported that she was committed", false, ".", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 5)
		{
				changeText(true,"After 1936, her output ends." ,true, "It is reported that she was committed", true, "to an institution following a still birth.", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 8)
		{
				changeText(true,"She remained confined until her death in 1991." ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 10)
		{
				changeText(true,"She remained confined until her death in 1991." ,true, "Carles Riba to Paulina Crusat, 8/3/1956:", false, ".", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 12)
		{
				changeText(true,"As for Concepcio Casanova..." ,false, ".", false, ".", true, "Quant a Concepció Casanova...",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 13)
		{
				changeText(true,"As for Concepcio Casanova... it is very sad" ,false, ".", false, ".", true, "Quant a Concepció Casanova... és molt trist",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 14)
		{
				changeText(true,"As for Concepcio Casanova... it is very sad" ,true, "The anxiety, the susceptibility, the sweetness", false, ".", true, "Quant a Concepció Casanova... és molt trist",true, "L'ansietat, la susceptibilitat, la dolçor",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 15)
		{
				changeText(true,"As for Concepcio Casanova... it is very sad" ,true, "The anxiety, the susceptibility, the sweetness", true, "at the same time exigent and defenceless that", true, "Quant a Concepció Casanova... és molt trist",true, "L'ansietat, la susceptibilitat, la dolçor",true, "alhora exigent i indefensa que");
		}
		if(dot->checkMoveTrigger(false) == 17)
		{
				changeText(true,"I had known in this former student of mine," ,false, ".", false, ".", true, "havia conegut en aquesta antiga alumna meva,",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 18)
		{
				changeText(true,"I had known in this former student of mine," ,true, "one day I was told that they were total,", true, "'Umnachtung'", true, "havia conegut en aquesta antiga alumna meva,",true, " un dia em fou dit que eren total.",true, "«Umnachtung»");
		}
		if(dot->checkMoveTrigger(false) == 20)
		{
				changeText(true,"Maybe twenty years ago." ,false, ".", false, ".", true, "Fa potser vint anys.",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 21)
		{
				changeText(true,"Maybe twenty years ago." ,true, "Always I had ignored the details of the", false, ".", true, "Fa potser vint anys.",true, "Sempre he ignorat els detalls del",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 22)
		{
				changeText(true,"Maybe twenty years ago." ,true, "Always I had ignored the details of the", true, "disaster: She had married,", true, "Fa potser vint anys.",true, "Sempre he ignorat els detalls del",true, "desastre: s'havia casat,");
		}
		if(dot->checkMoveTrigger(false) == 24)
		{
				changeText(true,"she had passed to an other circle of" ,false, ".", false, ".", true, "havia passat a un altre cercle de",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 25)
		{
				changeText(true,"she had passed to an other circle of" ,true, "relation. Some times I ask for her", false, ".", true, "havia passat a un altre cercle de.",true, "relació. De vegades pregunto per ella ",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 26)
		{
				changeText(true,"she had passed to an other circle of" ,true, "relation. Some times I ask for her", true, "from her sister Montserrat,", true, "havia passat a un altre cercle de",true, "relació. De vegades pregunto per ella ",true, "a la seva germana Montserrat,");
		}
		if(dot->checkMoveTrigger(false) == 28)
		{
				changeText(true,"a painter of talent: " ,false, ".", false, ".", true, "una pintora de talent: ",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 29)
		{
				changeText(true,"a painter of talent: " ,true, "she shakes her head,", false, ".", true, "una pintora de talent: ",true, "branda el cap, ",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 30)
		{
				changeText(true,"a painter of talent: " ,true, "she shakes her head,", true, "'She's still locked up.'", true, "una pintora de talent: ",true, "branda el cap, ",true, "«Continua reclosa...» ");
		}
		
		if(dot->checkMoveTrigger(false) == 31)
		{
				changeText(false,"." ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 32)
		{
				changeText(true,"'Umnachtung', the German for mentally disturbed" ,false, ".", false, ".", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) == 35)
		{
				changeText(true,"'Umnachtung', the German for mentally disturbed" ,true, "literally, 'surrounded by night'.", false, ".", false, ".",false, ".",false, ".");
		}
		if(dot->checkMoveTrigger(false) > 38)
		{
			//sets dotB toward centre
				dotB->init(SCREEN_WIDTH, SCREEN_HEIGHT/2, -dotB->getDOT_VEL(), 0);
				level = 25;
				sound = 6;
				playSound();
		}
		break;
	case 25:
		//move dotB to centre
		handleEvents(checkingMovement);
		//dot->move(dotB->getRect(), false);
		dotB->move(false);
		clear();
		render();
		update();
		if(dotB->getPosX() < dot->getCameraCentre()->x)
		{
			dotB->init(dotB->getPosX(), dotB->getPosY(), 0, 0);
			checkingMovement = true;
			dot->checkMoveTrigger(true);
			level = 26;
		}
		break;
		
	case 26:
		handleEvents(checkingMovement);
		//dot->move(dotB->getRect(), false);
		dotB->move(false);
		clear();
		render();
		update();
		if(dot->checkMoveTrigger(false) == 2)
		{
			changeText(true,"XLV" ,false, ".", false, ".", true, "XLV",false, ".",false, ".");
			dotBDance(-1, 1);
		}
		if(dot->checkMoveTrigger(false) == 3)
		{
			changeText(true,"XLV" ,true, "Música of love", false, ".", true, "XLV",true, "Música de l’amor,",false, ".");
			dotBDance(1, 1);
		}
		if(dot->checkMoveTrigger(false) == 4)
		{
			changeText(true,"XLV" ,true, "Música of love", true, "i dancem refusant", true, "XLV",true, "Música de l’amor,",true, "i dancem refusant");
			dotBDance(1, -1);
		}
		if(dot->checkMoveTrigger(false) == 5)
		{
			changeText(true, "Música of love", true, "i dancem refusant",true, "el gest, continuament.", true,  "Música de l’amor,",true, "i dancem refusant", true, "el gest, continuament.");
			dotBDance(-1, 1);
		}
		if(dot->checkMoveTrigger(false) == 6)
		{
			changeText(true,"(Per a Tu, to only you" ,false, ".", false, ".", true, "(Per a Tu, per a Tu només",false, ".",false, ".");
			dotBDance(1, -1);
		}
		if(dot->checkMoveTrigger(false) == 7)
		{
			changeText(true,"(Per a Tu, to only you" ,true, "la flower of thought).", false, ".", true, "(Per a Tu, per a Tu només",true, "la flor del pensament).",false, ".");
			dotBDance(-1, 1);
		}
		if(dot->checkMoveTrigger(false) == 8)
		{
			changeText(true,"(Per a Tu, to only you" ,true, "la flower of thought).", true, "Neither red, ni very tremulous", true, "(Per a Tu, per a Tu només",true, "la flor del pensament).",true, "Ni roja, ni molt trèmula");
			dotBDance(1, -1);
		}
		if(dot->checkMoveTrigger(false) == 9)
		{
			changeText(true,"          I don't know." ,false, ".", false, ".", true, "          No sé.",false, ".",false, ".");
			dotBDance(-1, 1);
		}
		if(dot->checkMoveTrigger(false) == 10)
		{
			changeText(true,"          I don't know." ,true, "Per ever more I will love you", false, ".", true, "          No sé.",true, "Per sempre més t’estimaré",false, ".");
			dotBDance(1, -1);
		}
		if(dot->checkMoveTrigger(false) == 11)
		{
			changeText(true,"          I don't know." ,true, "Per ever more I will love you", true, "          In oblition.", true, "          No sé.",true, "Per sempre més t’estimaré",true, "          dintre l’oblit.");
			dotBDance(-1, 1);
		}
		//DEBUG FROM HERE
		if(dot->checkMoveTrigger(false) > 13)
		{
			if(dotB->getPosX() < SCREEN_WIDTH && dotB->getPosX() > 0 && dotB->getPosY() < SCREEN_HEIGHT && dotB->getPosY() > 0)
			{
				changeText(false,"." ,false, ".", false, ".", false, ".",false, ".",false, ".");
				dotB->init(dotB->getPosX(),dotB->getPosY(), 0, 0);
				dot->posInit(SCREEN_WIDTH/8,SCREEN_HEIGHT/2);
				dot->checkMoveTrigger(true);
				checkingMovement = false;
				level = 27;
				break;	
			}
			dotBDance(1, 1);
		
		} 
		
		if (dotB->getPosX() > SCREEN_WIDTH )
		{
		dotB->init(0,dotB->getPosY(), prevVelX, prevVelY);
			break;

		}
		if (dotB->getPosX() < 0 )
		{
			dotB->init(SCREEN_WIDTH, dotB->getPosY(), prevVelX, prevVelY);
			break;
		}
		if(dotB->getPosY() > SCREEN_HEIGHT)
		{
			dotB->init(dotB->getPosX(),0, prevVelX, prevVelY);
			break;
		}
		if(dotB->getPosY() < 0)
		{
			dotB->init(dotB->getPosX(),SCREEN_HEIGHT, prevVelX, prevVelY);
		}
			
		break;
	case 27:
		//decomment to start debug here WHAT DOES OFFSCREEN DO???
		//dotB->init(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, 0, 0);
		//
		gameLoop(dotB->getRect(), cameraOff, false);
		if(checkAllColliders() == true)
		{	
			relativeX = dotB->getPosX() - dot->getPosX();
			relativeY = dotB->getPosY() - dot->getPosY();
			dot->checkMoveTrigger(true);
			Mix_PlayMusic( gMusic, -1 );	
			level = 28;
			
		}
		break;
	case 28:
		checkingMovement = true;
		dotB->init(dot->getPosX()+relativeX,dot->getPosY()+relativeY,0,0); 
		handleEvents(checkingMovement);
		dot->move(&offScreen, cameraOff);
		dotB->move(false);
		//render();
		dotB->render(gRenderer);
		dot->render(gRenderer);
		//Load media
		//
		update();
		
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);

		if(dot->checkMoveTrigger(false) < 3)
		{
			poemWords->render(SCREEN_WIDTH/3, wordsHeight, gRenderer);			
		}
		if(dot->checkMoveTrigger(false) > 3 && dot->checkMoveTrigger(false) < 7)
		{
			poemWords1->render(SCREEN_WIDTH/3, wordsHeight*2, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 7 && dot->checkMoveTrigger(false) < 11)		
		{
			poemWords2->render(SCREEN_WIDTH/20, wordsHeight*4, gRenderer);
			poemWords3->render(SCREEN_WIDTH*3/5, wordsHeight*4, gRenderer);
		}
		if(dot->checkMoveTrigger(false) > 11 && dot->checkMoveTrigger(false) < 15)		
		{
			poemWords4->render(SCREEN_WIDTH/20, wordsHeight*5, gRenderer);
			poemWords5->render(SCREEN_WIDTH*3/5, wordsHeight*5, gRenderer);
		}
		if(dot->checkMoveTrigger(false) > 15 && dot->checkMoveTrigger(false) < 19)		
		{
			poemWords6->render(SCREEN_WIDTH/20, wordsHeight*6, gRenderer);
			poemWords7->render(SCREEN_WIDTH*3/5, wordsHeight*6, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 19 && dot->checkMoveTrigger(false) < 23)		
		{
			poemWords8->render(SCREEN_WIDTH/4, wordsHeight*7, gRenderer);
		}
		if(dot->checkMoveTrigger(false) > 23 && dot->checkMoveTrigger(false) < 27)		
		{
			poemWords9->render(SCREEN_WIDTH/4, wordsHeight*8, gRenderer);
		}
		if(dot->checkMoveTrigger(false) > 27 && dot->checkMoveTrigger(false) < 31)		
		{
			poemWords10->render(SCREEN_WIDTH/4, wordsHeight*9, gRenderer);
		}
		if(dot->checkMoveTrigger(false) > 31 && dot->checkMoveTrigger(false) < 34)		
		{
			poemWords11->render(SCREEN_WIDTH/4, wordsHeight*10, gRenderer);
		}
		if(dot->checkMoveTrigger(false) > 34 && dot->checkMoveTrigger(false) < 38)		
		{
			poemWords12->render(SCREEN_WIDTH/4, wordsHeight*11, gRenderer);
			
		}
		if(dot->checkMoveTrigger(false) > 38 && dot->checkMoveTrigger(false) < 42)		
		{
			poemWords13->render(SCREEN_WIDTH/20, wordsHeight*13, gRenderer);
			poemWords14->render(SCREEN_WIDTH*3/5, wordsHeight*13, gRenderer);
		}
		if(dot->checkMoveTrigger(false) > 42 && dot->checkMoveTrigger(false) < 46)		
		{
			poemWords15->render(SCREEN_WIDTH/20, wordsHeight*14, gRenderer);
			poemWords16->render(SCREEN_WIDTH*3/5, wordsHeight*14, gRenderer);
		}
		if(dot->checkMoveTrigger(false) > 46 && dot->checkMoveTrigger(false) < 50)		
		{

			poemWords17->render(SCREEN_WIDTH/20, wordsHeight*15, gRenderer);
			poemWords18->render(SCREEN_WIDTH*3/5, wordsHeight*15, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 50 && dot->checkMoveTrigger(false) < 54)		
		{
			poemWords19->render(SCREEN_WIDTH/20, wordsHeight*16, gRenderer);
			poemWords20->render(SCREEN_WIDTH*3/5, wordsHeight*16, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 54 && dot->checkMoveTrigger(false) < 58)		
		{
			poemWords21->render(SCREEN_WIDTH/2, wordsHeight*17, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 58 && dot->checkMoveTrigger(false) < 62)		
		{
			poemWords22->render(SCREEN_WIDTH/2, wordsHeight*18, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 62 && dot->checkMoveTrigger(false) < 66)		
		{
			poemWords23->render(SCREEN_WIDTH/2, wordsHeight*19, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 66 && dot->checkMoveTrigger(false) < 70)		
		{
			poemWords24->render(SCREEN_WIDTH/2, wordsHeight*20, gRenderer);
		}
		if(dot->checkMoveTrigger(false) > 70 && dot->checkMoveTrigger(false) < 74)		
		{
			poemWords25->render(SCREEN_WIDTH/2, wordsHeight*21, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 74 && dot->checkMoveTrigger(false) < 78)		
		{
			poemWords26->render(SCREEN_WIDTH/2, wordsHeight*22, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 78 && dot->checkMoveTrigger(false) < 82)		
		{
			poemWords27->render(SCREEN_WIDTH/20, wordsHeight*24, gRenderer);
			poemWords28->render(SCREEN_WIDTH*3/5, wordsHeight*24, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 82 && dot->checkMoveTrigger(false) < 86)		
		{
			poemWords29->render(SCREEN_WIDTH/3, wordsHeight*25, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 86 && dot->checkMoveTrigger(false) < 90)		
		{
			poemWords30->render(SCREEN_WIDTH/3, wordsHeight*26, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 90 && dot->checkMoveTrigger(false) < 94)		
		{
			poemWords31->render(SCREEN_WIDTH/3, wordsHeight*27, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 94 && dot->checkMoveTrigger(false) < 98)		
		{
			poemWords32->render(SCREEN_WIDTH/3, wordsHeight*28, gRenderer);

		}
		if(dot->checkMoveTrigger(false) > 98 && dot->checkMoveTrigger(false) < 102)		
		{
			poemWords33->render(SCREEN_WIDTH/3, wordsHeight*29, gRenderer);

		}



		//check if dotB is onscreen and if a big pattern has been made
		if(dot->checkMoveTrigger(false) > 140 && dotB->getPosX() < SCREEN_WIDTH && dotB->getPosX() > 0 && dotB->getPosY() < SCREEN_HEIGHT &&dotB->getPosY() > 0)
		{
			checkingMovement = false;
			dot->checkMoveTrigger(true);
			level = 29;
			Mix_FadeOutMusic(2000);

		}
		break;
	case 29: 
		handleEvents(checkingMovement);
		dot->move(&offScreen, cameraOff);
		dotB->move(false);
		//fade dotb in and out
		if(hasTimePassed(1))
		{
			
			colorFade = colorFade - 5;
			dotB->renderDiffColor(gRenderer, colorFade);
			if(colorFade == 50)
			{
				colorFade = 255;
			}
		}
		dot->render(gRenderer);
		renderTheWords();
		update();
		if(dot->checkCollision(dotB->getRect())==true)
		{
			sound = 7;
			playSound();
			clear();
			render();
			update();
			level = 30;
			trigger = 0;
			setTimeVariables();
		}
		break;
	case 30:
		handleEvents(checkingMovement);
		clear();
		render();	
		update();
		if(hasTimePassed(2000))
		{
			
			trigger++;
			level = 31;
		}
		break;
	case 31:
		
		if(trigger == 1)
		{
			changeText(true,"Now: stillness?" ,false, ".", false, ".", true, "Ara: quietud?",false, ".",false, ".");
			level = 30;
			setTimeVariables();
		}
		if(trigger == 2)
		{level = 30;
		setTimeVariables();
			changeText(true,"Now: stillness?" ,true, "No, it is the respect of the earth", false, ".", true, "Ara: quietud?",true, "No, és el respecte de la terra",false, ".");
		}
		if(trigger == 3)
		{level = 30;
		setTimeVariables();
			changeText(true,"Now: stillness?" ,true, "No, it is the respect of the earth", true, "for the storm that has passed.", true, "Ara: quietud?",true, "No, és el respecte de la terra",true, "per la tempesta que ha passat.");
		}
		if(trigger == 4)
		{level = 30;
		setTimeVariables();
			changeText(true,"Absence? ..." ,false, ".", false, ".", true, "Absència? ...",false, ".",false, ".");
		}
		if(trigger == 5)
		{level = 30;
		setTimeVariables();
			changeText(true,"Absence? ..." ,true, "But, no:", false, ".", true, "Absència? ...",true, "Pero, no:",false, ".");
		}
		if(trigger == 6)
		{level = 30;
		setTimeVariables();
			changeText(true,"Absence? ..." ,true, "But, no:", true, "it is the shrunken timidity of space.", true, "Absència? ...",true, "Pero, no:",true, "és la encongida timidesa de l'espai.");
		}
		if(trigger == 7)
		{level = 30;
			setTimeVariables();
			changeText(false,"." ,false, ".", false, ".", false, ".",false, ".",false, ".");

		}
		if(trigger == 8)
		{
				handleEvents(checkingMovement);
				clear();
				render();
				update();
				//reset();
				level = 0;	
		}
		break;

			
	default: level = 0; break;
	}
}
