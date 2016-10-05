#pragma once
#include <vector>

namespace Engine
{
	class GameObject;

	class ObjectManager
	{
		std::vector<GameObject*> gameObjects;
	public:
		ObjectManager();

		void addGameObject(GameObject* object);
		void removeGameObject(GameObject* object);

		~ObjectManager();
	};
}


