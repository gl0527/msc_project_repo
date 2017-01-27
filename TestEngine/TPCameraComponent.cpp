#include "TPCameraComponent.h"
#include "GameObject.h"

namespace Engine
{
	TPCameraComponent::TPCameraComponent(const std::string& name, int zDepth, bool fix)
		: CameraComponent(name, zDepth),
		camHeight(200.0f),
		targetHeight(80.0f),
		camDist(400.0f),
		motBlend(3.0f),
		fixed(fix)
	{}


	TPCameraComponent::~TPCameraComponent()
	{}


	void TPCameraComponent::onInit(GameObject* object)
	{
		ownerObject = object;
		Ogre::Vector3& dir = ownerObject->getTransform()->getForward();
		dir.normalise();
		
		camera->setPosition(ownerObject->getTransform()->getPosition() - dir*camDist + Ogre::Vector3(0, camHeight, 0));
		camera->lookAt(ownerObject->getTransform()->getPosition() + Ogre::Vector3(0, targetHeight, 0));
	}


	void TPCameraComponent::onPostUpdate(float t, float dt)
	{
		Ogre::Vector3& dir = ownerObject->getTransform()->getForward();
		dir.normalise();
		Ogre::Vector3 newPos = ownerObject->getTransform()->getPosition() - dir*camDist + Ogre::Vector3(0, camHeight, 0);
		
		if (!fixed)
			camera->setPosition(motBlend * dt * newPos + (1.0f - motBlend * dt) * camera->getPosition());
		camera->lookAt(ownerObject->getTransform()->getPosition() + Ogre::Vector3(0, targetHeight, 0));
	}
}