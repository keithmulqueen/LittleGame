#pragma once
#include "stdafx.h"
#include <vector>
#include "SDL_Setup.h"
#include "Sprite.h"
#include "Tree.h"
#include <fstream>
#include <string>
#include <sstream>

class Environment
{
public:
	Environment(int ScreenWidth, int ScreenHeight, float *CameraX, float *CameraY, SDL_Setup* csdl_setup);
	~Environment(void);


	void DrawBack();
	void DrawFront();

	void Update();

	void SaveToFile();
	void LoadFromFile();

	enum ModeType
	{
		GamePlay,
		LevelCreation
	};

	std::vector<Tree*> GetTrees() { return trees; }

private:
	int Mode;
	SDL_Setup* sdl_setup;
	float* CameraX;
	float* CameraY;

	bool OnePressed;
	Sprite* grass[4][7];

	std::vector<Tree*> trees;
};