#include "RenderSystem.h"

namespace Engine
{
	RenderSystem::RenderSystem(const char* wName) : windowName(wName), windowWidth(800), windowHeight(600)
	{
	}

	void RenderSystem::init()
	{
		ogreRoot = new Ogre::Root("", "");
#ifdef _DEBUG
		ogreRoot->loadPlugin("RenderSystem_GL_d");
#else
		ogreRoot->loadPlugin("RenderSystem_GL");
#endif
		const Ogre::RenderSystemList& list = ogreRoot->getAvailableRenderers();
		ogreRoot->setRenderSystem(list.at(0));
		ogreRoot->initialise(false);

		renderWindow = ogreRoot->createRenderWindow(windowName, windowWidth, windowHeight, false);

		sceneManager = ogreRoot->createSceneManager(0, "Default");

		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media", "FileSystem", "General", false);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void RenderSystem::update(float t, float dt)
	{
		if (renderWindow->isClosed())
			ogreRoot->shutdown();

		Ogre::WindowEventUtilities::messagePump();
		
		if (!ogreRoot->renderOneFrame())
			ogreRoot->shutdown();
	}

	void RenderSystem::destroy()
	{
		sceneManager->clearScene();
	}
}

