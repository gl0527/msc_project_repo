#include "stdafx.h"
#include "GameObject.h"
#include "ObjectManager.h"

namespace Engine
{
	GameObject::GameObject(const std::string& id)
		: name(id),
		destroyed(false),
		parent(std::shared_ptr<GameObject>(nullptr))
	{
		std::shared_ptr<TransformComponent> transform(new TransformComponent(id));
		addComponent(transform);
	}


	void GameObject::addComponent(const Component_sptr& comp)
	{
		// TODO: unicitást ellenorizni kellene!
		if (comp)
		{
			components.push_back(comp);
			comp->onInit(this);
		}
	}


	void GameObject::removeComponent(const std::string& compName)
	{
		for (auto it = components.begin(); it != components.end(); it++)
		{
			if ((*it)->getName() == compName)
			{
				components.erase(it);
				break;
			}
		}
	}


	void GameObject::removeComponent(const Component_sptr& comp)
	{
		components.erase(std::remove(components.begin(), components.end(), comp), components.end());
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


	void GameObject::addChild(const std::string & childName)
	{
		const auto& child = ObjectManager::getInstance().getGameObject(childName);
		if(child)
			children.push_back(child);
	}


	void GameObject::removeChild(const std::string & childName)
	{
		for (auto child = children.begin(); child != children.end(); ++child)
		{
			if ((*child).lock()->getName() == childName)
			{
				child = children.erase(child);
				break;
			}
		}
	}


	void GameObject::removeChildren()
	{
		children.clear();
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


	void GameObject::onDestroy()
	{
		clearParent();
		for (auto it = components.begin(); it != components.end(); ++it)
		{
			(*it)->onDestroy();
		}
		destroyed = true;
	}


	const Component_sptr& GameObject::getComponent(const std::string& cID) const
	{
		for (auto it = components.cbegin(); it != components.cend(); ++it)
			if ((*it)->getName() == cID)
				return *it;
		return nullptr;
	}


	std::vector<std::string> GameObject::getChildrenNames() const
	{
		std::vector<std::string> childrenNames;
		for (auto child = children.begin(); child != children.end(); ++child)
		{
			childrenNames.push_back(child->lock()->getName());
		}
		return childrenNames;
	}


	void GameObject::setParent(const std::string& parentName)
	{
		const auto& parentObj = ObjectManager::getInstance().getGameObject(parentName);
		parent = parentObj;
		parentObj->addChild(name);
	}


	bool GameObject::hasTag(const std::string& t)
	{
		for (auto it = tags.cbegin(); it != tags.cend(); ++it)
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
		removeChildren();
	}


}
