#pragma once
#include "Ticker.h"

namespace Engine
{
	class Game
	{
		Ticker* timer;
		bool inited;
		bool running;
		bool destroyed;
	public:
		Game();

		void init();
		void start();
		void pause();
		void mainLoop();
		void update(float t, float dt);
		void destroy();

		~Game();
	};
}

