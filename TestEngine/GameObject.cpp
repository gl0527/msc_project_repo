#include "stdafx.h"
#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject() : tag(0), isDestroyed(false)
	{
	}

	void GameObject::onStart()
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			(*it)->onStart(this);
	}

	void GameObject::onPreUpdate(float t, float dt)
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			(*it)->onPreUpdate(t, dt);
	}

	void GameObject::onPostUpdate(float t, float dt)
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			(*it)->onPostUpdate(t, dt);
	}

	void GameObject::onDestroy()
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			(*it)->onDestroy();
	}

	Component* GameObject::getComponent(unsigned int cID)
	{
		for (auto it = components.begin(); it != components.end(); ++it)
			if ((*it)->getID() == cID)
				return *it;
		return nullptr;
	}

	GameObject::~GameObject()
	{
	}
}
