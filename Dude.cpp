#include "Dude.h"

#include "globals.h"

#include <iostream>

Dude::Dude() {}
Dude::Dude(SDL_Texture* spritesheet) :
	x(2),
	y(2),
	w(8),
	h(8),
	health(100)
{
	this->srcRect = { 0, 0, w, h };
	this->image = spritesheet;
	lastAttack = true;
	isDead = false;
}

void Dude::FixedUpdate(HUD& hud)
{
	if (health <= 0)
	{
		isDead = true;
		hud.PrintMessage("Oof. You died");
	}
}



void Dude::Update(std::vector<Enemy>& enemies, Level& level, HUD& hud)
{

	for (Enemy& e : enemies)
	{
		if (e.x == this->x && e.y == this->y)
		{
			if (lastAttack)
			{
				lastAttack = false;
				this->health -= level.Random(1, 30);
				hud.PrintMessage("A skeleton attacked you.");
			}
			else
			{
				lastAttack = true;
				level.RemoveEnemy(e);
				hud.PrintMessage("You slayed the skeleton");
			}
		}
	}

	if (level.endx == this->x && level.endy == this->y)
	{
		level.CreateLevel();
		this->x = 2;
		this->y = 2;
	}

	if (level.foodx == this->x && level.foody == this->y)
	{
		this->health += level.Random(2, 30);
		level.EatFood(level.foodx, level.foody);
		hud.PrintMessage("You ate something off the floor.");
		if (this->health > 100)
		{
			this->health = 100;
		}
	}
}

void Dude::Render(SDL_Renderer *renderer)
{
	SDL_Rect destRect = { this->x * Globals::GRID_CELL_SIZE, this->y * Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE, Globals::GRID_CELL_SIZE };
	SDL_RenderCopy(renderer, this->image, &this->srcRect, &destRect);
}

void Dude::MoveDown(int currentLevel[16][16])
{
	int predictedLocation = this->y + 1;
	if (currentLevel[predictedLocation][this->x] != 1)
	{
		this->y = predictedLocation;
	}
}

void Dude::MoveUp(int currentLevel[16][16])
{
	int predictedLocation = this->y - 1;
	if (currentLevel[predictedLocation][this->x] != 1)
	{
		this->y = predictedLocation;
	}
}

void Dude::MoveLeft(int currentLevel[16][16])
{
	int predictedLocation = this->x - 1;
	if (currentLevel[this->y][predictedLocation] != 1)
	{
		this->x = predictedLocation;
	}
}

void Dude::MoveRight(int currentLevel[16][16])
{
	int predictedLocation = this->x + 1;
	if (currentLevel[this->y][predictedLocation] != 1)
	{
		this->x = predictedLocation;
	}
}