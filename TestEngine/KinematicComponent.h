#pragma once
#include "PhysicsComponent.h"

namespace Engine
{
	class KinematicComponent : public PhysicsComponent
	{
		void SetPhysicalPosition(const Ogre::Vector3& p);
		void SetPhysicalOrientation(const Ogre::Quaternion& q);
	public:
		KinematicComponent();
		~KinematicComponent();
	};
}


