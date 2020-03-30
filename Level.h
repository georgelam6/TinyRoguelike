#pragma once

#include <SDL2/SDL.h>
#include "Enemy.h"
#include <vector>

class Level
{
public:
	Level();
	Level(SDL_Texture* spritesheet);
	void CreateLevel();
	void Render(SDL_Renderer* renderer);
	void Update(int px, int py);
	void RemoveEnemy(Enemy enemy);
	bool LevelContains(int thing);
	int Random(int min, int max);
	void EatFood(int x, int y);


	int currentLevel[16][16];
	std::vector<Enemy> enemies;

	int endx, endy;
	int foodx, foody;

private:
	SDL_Texture* image;
	SDL_Rect wallSrcRect;
	SDL_Rect enemySrcRect;
	SDL_Rect stairSrcRect;
	SDL_Rect foodSrcRect;
	SDL_Rect doorSrcRect;

	int template00[16][16] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
};

