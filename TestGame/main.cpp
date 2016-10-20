#include "TestEngine.h"

using namespace Engine;

int main(int argc, char** argv)
{
	Game::getInstance().init();
	Game::getInstance().start();
	Game::getInstance().destroy();

	return 0;
}