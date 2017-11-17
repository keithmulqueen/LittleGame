#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
#include "MainCharacter.h"
#include "Environment.h"
#include <math.h> 

class Main
{
public:
	Main(int passed_ScreenWidth, int passed_ScreenHeight);
	~Main(void);
	void GameLoop();

private:
	float CameraX;
	float CameraY;

	MainCharacter *bob;
	Environment* ForestArea;

	int ScreenWidth;
	int ScreenHeight;

	bool quit;


	SDL_Setup* sdl_setup;

	int MouseX;
	int MouseY;
};

