#include "Game.h"


int main(int argc, char* argv[])
{
	Game game;

	game.Init();
	while (game.running)
	{
		game.HandleEvents();
		game.Update();
		game.Render();
	}
	game.Quit();

	return 0;

}