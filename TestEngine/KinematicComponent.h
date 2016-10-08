#pragma once
#include "PhysicsComponent.h"

namespace Engine
{
	class KinematicComponent : public PhysicsComponent
	{
		void setPhysicalPosition(const Ogre::Vector3& p);
		void setPhysicalOrientation(const Ogre::Quaternion& q);
	public:
		KinematicComponent();

		virtual void onPostUpdate(float t, float dt) override;

		~KinematicComponent();
	};
}


