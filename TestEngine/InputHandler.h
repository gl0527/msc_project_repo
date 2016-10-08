#pragma once
#include <OIS\OIS.h>

namespace Engine
{
	class InputHandler
	{
		OIS::InputManager* inputManager;
		OIS::Keyboard* keyboard;
		OIS::Mouse* mouse;
	public:
		InputHandler();
		~InputHandler();
	};
}


