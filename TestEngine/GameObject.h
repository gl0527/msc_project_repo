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
		std::vector<Component*> components;
		unsigned int tag;
		bool isDestroyed;
	public:
		GameObject();

		void addComponent(Component* component);
		void removeComponent(unsigned int cID);
		void removeComponent();

		void onStart();
		void onPreUpdate(float t, float dt);
		void onUpdate(float t, float dt);
		void onPostUpdate(float t, float dt); 
		void onDestroy();
		//void onCollision(Collider other);

		const Ogre::Vector3& getPosition() const { return position; }
		const Ogre::Quaternion& getOrientation() const { return orientation; }
		const Ogre::Vector3& getScale() const { return scale; }
		Component* getComponent(unsigned int cID);

		void destroy();

		~GameObject();
	};
}


