#pragma once
#include "stdafx.h"
#include <memory>
#include "TransformComponent.h"

namespace Engine
{
	class DLL_SPEC GameObject
	{
		const std::string name;
		bool destroyed;
		GameObject_sptr parent;
		std::vector<GameObject_wptr> children;
		std::vector<Component_sptr> components;
		std::unordered_set<std::string> tags;
	public:
		GameObject(const std::string& id);
		~GameObject();

		void addComponent(const Component_sptr& comp);
		void removeComponent(const std::string& compName);
		void removeComponent(const Component_sptr& comp);
		void removeComponent();

		void addTag(const std::string& tag);
		void removeTag(const std::string& tag);
		void removeTag();

		void addChild(const std::string& childName);
		void removeChild(const std::string& childName);
		void removeChildren();

		void onStart();
		void onPreUpdate(float t, float dt);
		void onUpdate(float t, float dt);
		void onPostUpdate(float t, float dt);
		void onDestroy();

		const std::string& getName() const { return name; }
		TransformComponent* transform() const { return (TransformComponent*)components[0].get(); }
		Component_wptr getComponent(const std::string& cID) const;
		GameObject_wptr getParent() const { return parent; }
		std::vector<std::string> getChildrenNames() const;
		
		template<typename T>
		std::weak_ptr<T> getFirstComponentByType()
		{
			for (auto it = components.begin(); it != components.end(); ++it)
			{
				if (auto casted = std::dynamic_pointer_cast<T>(*it))
					return casted;
			}
			return std::shared_ptr<T>(nullptr);
		}

		void clearParent() { parent.reset(); }
		bool hasParent() const { return parent != nullptr; }
		void setParent(const std::string& parentName);
		bool hasTag(const std::string& t);
		bool isDestroyed() const { return destroyed; }
	};


}


