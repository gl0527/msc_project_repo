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


	void ObjectManager::addComponentFactory(const std::string& compType, IComponentFactory* compFact)
	{
		if (compFact)
			componentFactories[compType] = compFact;
	}


	GameObject* ObjectManager::createGameObject(unsigned int id)
	{
		auto it = gameObjects.find(id);	
		if (it == gameObjects.end())
		{
			gameObjects[id] = new GameObject(id);
			return gameObjects[id];
		}
		return nullptr;
	}


	void ObjectManager::removeGameObject(unsigned int id)
	{

	}


	Component* ObjectManager::createComponent(const std::string& compType)
	{
		/*if (componentFactories.find(compType) == componentFactories.end())
			return nullptr;
		else
		{
			return componentFactories[compType]->create();
		}*/
		return nullptr;
	}


	void ObjectManager::start()
	{
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->onStart();
		}
	}


	void ObjectManager::preUpdate(float t, float dt)
	{
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->onPreUpdate(t, dt);
		}
	}


	void ObjectManager::update(float t, float dt)
	{
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->onUpdate(t, dt);
		}
	}


	void ObjectManager::postUpdate(float t, float dt)
	{
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->onPostUpdate(t, dt);
		}
	}


	ObjectManager::~ObjectManager()
	{
	}
}

