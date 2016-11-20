#include "stdafx.h"
#include "Game.h"
#include "ObjectManager.h"

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


	bool Game::exists()
	{
		return (instance != nullptr);
	}


	bool Game::init()
	{		
		inited = physicsSystem->init() && renderSystem->init() && inputHandler->init();
		return inited;
	}


	void Game::start()
	{
		if (running)
			return;
		if (!inited)
			if (!init())
			{
				destroy();
				return;
			}
		else
			timer->pause();
		running = true;
		if (inited)
			ObjectManager::getInstance().start();
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
				if (!update(t, dt))
					destroy();
			}
		}
	}


	bool Game::update(float t, float dt)
	{		
		if (!inputHandler->update(t, dt))
			return false;
	
		ObjectManager::getInstance().preUpdate(t, dt); // fizika elotti teendok befrissitese
			
		if (!physicsSystem->update(t, dt)) // fizikai rendszer befrissitese
			return false;

		ObjectManager::getInstance().update(t, dt); // fizika befrissitese
			
		ObjectManager::getInstance().postUpdate(t, dt); // fizika utani teendok elvegzese
			
		if (!renderSystem->update(t, dt)) // kirajzolas
			return false;
		
		return true;
	}


	void Game::destroy()
	{
		if (timer)
		{
			delete timer;
			timer = nullptr;
		}
		inputHandler->destroy();
		renderSystem->destroy();
		physicsSystem->destroy();

		//deleteInstance();
	}


}
