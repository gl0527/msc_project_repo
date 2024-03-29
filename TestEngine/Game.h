#pragma once
#include "Ticker.h"
#include "stdafx.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "InputHandler.h"
#include "AudioSystem.h"
#include "XMLParser.h"

namespace Engine
{
	class DLL_SPEC Game
	{
		bool inited;
		bool running;
		bool destroyed;

		RenderSystem* renderSystem;
		PhysicsSystem* physicsSystem;
		InputHandler* inputHandler;
		AudioSystem* audioSystem;
		Ticker* timer;

		void mainLoop();
		bool update(float t, float dt);

		static Game* instance;
		Game(const char* title);
	public:
		static Game& getInstance();
		static void deleteInstance();
		static bool exists();

		bool init();
		void start();
		void pause();
		void destroy();

		RenderSystem* getRenderSystem() const { return renderSystem; }
		PhysicsSystem* getPhysicsSystem() const { return physicsSystem; }
		InputHandler* getInputHandler() const { return inputHandler; }
		AudioSystem* getAudioSystem() const { return audioSystem; }
	};
}

