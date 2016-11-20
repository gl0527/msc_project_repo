#pragma once
#include "Ogre.h"
#include <OIS\OIS.h>
#include "System.h"
#include "stdafx.h"

namespace Engine
{
	class DLL_SPEC InputHandler : public System
	{
		OIS::InputManager* inputManager;
		OIS::Keyboard* keyboard;
		OIS::Mouse* mouse;
		Ogre::RenderWindow* renderWindow;
	public:
		InputHandler();

		virtual bool init() override;
		virtual bool update(float t, float dt) override;
		virtual void destroy() override;

		bool isKeyDown(OIS::KeyCode key) const;
		const OIS::MouseState& getMouseState() const;
	};
}


