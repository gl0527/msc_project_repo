#include "stdafx.h"
#include "Game.h"

namespace Engine
{
	Game* Game::instance = nullptr;
	

	Game::Game(const char* title)
		: inited(false), running(false), destroyed(false), renderSystem(nullptr), physicsSystem(nullptr), 
		inputHandler(nullptr), timer(nullptr)
	{
		renderSystem = new RenderSystem(title);
		physicsSystem = new PhysicsSystem();
		inputHandler = new InputHandler();
		timer = new Ticker();
	}


	Game& Game::getInstance()
	{
		if (instance == nullptr)
			instance = new Game("Project lab Gurzo Lajos");
		return *instance;
	}


	void Game::deleteInstance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}


	void Game::init()
	{
		physicsSystem->init();
		renderSystem->init();
		//inputHandler->init();
		inited = true;
	}


	void Game::start()
	{
		if (running)
			return;
		if (!inited)
			init();
		else
			timer->pause();
		running = true;
		mainLoop();
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
		//inputHandler->update(t, dt);
		physicsSystem->update(t, dt);
		renderSystem->update(t, dt);
	}


	void Game::destroy()
	{
		if (timer)
		{
			delete timer;
			timer = nullptr;
		}
		//inputHandler->destroy();
		renderSystem->destroy();
		physicsSystem->destroy();
	}


}
