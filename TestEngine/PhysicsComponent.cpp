#include "PhysicsComponent.h"
#include "GameObject.h"

namespace Engine
{
	PhysicsComponent::PhysicsComponent(float m)
		: Component(0), mass(m), isTrigger(false), rigidBody(nullptr), motionState(nullptr)
	{
		if (mass < 0.0001f)
			type = PhysicsComponent::STATIC;
		else
			type = PhysicsComponent::DYNAMIC;
	}


	void PhysicsComponent::onPreUpdate(float t, float dt)
	{

	}


	void PhysicsComponent::onUpdate(float t, float dt)
	{
		if (type == PhysicsComponent::DYNAMIC)
		{
			ownerObject->setPosition(getPosition());
			ownerObject->setOrientation(getOrientation());
		}
	}


	void PhysicsComponent::onPostUpdate(float t, float dt)
	{
		if (type == PhysicsComponent::KINEMATIC)
		{
			setPosition(ownerObject->getPosition());
			setOrientation(ownerObject->getOrientation());
		}
	}


	Ogre::Vector3 PhysicsComponent::getPosition() const
	{
		btTransform transform;
		motionState->getWorldTransform(transform);
		return Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z());
	}


	Ogre::Quaternion PhysicsComponent::getOrientation() const
	{
		btTransform transform;
		motionState->getWorldTransform(transform);
		return Ogre::Quaternion(transform.getRotation().w(),
			transform.getRotation().x(),
			transform.getRotation().y(),
			transform.getRotation().z());
	}


	void PhysicsComponent::setPosition(const Ogre::Vector3& p)
	{
		btTransform prevTransform;
		motionState->getWorldTransform(prevTransform);
		btTransform newTransform(prevTransform.getRotation(), btVector3(p.x, p.y, p.z));
		motionState->setWorldTransform(newTransform);
	}


	void PhysicsComponent::setOrientation(const Ogre::Quaternion& q)
	{
		btTransform prevTransform;
		motionState->getWorldTransform(prevTransform);
		btTransform newTransform(btQuaternion(q.x, q.y, q.z, q.w), prevTransform.getOrigin());
		motionState->setWorldTransform(newTransform);
	}


	void PhysicsComponent::addForce(float fx, float fy, float fz)
	{
		if (type == PhysicsComponent::DYNAMIC && rigidBody)
		{
			btVector3 centralForce(fx, fy, fz);
			rigidBody->applyCentralForce(centralForce);
		}
	}


	void PhysicsComponent::setFriction(float friction)
	{
		if (rigidBody)
		{
			rigidBody->setFriction(friction);
		}
	}


	void PhysicsComponent::setDamping(float linear, float angular)
	{
		if (rigidBody)
		{
			rigidBody->setDamping(linear, angular);
		}
	}


	void PhysicsComponent::setRestitution(float restitution)
	{
		if (rigidBody)
		{
			rigidBody->setRestitution(restitution);
		}
	}


	void PhysicsComponent::setAngularFactor(float x, float y, float z)
	{
		if (type == PhysicsComponent::DYNAMIC && rigidBody)
		{
			rigidBody->setAngularFactor(btVector3(x,y,z));
		}
	}


	PhysicsComponent::~PhysicsComponent()
	{
	}


}

