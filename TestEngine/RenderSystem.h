#pragma once
#include "System.h"
#include "Ogre.h"
#include "OGRE\Overlay\OgreOverlayManager.h"
#include "OGRE\Overlay\OgreOverlaySystem.h"
#include "stdafx.h"

namespace Engine
{
	class DLL_SPEC RenderSystem : public System
	{
		Ogre::Root* ogreRoot;
		Ogre::SceneManager* sceneManager;
		Ogre::RenderWindow* renderWindow;
		Ogre::OverlaySystem* overlaySystem;
		Ogre::OverlayManager* overlayManager;
		std::string windowName;
		unsigned int windowWidth;
		unsigned int windowHeight;
	public:
		RenderSystem(const char* wName, unsigned int w = 800, unsigned int h = 600);

		virtual bool init() override;
		virtual bool update(float t, float dt) override;
		virtual void destroy() override;

		void createPlaneMeshXZ(const char* planeMeshName, float y, unsigned int u = 1, unsigned int v = 1);
		
		Ogre::Root* getRoot() const { return ogreRoot; }
		Ogre::SceneNode* getRootNode() const { return sceneManager->getRootSceneNode(); }
		Ogre::SceneManager* getSceneManager() const { return sceneManager; }
		Ogre::RenderWindow* getRenderWindow() const { return renderWindow; }

		Ogre::OverlayElement* getOverlayElement(const char* elementName) const;
		Ogre::Overlay* getOverlay(const char* overlayName) const;
		Ogre::OverlayContainer* getContainer(const char* containerName) const;
	};
}


