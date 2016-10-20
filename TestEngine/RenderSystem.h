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

		virtual void init() override;
		virtual void update(float t, float dt) override;
		virtual void destroy() override;

		Ogre::Root* getRoot() const { return ogreRoot; }
		Ogre::SceneNode* getRootNode() const { return sceneManager->getRootSceneNode(); }
		Ogre::SceneManager* getSceneManager() const { return sceneManager; }
		Ogre::RenderWindow* getRenderWindow() const { return renderWindow; }
	};
}


