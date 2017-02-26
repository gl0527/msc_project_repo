#pragma once
#include <map>
#include <memory>
#include "stdafx.h"

namespace Engine
{
	class GameObject;

	class DLL_SPEC ObjectManager
	{
		std::map<std::string, GameObject_sptr> gameObjects;
		ObjectManager();
		static ObjectManager* instance;
	public:
		static ObjectManager& getInstance();
		static void deleteInstance();
		static bool exists();

		const GameObject_sptr& createGameObject(const std::string& id);
		void removeGameObject(const std::string& id);

		void start();
		void preUpdate(float t, float dt);
		void update(float t, float dt);
		void postUpdate(float t, float dt);
		void destroy();

		const GameObject_sptr& getGameObject(const std::string& objName) const { return gameObjects.at(objName); }

		~ObjectManager();
	};
}


