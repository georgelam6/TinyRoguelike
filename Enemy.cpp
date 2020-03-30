#include "Enemy.h"

#include "globals.h"

Enemy::Enemy() {}
Enemy::Enemy(SDL_Texture* sheet, int x, int y, int id) :
	x(x),
	y(y),
	image(sheet),
	id(id)
{
	this->srcRect = { 8, 0, 8, 8 };
}

void Enemy::Update(int playerx, int playery, int level[16][16])
{
	if (playerx < this->x)
	{
		MoveLeft(level);
	}
	else if (playerx > this->x)
	{
		MoveRight(level);
	}
	else if (playery > this->y)
	{
		MoveDown(level);
	}
	else if (playery < this->y)
	{
		MoveUp(level);
	}
}

void Enemy::Render(SDL_Renderer *renderer)
{
	SDL_Rect destRect = { this->x * Globals::GRID_CELL_SIZE, this->y * Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE };
	SDL_RenderCopy(renderer, this->image, &this->srcRect, &destRect);
}

void Enemy::MoveDown(int currentLevel[16][16])
{
	int predictedLocation = this->y + 1;
	if (currentLevel[predictedLocation][this->x] != 1)
	{
		this->y = predictedLocation;
	}
}

void Enemy::MoveUp(int currentLevel[16][16])
{
	int predictedLocation = this->y - 1;
	if (currentLevel[predictedLocation][this->x] != 1)
	{
		this->y = predictedLocation;
	}
}

void Enemy::MoveLeft(int currentLevel[16][16])
{
	int predictedLocation = this->x - 1;
	if (currentLevel[this->y][predictedLocation] != 1)
	{
		this->x = predictedLocation;
	}
}

void Enemy::MoveRight(int currentLevel[16][16])
{
	int predictedLocation = this->x + 1;
	if (currentLevel[this->y][predictedLocation] != 1)
	{
		this->x = predictedLocation;
	}
}