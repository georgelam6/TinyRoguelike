#include "Level.h"

#include "globals.h"

#include <iostream>
#include <ctime>
#include <cstdlib>


Level::Level() {}
Level::Level(SDL_Texture* spritesheet)
{
	this->CreateLevel();
	this->image = spritesheet;
	this->wallSrcRect = { 16, 0, 8, 8 };
	this->enemySrcRect = { 8, 0, 8, 8 };
	this->stairSrcRect = { 25, 0, 8, 8 };
	this->foodSrcRect = { 48, 0, 8, 8 };
	this->doorSrcRect = { 32, 0, 8, 8 };
}

int Level::Random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

bool Level::LevelContains(int thing)
{
	for (int row = 0; row < 16; row++)
	{
		for (int col = 0; col < 16; col++)
		{
			int type = this->currentLevel[row][col];
			if (type == thing)
			{
				return true;
			}
		}
	}
	return false;
}

void Level::CreateLevel()
{
	// Reset level
	for (int row = 0; row < 16; row++)
	{
		for (int col = 0; col < 16; col++)
		{
			this->currentLevel[row][col] = 0;
		}
	}
	this->enemies.clear();
	foodx = foody = 0;


	int count = 0;
	for (int row = 0; row < 16; row++)
	{
		for (int col = 0; col < 16; col++)
		{
			this->currentLevel[row][col] = template00[row][col];

			int type = template00[row][col];

			//if (type == 2)
			//{
				//count++;
				//Enemy e = Enemy(this->image, row, col, count);
				//this->enemies.push_back(e);
			//}

			// spawn enemies
			if (Random(1, 60) == 1 && currentLevel[row][col] == 0)
			{
				count++;
				Enemy e = Enemy(this->image, col, row, count);
				this->enemies.push_back(e);
			}

			// spawn walls
			if (Random(1, 50) == 1 && row != 2 && col != 2)
			{
				this->currentLevel[row][col] = 1;
			}

			// spawn the stairs
			if (Random(1, 30) == 1 && row != 2 && col != 0 && !LevelContains(3) && currentLevel[row][col] == 0)
			{
				this->currentLevel[row][col] = 3;
				endx = col;
				endy = row;
			}

			// spawn a food
			if (Random(1, 60) == 1 && row != 2 && col != 0 && !LevelContains(4) && currentLevel[row][col] == 0)
			{
				this->currentLevel[row][col] = 4;
				foodx = col;
				foody = row;
			}
		}
	}
}

void Level::Render(SDL_Renderer *renderer)
{
	int type = 0;

	for (int row = 0; row < 16; row++)
	{
		for (int col = 0; col < 16; col++)
		{
			type = this->currentLevel[row][col];

			if (type == 1)
			{
				SDL_Rect destRect = { col * Globals::GRID_CELL_SIZE, row * Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE ,Globals::GRID_CELL_SIZE };
				SDL_RenderCopy(renderer, this->image, &this->wallSrcRect, &destRect);
			}
			else if (type == 3)
			{
				SDL_Rect destRect = { col * Globals::GRID_CELL_SIZE, row * Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE ,Globals::GRID_CELL_SIZE };
				SDL_RenderCopy(renderer, this->image, &this->stairSrcRect, &destRect);
			}
			else if (type == 4)
			{
				SDL_Rect destRect = { col * Globals::GRID_CELL_SIZE, row * Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE ,Globals::GRID_CELL_SIZE };
				SDL_RenderCopy(renderer, this->image, &this->foodSrcRect, &destRect);
			}
			else if (type == 5)
			{
				SDL_Rect destRect = { col * Globals::GRID_CELL_SIZE, row * Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE ,Globals::GRID_CELL_SIZE };
				SDL_RenderCopy(renderer, this->image, &this->doorSrcRect, &destRect);
			}
		}
	}

	for (auto& e : this->enemies)
	{
		SDL_Rect destRect = { e.x * Globals::GRID_CELL_SIZE, e.y * Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE };
		SDL_RenderCopy(renderer, this->image, &enemySrcRect, &destRect);
	}
}

void Level::Update(int px, int py)
{
	for (auto& e : this->enemies)
	{
		e.Update(px, py, this->currentLevel);
	}
}

void Level::RemoveEnemy(Enemy enemy)
{
	std::vector<Enemy> tempList;

	for (auto& e : this->enemies)
	{
		if (enemy.id != e.id)
		{
			tempList.push_back(e);
		}
		else
		{
			std::cout << "You slayed the skeleton" << std::endl;
		}
	}

	this->enemies = tempList;

}

void Level::EatFood(int x, int y)
{
	this->currentLevel[y][x] = 0;
	foodx = foody = 0;
	std::cout << "You ate some food. It tasted good for something that you found on the floor." << std::endl;
}