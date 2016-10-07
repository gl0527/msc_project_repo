#include "stdafx.h"
#include "Game.h"

namespace Engine
{
	Game::Game() : inited(false), running(false), destroyed(false)
	{
		timer = new Ticker();
	}

	void Game::init()
	{

	}

	void Game::start()
	{

	}

	void Game::pause()
	{
		if (running)
			running = false;
		else if (inited)
			start();
	}

	void Game::mainLoop()
	{
		while (timer)
		{
			if (running)
			{
				timer->tick();
				float dt = timer->elapsedTime();
				float t = timer->uptime();
				update(t, dt);
			}
		}
	}

	void Game::update(float t, float dt)
	{

	}

	void Game::destroy()
	{

	}

	Game::~Game()
	{
	}
}
