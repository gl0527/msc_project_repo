#include "TestEngine.h"

using namespace Engine;

int main(int argc, char** argv)
{
	Game* game = new Game();

	game->init();
	game->start();
	game->destroy();

	delete game;

	return 0;
}