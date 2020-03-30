#pragma once

#include <SDL2/SDL.h>

#include <list>
#include "Enemy.h"
#include "Level.h"
#include "HUD.h"

class Dude
{
public:
	int x, y, w, h;
	int health;
	bool isDead;

	Dude();
	Dude(SDL_Texture *spritesheet);
	void FixedUpdate(HUD& hud);
	void Update(std::vector<Enemy>& enemies, Level& level, HUD& hud);
	void Render(SDL_Renderer *renderer);
	void MoveDown(int currentLevel[16][16]);
	void MoveUp(int currentLevel[16][16]);
	void MoveLeft(int currentLevel[16][16]);
	void MoveRight(int currentLevel[16][16]);

private:
	SDL_Rect srcRect;
	SDL_Texture* image;

	bool lastAttack;
};

