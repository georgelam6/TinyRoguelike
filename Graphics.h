#pragma once

#include <SDL2/SDL.h>
#include <map>


class Graphics
{
public:
	SDL_Texture* sheet;
	SDL_Renderer* renderer;

	void Init(int width, int height, const char* title, int flags);
	void Clean();
	void Clear();
	void FlipBuffers();

private:
	SDL_Window* window;
	
};

