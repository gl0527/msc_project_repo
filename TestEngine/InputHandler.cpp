#include "InputHandler.h"
#include <sstream>
#include "Game.h"

namespace Engine
{
	InputHandler::InputHandler()
		: inputManager(nullptr),
		keyboard(nullptr),
		mouse(nullptr),
		renderWindow(nullptr)
	{
		
	}


	bool InputHandler::init()
	{
		OIS::ParamList pl;
		size_t windowHnd = 0;
		renderWindow = Game::getInstance().getRenderSystem()->getRenderWindow();
		renderWindow->getCustomAttribute("WINDOW", &windowHnd);
		std::ostringstream windowHndStr;
		windowHndStr << windowHnd;

		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		// kurzor megjelenítése
//#if defined OIS_WIN32_PLATFORM
//		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
//		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
//		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
//		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
//#elif defined OIS_LINUX_PLATFORM
//		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
//		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
//		pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
//		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
//#endif
		inputManager = OIS::InputManager::createInputSystem(pl);
		keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, false)); // unbuffered keyboard
		mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, false)); // unbuffered mouse

		return true;
	}


	bool InputHandler::update(float t, float dt)
	{
		if (keyboard && mouse)
		{
			keyboard->capture();
			mouse->capture();
		}
		else
			return false;

		const OIS::MouseState& ms = mouse->getMouseState();
		ms.width = renderWindow->getViewport(0)->getActualWidth();
		ms.height = renderWindow->getViewport(0)->getActualHeight();

		return true;
	}


	bool InputHandler::isKeyDown(OIS::KeyCode key) const
	{
		if (keyboard)
			return keyboard->isKeyDown(key);
		else
			return false;
	}

	const OIS::MouseState& InputHandler::getMouseState() const
	{
		if (mouse)
			return mouse->getMouseState();
	}


	void InputHandler::destroy()
	{
		if (inputManager) 
		{
			if (mouse)
			{
				inputManager->destroyInputObject(mouse);
				mouse = nullptr;
			}
			if (keyboard)
			{
				inputManager->destroyInputObject(keyboard);
				keyboard = nullptr;
			}
			inputManager->destroyInputSystem(inputManager);
			inputManager = nullptr;
		}
	}


}

