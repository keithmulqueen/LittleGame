#pragma once

#include "stdafx.h"

class CollisionRectangle
{
public:
	CollisionRectangle();
	CollisionRectangle(int x, int y, int w, int h);
	~CollisionRectangle(void);

	void SetRectangle(int x, int y, int w, int h);
	SDL_Rect GetRectangle() { return CollisionRect; }

	void SetX(int x) { CollisionRect.x = x + OffsetX; }
	void SetY(int y) { CollisionRect.y = y + OffsetY; }

private:
	int OffsetX;
	int OffsetY;
	SDL_Rect CollisionRect;
};
