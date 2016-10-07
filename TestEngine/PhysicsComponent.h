#pragma once
#include "Component.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
	protected:
		float mass;
		bool isTrigger;
		/*btRigidBody* physicsBody;
		btCollisionShape* physicsShape; // ebbol tobb is lehet, s akkor compoundshape-eket is letre tudunk hozni
		btMotionState* physicsMotionState;*/
	public:
		PhysicsComponent();

		Ogre::Vector3 getPhysicalPosition() const;
		Ogre::Quaternion getPhysicalOrientation() const;

		~PhysicsComponent();
	};

}

