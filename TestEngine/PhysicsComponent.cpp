#include "PhysicsComponent.h"

namespace Engine
{
	PhysicsComponent::PhysicsComponent() : Component(0)
	{
	}

	Ogre::Vector3 PhysicsComponent::getPhysicalPosition() const
	{
		btTransform transform;
		motionState->getWorldTransform(transform);
		return Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z());
	}

	Ogre::Quaternion PhysicsComponent::getPhysicalOrientation() const
	{
		btTransform transform;
		motionState->getWorldTransform(transform);
		return Ogre::Quaternion(transform.getRotation().w(),
			transform.getRotation().x(),
			transform.getRotation().y(),
			transform.getRotation().z());
	}

	PhysicsComponent::~PhysicsComponent()
	{
	}
}

