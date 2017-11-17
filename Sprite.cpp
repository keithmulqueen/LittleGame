#include "Sprite.h"


Sprite::Sprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, float *passed_CameraX, float *passed_CameraY, CollisionRectangle passed_CollisionRect)
{

	CollisionRect = passed_CollisionRect;
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, FilePath.c_str());

	if (image == NULL)
	{
		std::cout << "Couldn't Load " << FilePath.c_str() << std::endl;
	}

	CollisionImage = NULL;

	CollisionImage = IMG_LoadTexture(renderer, "CollisionRect.png");

	if (CollisionImage == NULL)
	{
		std::cout << "Couldn't Load " << "CollisionImage" << std::endl;
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);

	crop.x = 0;
	crop.y = 0;
	crop.w = img_width;
	crop.h = img_height;

	X_pos = x;
	Y_pos = y;

	Orgin_X = 0;
	Orgin_Y = 0;

	CurrentFrame = 0;
	Amount_Frame_X = 0;
	Amount_Frame_X = 0;

	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	Camera.x = rect.x + *CameraX;
	Camera.y = rect.y + *CameraY;
	Camera.w = rect.w;
	Camera.h = rect.h;
}

void Sprite::SetUpAnimation(int passed_Amount_X, int passed_Amount_Y)
{
	Amount_Frame_X = passed_Amount_X;
	Amount_Frame_Y = passed_Amount_Y;


}

void Sprite::PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed)
{
	if (animationDelay + Speed < SDL_GetTicks())
	{

		if (EndFrame <= CurrentFrame)
			CurrentFrame = BeginFrame;
		else
			CurrentFrame++;

		crop.x = CurrentFrame * (img_width / Amount_Frame_X);
		crop.y = Row * (img_height / Amount_Frame_Y);
		crop.w = img_width / Amount_Frame_X;
		crop.h = img_height / Amount_Frame_Y;

		animationDelay = SDL_GetTicks();
	}
}

Sprite::~Sprite(void)
{
	SDL_DestroyTexture(image);
}

void Sprite::Draw()
{
	Camera.x = rect.x + *CameraX;
	Camera.y = rect.y + *CameraY;

	CollisionRect.SetX(rect.x + *CameraX);
	CollisionRect.SetY(rect.y + *CameraY);

	SDL_RenderCopy(renderer, image, &crop, &Camera);


	SDL_RenderCopy(renderer, CollisionImage, NULL, &CollisionRect.GetRectangle());
}

void Sprite::DrawSteady()
{
	SDL_RenderCopy(renderer, image, &crop, &rect);
	SDL_RenderCopy(renderer, CollisionImage, NULL, &CollisionRect.GetRectangle());
}

void Sprite::SetX(float X)
{
	X_pos = X;

	rect.x = int(X_pos - Orgin_X);
}

void Sprite::SetY(float Y)
{
	Y_pos = Y;

	rect.y = int(Y_pos - Orgin_Y);
}

void Sprite::SetPosition(float X, float Y)
{
	X_pos = X;
	Y_pos = Y;

	rect.x = int(X_pos - Orgin_X);
	rect.y = int(Y_pos - Orgin_Y);
}

float Sprite::GetX()
{
	return X_pos;
}

float Sprite::GetY()
{
	return Y_pos;
}

void Sprite::SetOrgin(float X, float Y)
{
	Orgin_X = X;
	Orgin_Y = Y;

	SetPosition(GetX(), GetY());

}

void Sprite::SetWidth(int W)
{
	rect.w = W;
}

void Sprite::SetHeight(int H)
{
	rect.h = H;
}

int Sprite::GetWidth()
{
	return rect.w;
}

int Sprite::GetHeight()
{
	return rect.h;
}

bool Sprite::isColliding(CollisionRectangle theCollider)
{
	return !(CollisionRect.GetRectangle().x + CollisionRect.GetRectangle().w < theCollider.GetRectangle().x || CollisionRect.GetRectangle().y + CollisionRect.GetRectangle().h < theCollider.GetRectangle().y || CollisionRect.GetRectangle().x > theCollider.GetRectangle().x + theCollider.GetRectangle().w || CollisionRect.GetRectangle().y > theCollider.GetRectangle().y + theCollider.GetRectangle().h);
}