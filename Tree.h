#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"

class Tree
{
public:
	Tree(int x, int y, float *CameraX, float *CameraY, SDL_Setup* csdl_setup);
	~Tree(void);

	void DrawCrown();
	void DrawTrunk();

	int GetX();
	int GetY();

	Sprite* GetCrown() { return Crown; }
	Sprite* GetTrunk() { return Trunk; }

private:
	int x, y;
	Sprite* Crown;
	Sprite* Trunk;

	float *CameraX;
	float *CameraY;
};
