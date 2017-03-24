#pragma once
#include <map>
#include <memory>
#include "stdafx.h"

namespace Engine
{
	class GameObject;

	typedef std::map<std::string, GameObject_sptr> GameObjectMap;

	class DLL_SPEC ObjectManager
	{
		GameObjectMap gameObjects;
		ObjectManager();
		static ObjectManager* instance;
	public:
		static ObjectManager& getInstance();
		static void deleteInstance();
		static bool exists();

		GameObject_wptr createGameObject(const std::string& id);
		void removeGameObject(const std::string& id);

		void start();
		void preUpdate(float t, float dt);
		void update(float t, float dt);
		void postUpdate(float t, float dt);
		void destroy();

		GameObject_wptr getGameObject(const std::string& objName) const;

		~ObjectManager();
	};
}


