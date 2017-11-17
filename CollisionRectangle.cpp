#include "CollisionRectangle.h"


CollisionRectangle::CollisionRectangle()
{
	OffsetX = 0;
	OffsetY = 0;
	SetRectangle(0, 0, 0, 0);
}

CollisionRectangle::CollisionRectangle(int x, int y, int w, int h)
{
	OffsetX = x;
	OffsetY = y;
	SetRectangle(0, 0, w, h);
}


CollisionRectangle::~CollisionRectangle(void)
{
}

void CollisionRectangle::SetRectangle(int x, int y, int w, int h)
{
	CollisionRect.x = x + OffsetX;
	CollisionRect.y = y + OffsetY;
	CollisionRect.w = w;
	CollisionRect.h = h;
}