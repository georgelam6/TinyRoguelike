#include "Graphics.h"

#include <SDL2/SDL_image.h>

#include <iostream>

void Graphics::Init(int width, int height, const char *title, int flags)
{
	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	this->renderer = SDL_CreateRenderer(this->window, NULL, NULL);

	if (!this->window || !this->renderer)
	{
		std::cout << "Unable to create window/renderer" << std::endl;
		SDL_Quit();
		return;
	}

	// Load the single spritesheet
	SDL_Surface* tmpSurf;
	tmpSurf = IMG_Load("MySheet.png");
	this->sheet = SDL_CreateTextureFromSurface(this->renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);
}

void Graphics::Clean()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}

void Graphics::Clear()
{
	SDL_RenderClear(this->renderer);
}

void Graphics::FlipBuffers()
{
	SDL_RenderPresent(this->renderer);
}