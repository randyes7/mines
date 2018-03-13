#include "Game.h"
#include <iostream>
#include <ctime>

int main()
{
	srand((unsigned int)time(NULL));

	// random comment
	// also random comment

	Game game;
	game.play();

	std::cin.get();
	std::cin.ignore();
	return 0;
}