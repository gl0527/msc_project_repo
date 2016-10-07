#pragma once
#include "PhysicsComponent.h"

namespace Engine
{
	class DynamicComponent : public PhysicsComponent
	{
		bool disableRotation;
	public:
		DynamicComponent();

		void addForce(const Ogre::Vector3 f);
		void setFriction(float friction);
		void setDamping(float linear, float angular);
		void setRestitution(float restitution);
		void setAngularFactor(float x, float y, float z);

		~DynamicComponent();
	};
}


