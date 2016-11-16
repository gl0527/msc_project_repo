#include "RenderSystem.h"

namespace Engine
{
	RenderSystem::RenderSystem(const char* wName, unsigned int w, unsigned int h)
		: ogreRoot(nullptr), sceneManager(nullptr), renderWindow(nullptr), windowName(wName), windowWidth(w), windowHeight(h)
	{
	}


	bool RenderSystem::init()
	{
		ogreRoot = new Ogre::Root;
#ifdef _DEBUG
		ogreRoot->loadPlugin("RenderSystem_Direct3D9_d");
		ogreRoot->loadPlugin("RenderSystem_GL_d");
#else
		ogreRoot->loadPlugin("RenderSystem_Direct3D9");
		ogreRoot->loadPlugin("RenderSystem_GL");
#endif
		const Ogre::RenderSystemList& list = ogreRoot->getAvailableRenderers();
		
		if (!ogreRoot->showConfigDialog())
		{
			delete ogreRoot;
			return false;
		}
		ogreRoot->initialise(false);

		renderWindow = ogreRoot->createRenderWindow(windowName, windowWidth, windowHeight, false);
		sceneManager = ogreRoot->createSceneManager(0, "Default");

		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media", "FileSystem", "General", false);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		return true;
	}


	bool RenderSystem::update(float t, float dt)
	{
		if (renderWindow->isClosed())
		{
			ogreRoot->shutdown();
			return false;
		}
			
		Ogre::WindowEventUtilities::messagePump();
		
		if (!ogreRoot->renderOneFrame())
		{
			ogreRoot->shutdown();
			return false;
		}
		return true;
	}


	void RenderSystem::destroy()
	{
		sceneManager->clearScene();
	}


	void RenderSystem::createPlaneXZ(const char* planeMeshName, float u, float v)
	{
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
		Ogre::MeshManager::getSingleton().createPlane(
			planeMeshName,
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane,
			1,// x-size
			1,// z-size
			1,// x-segments
			1,// z-segments
			true,
			1,
			u, // u-tile
			v, // v-tile
			Ogre::Vector3::UNIT_Z);
	}


}

