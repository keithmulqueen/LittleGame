#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "Environment.h"

#include <math.h>

class MainCharacter
{
public:
	MainCharacter(SDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *CameraX, float *CameraY, Environment* passed_Environment);
	~MainCharacter(void);

	double GetDistance(int X1, int Y1, int X2, int Y2);

	void Update();
	void Draw();
private:
	Environment* Environment1;
	void UpdateAnimation();
	void UpdateControls();

	float *CameraX;
	float *CameraY;

	int *MouseX;
	int *MouseY;

	SDL_Setup* sdl_setup;

	Sprite* bob;
	int timeCheck;

	bool Follow;
	int Follow_Point_X;
	int Follow_Point_Y;

	float distance;
	bool stopAnimation;
};