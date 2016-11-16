#pragma once
#include "Ogre.h"
#include <OIS\OIS.h>
#include "System.h"

namespace Engine
{
	typedef void(*handlerFunction)(void);

	class InputHandler : public System
	{
		OIS::InputManager* inputManager;
		OIS::Keyboard* keyboard;
		OIS::Mouse* mouse;
		Ogre::RenderWindow* renderWindow;
		std::map<std::string, bool> keys;
		
		std::map<unsigned int, std::vector<handlerFunction>> handlers;
	public:
		InputHandler();

		virtual bool init() override;
		virtual bool update(float t, float dt) override;
		virtual void destroy() override;

		void clearInputs();
	};
}


