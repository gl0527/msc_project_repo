#pragma once
#include "System.h"
#include "Ogre.h"

namespace Engine
{
	class RenderSystem : public System
	{
		Ogre::Root* ogreRoot;
		Ogre::SceneManager* sceneManager;
		Ogre::RenderWindow* renderWindow;
		std::string windowName;
		unsigned int windowWidth;
		unsigned int windowHeight;
	public:
		RenderSystem(const char* wName);

		void init() override;
		void update(float t, float dt) override;
		void destroy() override;
	};
}


