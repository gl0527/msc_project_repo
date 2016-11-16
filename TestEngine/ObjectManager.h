#pragma once
#include <map>
#include "stdafx.h"
#include "IComponentFactory.h"

namespace Engine
{
	class GameObject;

	class Component;

	class DLL_SPEC ObjectManager
	{
		std::map<unsigned int, GameObject*> gameObjects;
		std::map<std::string, IComponentFactory*> componentFactories;

		ObjectManager();
		static ObjectManager* instance;
	public:
		static ObjectManager& getInstance();
		static void deleteInstance();
		static bool exists();

		void addComponentFactory(const std::string& compType, IComponentFactory* compFact);

		GameObject* createGameObject(unsigned int id);
		void removeGameObject(unsigned int id);

		Component* createComponent(const std::string& compType);

		void start();
		void preUpdate(float t, float dt);
		void update(float t, float dt);
		void postUpdate(float t, float dt);

		~ObjectManager();
	};
}


