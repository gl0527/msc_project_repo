#include "stdafx.h"
#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject(unsigned int id)
		: position(Ogre::Vector3::ZERO), orientation(Ogre::Quaternion::IDENTITY), scale(Ogre::Vector3(1.0f, 1.0f, 1.0f)),
		parent(nullptr), ID(id), isDestroyed(false)
	{
	}


	void GameObject::addComponent(Component* comp)
	{
		if (comp)
		{
			components.push_back(comp);
			comp->setGameObject(this);
		}
	}

	
	void GameObject::removeComponent()
	{
		
	}


	void GameObject::addChild(GameObject* child)
	{
		if (child)
		{
			child->parent = this;
			children.push_back(child);
		}
	}


	void GameObject::removeChild(unsigned int childID)
	{
		std::vector<GameObject*>::iterator it;

		for (it = children.begin(); it != children.end() && (*it)->getID() != childID; ++it);
		
		if (it != children.end())
			children.erase(it);
	}


	void GameObject::onStart()
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			(*it)->onStart();
	}


	void GameObject::onPreUpdate(float t, float dt)
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			(*it)->onPreUpdate(t, dt);
	}


	void GameObject::onUpdate(float t, float dt)
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			(*it)->onUpdate(t, dt);
	}


	void GameObject::onPostUpdate(float t, float dt)
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			(*it)->onPostUpdate(t, dt);
	}


	void GameObject::onCollision(GameObject* other)
	{

	}


	void GameObject::onDestroy()
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			(*it)->onDestroy();
	}


	Component* GameObject::getComponent(unsigned int cID) const
	{
		for (auto it = components.cbegin(); it != components.cend(); ++it)
			if ((*it)->getID() == cID)
				return (*it);
		return nullptr;
	}


	GameObject* GameObject::getChild(unsigned int childID) const
	{
		for (auto it = children.cbegin(); it != children.cend(); ++it)
			if ((*it)->getID() == childID)
				return *it;
		return nullptr;
	}


	GameObject::~GameObject()
	{
	}


}
