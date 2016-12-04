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
		bool enabled;
		GameObject* ownerObject;
	public:
		class InitStruct{};
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

		unsigned int getID() const { return ID; }
		bool isUnique() const { return unique; }
		bool isEnabled() const { return enabled; }
		void enable() { enabled = true; }
		void disable() { enabled = false; }
		GameObject* getOwnerObject() const { return ownerObject; }

		virtual ~Component();
	};
}

