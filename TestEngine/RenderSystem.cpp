#include "RenderSystem.h"

namespace Engine
{
	RenderSystem::RenderSystem(const char* wName, unsigned int w, unsigned int h)
		: ogreRoot(nullptr),
		sceneManager(nullptr),
		renderWindow(nullptr),
		overlaySystem(nullptr),
		overlayManager(nullptr),
		windowName(wName),
		windowWidth(w),
		windowHeight(h)
	{
	}


	bool RenderSystem::init()
	{
		ogreRoot = new Ogre::Root;
#ifdef _DEBUG
		ogreRoot->loadPlugin("RenderSystem_Direct3D9_d");
		ogreRoot->loadPlugin("RenderSystem_GL_d");
		ogreRoot->loadPlugin("Plugin_ParticleFX_d");
#else
		ogreRoot->loadPlugin("RenderSystem_Direct3D9");
		ogreRoot->loadPlugin("RenderSystem_GL");
		ogreRoot->loadPlugin("Plugin_ParticleFX");
#endif
		const Ogre::RenderSystemList& list = ogreRoot->getAvailableRenderers();
		
		if (!ogreRoot->showConfigDialog())
		{
			delete ogreRoot;
			return false;
		}
		ogreRoot->initialise(false);

		renderWindow = ogreRoot->createRenderWindow(windowName, windowWidth, windowHeight, false);
		sceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);

		overlaySystem = new Ogre::OverlaySystem();
		sceneManager->addRenderQueueListener(overlaySystem);
		overlayManager = Ogre::OverlayManager::getSingletonPtr();

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
		if (overlaySystem)
		{
			delete overlaySystem;
			overlaySystem = nullptr;
		}
		if (sceneManager)
		{
			sceneManager->clearScene();
		}
		if (ogreRoot)
		{
			delete ogreRoot;
			ogreRoot = nullptr;
		}
	}


	void RenderSystem::createPlaneMeshXZ(const char* planeMeshName, float y, unsigned int u, unsigned int v)
	{
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y, y);
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


	Ogre::OverlayElement* RenderSystem::getOverlayElement(const char* elementName) const
	{
		return overlayManager->getOverlayElement(elementName);
	}
	
	
	Ogre::Overlay* RenderSystem::getOverlay(const char* overlayName) const
	{
		return overlayManager->getByName(overlayName);
	}


	Ogre::OverlayContainer* RenderSystem::getContainer(const char* containerName) const
	{
		return static_cast<Ogre::OverlayContainer*>(overlayManager->getOverlayElement(containerName));
	}
}

