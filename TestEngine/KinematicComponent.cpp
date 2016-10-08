#include "KinematicComponent.h"
#include "GameObject.h"

namespace Engine
{
	KinematicComponent::KinematicComponent()
	{
	}

	void KinematicComponent::setPhysicalPosition(const Ogre::Vector3& p)
	{
		btTransform prevTransform;
		motionState->getWorldTransform(prevTransform);
		btTransform newTransform(prevTransform.getRotation(), btVector3(p.x, p.y, p.z));
		motionState->setWorldTransform(newTransform);
	}

	void KinematicComponent::setPhysicalOrientation(const Ogre::Quaternion& q)
	{
		btTransform prevTransform;
		motionState->getWorldTransform(prevTransform);
		btTransform newTransform(btQuaternion(q.x, q.y, q.z, q.w), prevTransform.getOrigin());
		motionState->setWorldTransform(newTransform);
	}

	void KinematicComponent::onPostUpdate(float t, float dt)
	{
		setPhysicalPosition(ownerObject->getPosition());
		setPhysicalOrientation(ownerObject->getOrientation());
	}

	KinematicComponent::~KinematicComponent()
	{
	}
}

