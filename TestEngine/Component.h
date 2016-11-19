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

		virtual void onInit(GameObject* object) { ownerObject = object; }
		virtual void onStart() { }
		virtual void onPreUpdate(float t, float dt) { }
		virtual void onUpdate(float t, float dt) { }
		virtual void onPostUpdate(float t, float dt) { }
		virtual void onDestroy() { }
		virtual void onCollision(GameObject* other) { }

		unsigned int getID() const { return ID; }
		bool isUnique() const { return unique; }
		GameObject* getOwnerObject() const { return ownerObject; }

		~Component();
	};
}

