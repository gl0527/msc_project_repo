#pragma once
#include "System.h"
#include "Ogre.h"
#include "stdafx.h"

namespace Engine
{
	class DLL_SPEC RenderSystem : public System
	{
		Ogre::Root* ogreRoot;
		Ogre::SceneManager* sceneManager;
		Ogre::RenderWindow* renderWindow;
		std::string windowName;
		unsigned int windowWidth;
		unsigned int windowHeight;
	public:
		RenderSystem(const char* wName, unsigned int w = 800, unsigned int h = 600);

		virtual bool init() override;
		virtual bool update(float t, float dt) override;
		virtual void destroy() override;

		void createPlaneXZ(const char* planeMeshName, float u, float v);
		
		Ogre::Root* getRoot() const { return ogreRoot; }
		Ogre::SceneNode* getRootNode() const { return sceneManager->getRootSceneNode(); }
		Ogre::SceneManager* getSceneManager() const { return sceneManager; }
		Ogre::RenderWindow* getRenderWindow() const { return renderWindow; }
	};
}


