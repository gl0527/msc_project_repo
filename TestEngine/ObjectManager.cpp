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


	GameObject_wptr ObjectManager::createGameObject(const std::string& id)
	{
		if (gameObjects.find(id) == gameObjects.end())
		{
			gameObjects[id] = std::shared_ptr<GameObject>(new GameObject(id));
			return gameObjects[id];
		}
		else
		{
			std::cout << "Gameobject creation failed: Gameobject with name \"" << id << "\" already existing.\n";
			return std::shared_ptr<GameObject>(nullptr);
		}
	}


	void ObjectManager::removeGameObject(const std::string& id)
	{
		auto& removableObject = gameObjects[id];
		if (removableObject)
		{
			const auto& removableChildren = removableObject->getChildrenNames();
			for (auto it = removableChildren.begin(); it != removableChildren.end(); ++it)
			{
				removeGameObject(*it);
			}
			removableObject->onDestroy();
			gameObjects.erase(gameObjects.find(id));
		}
	}


	void ObjectManager::start()
	{
		for (auto it = gameObjects.begin(), end = gameObjects.end(); it != end; ++it)
		{
			it->second->onStart();
		}
	}


	void ObjectManager::preUpdate(float t, float dt)
	{
		for (auto it = gameObjects.begin(), end = gameObjects.end(); it != end; ++it)
		{
			it->second->onPreUpdate(t, dt);
		}
	}


	void ObjectManager::update(float t, float dt)
	{
		for (auto it = gameObjects.begin(), end = gameObjects.end(); it != end; ++it)
		{
			it->second->onUpdate(t, dt);
		}
	}


	void ObjectManager::postUpdate(float t, float dt)
	{
		for (auto it = gameObjects.begin(), end = gameObjects.end(); it != end; ++it)
		{
			it->second->onPostUpdate(t, dt);
		}
	}


	void ObjectManager::destroy()
	{
		for (auto it = gameObjects.begin(), end = gameObjects.end(); it != end; ++it)
		{
			it->second->onDestroy();
		}
	}


	GameObject_wptr ObjectManager::getGameObject(const std::string& objName) const
	{
		if (gameObjects.find(objName) != gameObjects.end())
			return gameObjects.at(objName);
		else
		{
			std::cout << "Gameobject with name \"" << objName << "\" not found.\n";
			return std::shared_ptr<GameObject>(nullptr);
		}
	}


	ObjectManager::~ObjectManager()
	{
		gameObjects.clear();
	}
}

