#pragma once

#include "Graphics.h"


class Game
{
public:
	bool running;

	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Quit();
	
private:
	Graphics graphics;
};

