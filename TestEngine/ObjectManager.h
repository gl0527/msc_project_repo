#pragma once
#include <map>
#include <memory>
#include "stdafx.h"

namespace Engine
{
	class GameObject;

	class DLL_SPEC ObjectManager
	{
		std::map<unsigned int, std::shared_ptr<GameObject>> gameObjects;
		ObjectManager();
		static ObjectManager* instance;
	public:
		static ObjectManager& getInstance();
		static void deleteInstance();
		static bool exists();

		GameObject* createGameObject(unsigned int id);
		void removeGameObject(unsigned int id);

		void start();
		void preUpdate(float t, float dt);
		void update(float t, float dt);
		void postUpdate(float t, float dt);
		void destroy();

		~ObjectManager();
	};
}


