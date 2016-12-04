#pragma once
#include "System.h"
#include "Ogre.h"
#include "OGRE\Overlay\OgreOverlayManager.h"
#include "OGRE\Overlay\OgreOverlaySystem.h"
#include "stdafx.h"

namespace Engine
{
	class DLL_SPEC GUI : public System
	{
		Ogre::SceneManager* sceneManager;
		Ogre::OverlaySystem* overlaySystem;
		Ogre::OverlayManager* overlayManager;
	public:
		GUI();
		~GUI();

		virtual bool init() override;
		virtual bool update(float t, float dt) override;
		virtual void destroy() override;

		Ogre::OverlayElement* getOverlayElement(const char* elementName) const;
		Ogre::Overlay* getOverlay(const char* overlayName) const;
		Ogre::OverlayContainer* getContainer(const char* containerName) const;
	};
}


