#include "HUD.h"

#include <iostream>

#include <string>

HUD::HUD() {}
std::string gh;

void HUD::Init()
{
	TTF_Init();
	this->font = TTF_OpenFont("cre.fon", 12);
	this->fontColor = { 255, 255, 255 };
	this->message = "Welcome to TinyRoguelike";

	if (!font)
		std::cout << "Unable to load font" << std::endl;
}


void HUD::Render(SDL_Renderer* renderer, int guyHealth)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->font, this->message, this->fontColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 257; // controls the rect's y coordinte
	Message_rect.w = 8*strlen(this->message); // controls the width of the rect
	Message_rect.h = 8; // controls the height of the rect

	SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(this->font, gh.c_str(), this->fontColor);
	SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);
	SDL_FreeSurface(surfaceMessage2);

	gh = "health: " + std::to_string(guyHealth);
	SDL_Rect Message_rect2; //create a rect
	Message_rect2.x = 0;  //controls the rect's x coordinate 
	Message_rect2.y = 270; // controls the rect's y coordinte
	Message_rect2.w = 9 * strlen(gh.c_str()); // controls the width of the rect
	Message_rect2.h = 9; // controls the height of the rect


	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);
	SDL_DestroyTexture(Message);
	SDL_DestroyTexture(Message2);
}

void HUD::PrintMessage(const char* m)
{
	this->message = m;
}