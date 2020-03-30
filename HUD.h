#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class HUD
{
public:
	HUD();
	void Init();

	void Render(SDL_Renderer* renderer, int guyHealth);

	void PrintMessage(const char* m);
private:
	TTF_Font* font;
	SDL_Color fontColor;
	const char* message;
};

