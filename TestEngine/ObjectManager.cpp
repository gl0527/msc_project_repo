#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"

namespace Engine
{
	ObjectManager* ObjectManager::instance = nullptr;

	ObjectManager::ObjectManager()
	{
	}


	ObjectManager& ObjectManager::getInstance()
	{
		if (instance == nullptr)
			instance = new ObjectManager();
		return *instance;
	}

	
	void ObjectManager::deleteInstance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}


	bool ObjectManager::exists()
	{
		return (instance != nullptr);
	}


	const GameObject_sptr& ObjectManager::createGameObject(const std::string& id)
	{
		if (gameObjects.find(id) == gameObjects.end())
		{
			gameObjects[id] = std::shared_ptr<GameObject>(new GameObject(id));
			return gameObjects[id];
		}
		return nullptr;
	}


	void ObjectManager::removeGameObject(const std::string& id)
	{
		gameObjects.erase(id);
	}


	void ObjectManager::start()
	{
		for (auto&& it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->onStart();
		}
	}


	void ObjectManager::preUpdate(float t, float dt)
	{
		for (auto&& it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->onPreUpdate(t, dt);
		}
	}


	void ObjectManager::update(float t, float dt)
	{
		for (auto&& it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->onUpdate(t, dt);
		}
	}


	void ObjectManager::postUpdate(float t, float dt)
	{
		for (auto&& it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->onPostUpdate(t, dt);
		}
	}


	void ObjectManager::destroy()
	{
		for (auto&& it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->onDestroy();
		}
	}


	const GameObject_sptr& ObjectManager::getGameObject(const std::string& objName) const
	{
		if (gameObjects.find(objName) != gameObjects.end())
			return gameObjects.at(objName);
		else
		{
			std::cout << "GameObject not found.\n";
			return nullptr;
		}
	}


	ObjectManager::~ObjectManager()
	{
		gameObjects.clear();
	}
}

