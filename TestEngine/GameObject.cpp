#include "stdafx.h"
#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject(const std::string& id)
		: name(id),
		destroyed(false),
		parent(nullptr)
	{
		TransformComponent* transform = new TransformComponent(id);
		addComponent(transform);
	}


	void GameObject::addComponent(Component* comp)
	{
		// TODO: unicitást ellenorizni kellene!
		if (comp)
		{
			components.push_back(std::shared_ptr<Component>(comp));
			comp->onInit(this);
		}
	}


	void GameObject::removeComponent(const std::string& compName)
	{
		for (auto&& it = components.begin(); it != components.end(); it++)
		{
			if ((*it)->getName() == compName)
			{
				components.erase(it);
				break;
			}
		}
	}


	void GameObject::removeComponent(Component* comp)
	{
		for (auto&& it = components.begin(); it != components.end(); it++)
		{
			if ((*it).get() == comp)
				it = components.erase(it);
		}
	}

	
	void GameObject::removeComponent()
	{
		components.clear();
	}


	void GameObject::addTag(const std::string& tag)
	{
		tags.insert(tag);
	}


	void GameObject::removeTag(const std::string& tag)
	{
		tags.erase(tag);
	}


	void GameObject::removeTag()
	{
		tags.clear();
	}


	void GameObject::onStart()
	{
		for (auto&& it = components.begin(); it != components.end(); ++it)
			(*it)->onStart();
	}


	void GameObject::onPreUpdate(float t, float dt)
	{
		for (auto&& it = components.begin(); it != components.end(); ++it)
			(*it)->onPreUpdate(t, dt);
	}


	void GameObject::onUpdate(float t, float dt)
	{
		for (auto&& it = components.begin(); it != components.end(); ++it)
			(*it)->onUpdate(t, dt);
	}


	void GameObject::onPostUpdate(float t, float dt)
	{
		for (auto&& it = components.begin(); it != components.end(); ++it)
			(*it)->onPostUpdate(t, dt);
	}


	void GameObject::onDestroy()
	{
		for (auto&& it = components.begin(); it != components.end(); ++it)
		{
			(*it)->onDestroy();
		}
		destroyed = true;
	}


	Component* GameObject::getComponent(const std::string& cID) const
	{
		for (auto&& it = components.cbegin(); it != components.cend(); ++it)
			if ((*it)->getName() == cID)
				return (*it).get();
		return nullptr;
	}


	bool GameObject::hasTag(const std::string& t)
	{
		for (auto&& it = tags.cbegin(); it != tags.cend(); ++it)
		{
			if (*it == t)
				return true;
		}
		return false;
	}


	GameObject::~GameObject()
	{
		removeComponent();
		removeTag();
	}


}
