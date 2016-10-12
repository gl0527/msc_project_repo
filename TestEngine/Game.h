#pragma once
#include "Ticker.h"
#include "stdafx.h"

namespace Engine
{
	class DLL_SPEC Game
	{
		Ticker* timer;
		bool inited;
		bool running;
		bool destroyed;

		void mainLoop();
		void update(float t, float dt);
	public:
		Game();

		void init();
		void start();
		void pause();
		void destroy();

		~Game();
	};
}

