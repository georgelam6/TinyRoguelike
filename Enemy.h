#pragma once

#include <SDL2/SDL.h>

class Enemy
{
public:
	int x, y;
	int id;

	Enemy();
	Enemy(SDL_Texture *sheet, int x, int y, int id);
	void Update(int playerx, int playery, int level[16][16]);
	void Render(SDL_Renderer *renderer);

	void MoveDown(int currentLevel[16][16]);
	void MoveUp(int currentLevel[16][16]);
	void MoveLeft(int currentLevel[16][16]);
	void MoveRight(int currentLevel[16][16]);

private:
	SDL_Texture* image;
	SDL_Rect srcRect;
};

