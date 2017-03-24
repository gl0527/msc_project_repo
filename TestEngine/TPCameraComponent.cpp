#include "TPCameraComponent.h"
#include "GameObject.h"

namespace Engine
{
	TPCameraComponent::TPCameraComponent(const std::string& name, int zDepth)
		: CameraComponent(name, zDepth),
		targetHeight(80.0f),
		camDist(400.0f),
		motBlend(2.0f),
		fixed(false)
	{
	}


	TPCameraComponent::~TPCameraComponent()
	{}


	void TPCameraComponent::onInit(GameObject* object)
	{
		CameraComponent::onInit(object);
		Ogre::Vector3& dir = ownerObject->transform()->forward();
		dir.normalise();
		
		camera->setPosition(ownerObject->transform()->position() - dir*camDist + Ogre::Vector3(0, height, 0));
		camera->lookAt(ownerObject->transform()->position() + Ogre::Vector3(0, targetHeight, 0));
	}


	void TPCameraComponent::onPostUpdate(float t, float dt)
	{
		Ogre::Vector3& dir = ownerObject->transform()->forward();
		dir.normalise();
		Ogre::Vector3 newPos = ownerObject->transform()->position() - dir*camDist + Ogre::Vector3(0, height, 0);
		float w = motBlend * dt;

		if (!fixed)
			camera->setPosition(w * newPos + (1.0f - w) * camera->getPosition());
		camera->lookAt(ownerObject->transform()->position() + Ogre::Vector3(0, targetHeight, 0));
	}
}