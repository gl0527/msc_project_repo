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

		void onStart();
		void onPreUpdate(float t, float dt);
		void onUpdate(float t, float dt);
		void onPostUpdate(float t, float dt);
		void onDestroy();

		const std::string& getName() const { return name; }
		TransformComponent* transform() const { return (TransformComponent*)components[0].get(); }
		const Component_sptr& getComponent(const std::string& cID) const;
		const GameObject_sptr& getParent() const { return parent; }
		
		template<typename T>
		T* getFirstComponentByType()
		{
			for (auto it = components.begin(); it != components.end(); ++it)
			{
				if (T* castedComponent = dynamic_cast<T*>((*it).get()))
					return castedComponent;
			}
			return nullptr;
		}
		
		template<typename T>
		std::vector<T*> getComponentsByType()
		{
			std::vector<T*> returnVector;

			for (auto it = components.begin(); it != components.end(); ++it)
			{
				if (T* castedComponent = dynamic_cast<T*>(*it))
					returnVector.push_back(*it);
			}
			return returnVector;
		}

		void clearParent() { parent = nullptr; }
		bool hasParent() const { return parent != nullptr; }
		void setParent(const GameObject_sptr& p) { parent = p; }
		bool hasTag(const std::string& t);
		bool isDestroyed() const { return destroyed; }
	};


}


