#include "PhysicsComponent.h"

namespace Engine
{
	PhysicsComponent::PhysicsComponent() : Component(0)
	{
	}

	Ogre::Vector3 PhysicsComponent::getPhysicalPosition() const
	{
		return Ogre::Vector3(0, 0, 0);
	}

	Ogre::Quaternion PhysicsComponent::getPhysicalOrientation() const
	{
		return Ogre::Quaternion(0, 0, 0, 0);
	}

	PhysicsComponent::~PhysicsComponent()
	{
	}
}

