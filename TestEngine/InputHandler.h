#pragma once
#include "Ogre.h"
#include <OIS\OIS.h>
#include "System.h"

namespace Engine
{
	class InputHandler : public System
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

		bool isKeyDown(OIS::KeyCode key) const { return keyboard->isKeyDown(key); }
		const OIS::MouseState& getMouseState() const { return mouse->getMouseState(); }
	};
}


