#include "InputHandler.h"
#include <sstream>

namespace Engine
{
	InputHandler::InputHandler(Ogre::RenderWindow* rw)
		: inputManager(nullptr), keyboard(nullptr), mouse(nullptr), renderWindow(rw)
	{
		keys["left"] = false;
		keys["right"] = false;
		keys["up"] = false;
		keys["down"] = false;
		keys["zoomIn"] = false;
		keys["zoomOut"] = false;
		keys["quit"] = false;

		
	}

	void InputHandler::init()
	{
		OIS::ParamList pl;
		size_t windowHnd = 0;
		renderWindow->getCustomAttribute("WINDOW", &windowHnd);
		std::ostringstream windowHndStr;
		windowHndStr << windowHnd;

		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		// kurzor megjelenítése
#if defined OIS_WIN32_PLATFORM
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
		inputManager = OIS::InputManager::createInputSystem(pl);
		keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, false)); // unbuffered keyboard
		mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, false)); // unbuffered mouse
	}

	void InputHandler::update(float t, float dt)
	{
		keyboard->capture();
		mouse->capture();

		if (keyboard->isKeyDown(OIS::KC_ESCAPE))
			keys["quit"] = true;

		if (keyboard->isKeyDown(OIS::KC_DOWN))
			keys["down"] = true;

		const OIS::MouseState& ms = mouse->getMouseState();
		ms.width = renderWindow->getViewport(0)->getActualWidth();
		ms.height = renderWindow->getViewport(0)->getActualHeight();
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

	void InputHandler::clearInputs()
	{
		for (auto it = keys.begin(); it != keys.end(); ++it)
			it->second = false;
		
	}
}

