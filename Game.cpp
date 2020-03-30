#include "Game.h"

#include <SDL2/SDL.h>
#include "globals.h"

#include "Dude.h"
#include "Level.h"
#include "Enemy.h"
#include "HUD.h"

#include <iostream>

Dude guy;
Level level;
HUD hud;
bool turn = false;

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	this->graphics.Init(Globals::SCR_SIZE, Globals::SCR_SIZE + 32, "TinyRoguelike", NULL);
	
	guy = Dude(this->graphics.sheet);
	level = Level(this->graphics.sheet);

	hud.Init();
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	
	if (event.type == SDL_QUIT)
	{
		this->running = false;
	}

	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			guy.MoveUp(level.currentLevel);
			turn = true;
			break;
		case SDLK_DOWN:
			guy.MoveDown(level.currentLevel);
			turn = true;
			break;
		case SDLK_LEFT:
			guy.MoveLeft(level.currentLevel);
			turn = true;
			break;
		case SDLK_RIGHT:
			guy.MoveRight(level.currentLevel);
			turn = true;
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	guy.FixedUpdate(hud);

	// Start the turn
	if (turn)
	{
		if (!guy.isDead)
		{
			level.Update(guy.x, guy.y);
			guy.Update(level.enemies, level, hud);
		}

		// End the turn
		turn = false;
	}
}

void Game::Render()
{
	this->graphics.Clear();

	if (!guy.isDead)
	{
		// stuff to render 
		guy.Render(this->graphics.renderer);
		level.Render(this->graphics.renderer);
	}
	hud.Render(this->graphics.renderer, guy.health);

	this->graphics.FlipBuffers();
}

void Game::Quit()
{
	this->graphics.Clean();
	SDL_Quit();
}