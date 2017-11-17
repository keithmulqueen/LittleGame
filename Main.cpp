#include "StdAfx.h"
#include "Main.h"


Main::Main(int passed_ScreenWidth, int passed_ScreenHeight)
{
	CameraX = 0;
	CameraY = 0;
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	sdl_setup = new SDL_Setup(&quit, ScreenWidth, ScreenHeight);

	ForestArea = new Environment(ScreenWidth, ScreenHeight, &CameraX, &CameraY, sdl_setup);


	MouseX = 0;
	MouseY = 0;

	bob = new MainCharacter(sdl_setup, &MouseX, &MouseY, &CameraX, &CameraY, ForestArea);
}


Main::~Main(void)
{
	delete sdl_setup;

	delete bob;
}


void Main::GameLoop(void)
{
	while (!quit && sdl_setup->getMainEvent()->type != SDL_QUIT)
	{
		sdl_setup->Begin();
		SDL_GetMouseState(&MouseX, &MouseY);
		ForestArea->DrawBack();

		bob->Draw();
		bob->Update();
		ForestArea->Update();

		ForestArea->DrawFront();
		sdl_setup->End();
	}
}