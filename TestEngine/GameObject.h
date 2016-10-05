#pragma once
#include <vector>
#include "Component.h"

namespace Engine
{
	class GameObject
	{
		unsigned int tag;
		bool isDestroyed;
		std::vector<Component*> components;
		// position
		// orientation
		// scale
	public:
		GameObject();

		void addComponent(Component* component);
		void removeComponent(unsigned int cID);
		void removeComponent();

		void onStart();
		void onPreUpdate(float t, float dt);
		void onPostUpdate(float t, float dt);
		void onDestroy();
		//void onCollision(Collider other);

		Component* getComponent(unsigned int cID);

		void destroy();

		~GameObject();
	};
}


