#pragma once
#include "Ogre.h"

namespace Engine
{
	class GameObject;

	class Component
	{
	protected:
		unsigned int id;
		bool unique;
		GameObject* ownerObject;
	public:
		Component(unsigned int ident, bool uniq = true);

		virtual void onStart(GameObject* owner) { ownerObject = owner; }
		virtual void onPreUpdate(float t, float dt) { }
		virtual void onUpdate(float t, float dt) { }
		virtual void onPostUpdate(float t, float dt) { }
		virtual void onDestroy() { }
		//virtual void onCollision(Collider other) { }

		unsigned int getID() const { return id; }
		GameObject* getOwnerObject() const { return ownerObject; }

		~Component();
	};
}

