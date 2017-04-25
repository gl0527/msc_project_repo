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
		auto predicate = [&compName](const Component_sptr& elem) { return elem->getName() == compName; };
		components.erase(std::remove_if(components.begin(), components.end(), predicate), components.end());
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


	void GameObject::addChild(const std::string& childName)
	{
		if (const auto& child = ObjectManager::getInstance().getGameObject(childName).lock())
		{
			children.push_back(child);
		}
		
		//child->transform()->setPosition(this->transform()->position() + child->transform()->position());
		/*child->transform()->setRotation(this->transform()->rotation() * child->transform()->rotation());
		child->transform()->setScale(this->transform()->position() + child->transform()->position());*/
	}


	void GameObject::removeChild(const std::string& childName)
	{
		auto predicate = [&childName](GameObject_wptr elem) -> bool
		{
			if (auto& child = elem.lock())
			{
				if (child->getName() == childName)
				{
					child->onDestroy();
					return true;
				}
			}
			return false;
		};
		children.erase(std::remove_if(children.begin(), children.end(), predicate), children.end());
	}


	void GameObject::removeChildren()
	{
		children.clear();
	}


	void GameObject::onStart()
	{
		for (auto it = components.begin(), end = components.end(); it != end; ++it)
			(*it)->onStart();
	}


	void GameObject::onPreUpdate(float t, float dt)
	{
		for (auto it = components.begin(), end = components.end(); it != end; ++it)
			(*it)->onPreUpdate(t, dt);
	}


	void GameObject::onUpdate(float t, float dt)
	{
		for (auto it = components.begin(), end = components.end(); it != end; ++it)
			(*it)->onUpdate(t, dt);
	}


	void GameObject::onPostUpdate(float t, float dt)
	{
		for (auto it = components.begin(), end = components.end(); it != end; ++it)
			(*it)->onPostUpdate(t, dt);
	}


	void GameObject::onDestroy()
	{
		clearParent();
		for (auto it = components.begin(), end = components.end(); it != end; ++it)
		{
			(*it)->onDestroy();
		}
		destroyed = true;
	}


	Component_wptr GameObject::getComponent(const std::string& cID) const
	{
		for (auto it = components.cbegin(), end = components.cend(); it != end; ++it)
			if ((*it)->getName() == cID)
				return *it;
		return std::shared_ptr<Component>(nullptr);
	}


	std::vector<std::string> GameObject::getChildrenNames() const
	{
		std::vector<std::string> childrenNames;
		for (auto child = children.begin(), end = children.end(); child != end; ++child)
		{
			childrenNames.push_back(child->lock()->getName());
		}
		return childrenNames;
	}


	void GameObject::setParent(const std::string& parentName)
	{
		if (auto& ancestor = ObjectManager::getInstance().getGameObject(parentName).lock())
		{
			parent = ancestor;
			ancestor->addChild(name);
		}
	}


	bool GameObject::hasTag(const std::string& t)
	{
		for (auto it = tags.cbegin(), end = tags.cend(); it != end; ++it)
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
