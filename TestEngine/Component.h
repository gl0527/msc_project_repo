#pragma once
#include "Ogre.h"
#include "Game.h"
#include "stdafx.h"

namespace Engine
{
	class GameObject;

	class DLL_SPEC Component
	{
	protected:
		const unsigned int ID;
		const bool unique;
		GameObject* ownerObject;
	public:
		Component(unsigned int id, bool uniq = true);

		// runs when this component is added to a gameobject
		virtual void onInit(GameObject* object) { ownerObject = object; }
		// runs just before the updating loop - every gameobject is ready
		virtual void onStart() { }
		// runs on every update cycle - before the physics update
		virtual void onPreUpdate(float t, float dt) { }
		// runs on every update cycle - just before the physics update
		virtual void onUpdate(float t, float dt) { }
		// runs on every update cycle - after the physics update
		virtual void onPostUpdate(float t, float dt) { }
		virtual void onDestroy() { }
		virtual void onCollision(GameObject* other) { }

		unsigned int getID() const { return ID; }
		bool isUnique() const { return unique; }
		GameObject* getOwnerObject() const { return ownerObject; }

		~Component();
	};
}

