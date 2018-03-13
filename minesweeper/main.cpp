#include "Game.h"
#include <iostream>
#include <ctime>

int main()
{
	srand((unsigned int)time(NULL));
	


	Game game;
	game.play();

	std::cin.get();
	std::cin.ignore();
	return 0;
}