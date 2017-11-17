#include "Environment.h"


Environment::Environment(int ScreenWidth, int ScreenHeight, float *passed_CameraX, float *passed_CameraY, SDL_Setup* passed_sdl_setup)
{
	sdl_setup = passed_sdl_setup;

	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			grass[i][j] = new Sprite(sdl_setup->getRenderer(), "Background1.bmp", ScreenWidth * i, ScreenHeight  * j, ScreenWidth, ScreenHeight, CameraX, CameraY, CollisionRectangle());
		}
	}

	Mode = LevelCreation;
	LoadFromFile();

	OnePressed = false;
}


Environment::~Environment(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			delete grass[i][j];
		}

	}

	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
	{
		delete (*i);
	}

	trees.clear();
}

void Environment::DrawBack()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			grass[i][j]->Draw();
		}
	}

	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
	{
		(*i)->DrawTrunk();
	}
}

void Environment::DrawFront()
{
	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
	{
		(*i)->DrawCrown();
	}
}

void Environment::LoadFromFile()
{
	std::ifstream LoadedFile("StageLayout.txt");

	std::string line;

	enum ObjectType {
		TypeNone,
		TypeTree
	};

	int CurrentType = TypeNone;

	if (LoadedFile.is_open())
	{
		while (LoadedFile.good())
		{
			std::getline(LoadedFile, line);
			if (line == "---====BEGIN_TREE====---")
			{
				CurrentType = TypeTree;
			}
			else if (line == "---====END_TREE====---")
			{
				CurrentType = TypeNone;
			}
			else
			{
				if (CurrentType == TypeTree)
				{

					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string PreviousWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;

						if (PreviousWord == "x:")
						{
							TempX = atoi(word.c_str());
						}

						if (PreviousWord == "y:")
						{
							TempY = atoi(word.c_str());

							trees.push_back(new Tree(TempX, TempY, CameraX, CameraY, sdl_setup));
						}

						PreviousWord = word;
					}


				}
			}
		}
	}
	else
	{
		std::cout << "File Could Not Be Open: StageLayout.txt" << std::endl;
	}
}

void Environment::SaveToFile()
{
	std::ofstream LoadedFile;
	LoadedFile.open("data/StageLayout.txt");

	LoadedFile << "---====BEGIN_TREE====---" << std::endl;

	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
	{
		LoadedFile << "x: " << (*i)->GetX() << "\ty: " << (*i)->GetY() << std::endl;

	}

	LoadedFile << "---====END_TREE====---" << std::endl;

	LoadedFile.close();

	std::cout << "Level Saved!" << std::endl;
}

void Environment::Update()
{
	if (Mode == LevelCreation)
	{

		if (sdl_setup->getMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_3)
			{
				SaveToFile();
				OnePressed = true;
			}
		}

		if (sdl_setup->getMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_3)
			{
				OnePressed = false;
			}
		}



		if (sdl_setup->getMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_1)
			{
				trees.push_back(new Tree(-*CameraX + 275, -*CameraY + 90, CameraX, CameraY, sdl_setup));
				OnePressed = true;
			}
		}

		if (sdl_setup->getMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_1)
			{
				OnePressed = false;
			}
		}




		if (sdl_setup->getMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_2)
			{
				if (trees.size() > 0)
				{

					delete trees[trees.size() - 1];

					trees.pop_back();

				}
				OnePressed = true;
			}
		}

		if (sdl_setup->getMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_2)
			{
				OnePressed = false;
			}
		}
	}


	if (sdl_setup->getMainEvent()->type == SDL_KEYDOWN)
	{
		if (!OnePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_4)
		{
			if (Mode == LevelCreation)
			{
				std::cout << "Level Creation: OFF" << std::endl;
				Mode = GamePlay;
			}
			else if (Mode == GamePlay)
			{
				std::cout << "Level Creation: ON" << std::endl;
				Mode = LevelCreation;
			}

			OnePressed = true;
		}
	}

	if (sdl_setup->getMainEvent()->type == SDL_KEYUP)
	{
		if (OnePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_4)
		{
			OnePressed = false;
		}
	}

}