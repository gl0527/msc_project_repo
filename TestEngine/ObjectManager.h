#pragma once
#include <map>
#include <memory>
#include "stdafx.h"

namespace Engine
{
	class GameObject;

	class DLL_SPEC ObjectManager
	{
		std::map<std::string, std::shared_ptr<GameObject>> gameObjects;
		ObjectManager();
		static ObjectManager* instance;
	public:
		static ObjectManager& getInstance();
		static void deleteInstance();
		static bool exists();

		GameObject* createGameObject(const std::string& id);
		void removeGameObject(const std::string& id);

		void start();
		void preUpdate(float t, float dt);
		void update(float t, float dt);
		void postUpdate(float t, float dt);
		void destroy();

		GameObject* getGameObject(const std::string& objName) const { return gameObjects.at(objName).get(); }

		~ObjectManager();
	};
}


