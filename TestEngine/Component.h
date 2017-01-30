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
		const std::string name;
		const bool unique;
		bool enabled;
		GameObject* ownerObject;
	public:
		Component(const std::string& ident, bool uniq = false);

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

		const std::string& getName() const { return name; }
		bool isUnique() const { return unique; }
		bool isEnabled() const { return enabled; }
		void enable() { enabled = true; }
		void disable() { enabled = false; }
		GameObject* getOwnerObject() const { return ownerObject; }

		virtual ~Component();
	};
}

