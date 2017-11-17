#include "stdafx.h"
#include "SDL_Setup.h"

SDL_Setup::SDL_Setup(bool* quit, int ScreenWidth, int ScreenHeight)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	window = NULL;
	window = SDL_CreateWindow("My game", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window error." << std::endl;
		*quit = true;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mainEvent = new SDL_Event();
}


SDL_Setup::~SDL_Setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer* SDL_Setup::getRenderer()
{
	return renderer;
}

SDL_Event* SDL_Setup::getMainEvent()
{
	return mainEvent;
}

void SDL_Setup::Begin()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);

}

void SDL_Setup::End()
{
	SDL_RenderPresent(renderer);
}


