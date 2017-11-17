#include "stdafx.h"
#pragma once

class SDL_Setup
{
public:
	SDL_Setup(bool* quit, int ScreenWidth, int ScreenHeight);
	~SDL_Setup();

	SDL_Renderer* getRenderer();
	SDL_Event* getMainEvent();

	void Begin();
	void End();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;
};

