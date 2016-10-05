#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject() : tag(0), isDestroyed(false)
	{
	}

	void GameObject::onStart()
	{
		for (auto c : components)
			c->onStart(this);
	}

	void GameObject::onPreUpdate(float t, float dt)
	{
		for (auto c : components)
			c->onPreUpdate(t, dt);
	}

	void GameObject::onPostUpdate(float t, float dt)
	{
		for (auto c : components)
			c->onPostUpdate(t, dt);
	}

	void GameObject::onDestroy()
	{
		for (auto c : components)
			c->onDestroy();
	}

	Component* GameObject::getComponent(unsigned int cID)
	{
		for (auto c : components)
			if (c->getID() == cID)
				return c;
		return nullptr;
	}

	GameObject::~GameObject()
	{
	}
}
