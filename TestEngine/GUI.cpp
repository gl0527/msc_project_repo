#include "GUI.h"
#include "Game.h"
#include "OGRE\Overlay\OgreOverlay.h"
#include "OGRE\Overlay\OgreOverlaySystem.h"

namespace Engine
{
	GUI::GUI() : sceneManager(nullptr), overlaySystem(nullptr), overlayManager(nullptr)
	{
	}


	GUI::~GUI()
	{
	}


	bool GUI::init()
	{
		sceneManager = Game::getInstance().getRenderSystem()->getSceneManager();
		overlaySystem = new Ogre::OverlaySystem();
		sceneManager->addRenderQueueListener(overlaySystem);
		overlayManager = Ogre::OverlayManager::getSingletonPtr();
		return true;
	}


	bool GUI::update(float t, float dt)
	{
		return true;
	}


	void GUI::destroy()
	{
		// TODO: kaka
	}


	Ogre::OverlayElement* GUI::getOverlayElement(const char* elementName) const
	{
		return overlayManager->getOverlayElement(elementName);
	}


	Ogre::Overlay* GUI::getOverlay(const char* overlayName) const
	{
		return overlayManager->getByName(overlayName);
	}


	Ogre::OverlayContainer* GUI::getContainer(const char* containerName) const
	{
		return static_cast<Ogre::OverlayContainer*>(overlayManager->getOverlayElement(containerName));
	}
}

