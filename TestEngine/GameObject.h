#pragma once
#include "stdafx.h"
#include <vector>
#include "Component.h"

namespace Engine
{
	class DLL_SPEC GameObject
	{
		Ogre::Vector3 position;
		Ogre::Quaternion orientation;
		Ogre::Vector3 scale;

		GameObject* parent;
		std::vector<GameObject*> children;

		std::vector<Component*> components;
		std::vector<unsigned int> tags;
		const unsigned int ID;
		bool isDestroyed;
	public:
		GameObject(unsigned int id);
		~GameObject();

		void addComponent(Component* comp);
		void removeComponent(unsigned int cID);
		void removeComponent(Component* component);
		void removeComponent();

		void addChild(GameObject* child);
		void removeChild(unsigned int childID);

		void onStart();
		void onPreUpdate(float t, float dt);
		void onUpdate(float t, float dt);
		void onPostUpdate(float t, float dt);
		void onDestroy();

		unsigned int getID() const { return ID; }

		const Ogre::Vector3& getPosition() const { return position; }
		const Ogre::Quaternion& getOrientation() const { return orientation; }
		const Ogre::Vector3& getScale() const { return scale; }
		
		Ogre::Vector3 getDirection() const { return orientation * (-Ogre::Vector3::UNIT_Z); }
		Ogre::Vector3 getUp() const { return orientation * Ogre::Vector3::UNIT_Y; }
		Ogre::Vector3 getRight() const { return orientation * Ogre::Vector3::UNIT_X; }
		
		Component* getComponent(unsigned int cID) const;
		GameObject* getParent() const { return parent; }
		GameObject* getChild(unsigned int childID) const;
		const std::vector<GameObject*>& getChildren() const { return children; }

		template<typename T>
		T* getFirstComponentByType()
		{
			for (auto it = components.begin(); it != components.end(); ++it)
			{
				if (T* castedComponent = dynamic_cast<T*>(*it))
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

		void setPosition(const Ogre::Vector3& pos) { position = pos; }
		void setOrientation(const Ogre::Quaternion& q) { orientation = q; }
		void setScale(const Ogre::Vector3& s) { scale = s; }
		void clearParent() { parent = nullptr; }

		bool hasParent() const { return parent != 0; }
		bool hasTag(unsigned int t);

		bool operator==(const GameObject& other) { return ID == other.getID(); }
	};

	

}


