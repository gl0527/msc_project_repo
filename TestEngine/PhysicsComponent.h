#pragma once
#include "Component.h"
#include "btBulletDynamicsCommon.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
	protected:
		float mass;
		bool isTrigger;
		btRigidBody* rigidBody;
		std::vector<btCollisionShape*> shapes;
		btMotionState* motionState;
	public:
		PhysicsComponent();

		Ogre::Vector3 getPhysicalPosition() const;
		Ogre::Quaternion getPhysicalOrientation() const;

		~PhysicsComponent();
	};

}

