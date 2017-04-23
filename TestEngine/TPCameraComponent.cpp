#include "TPCameraComponent.h"
#include "GameObject.h"
#include "PhysicsSystem.h"

namespace Engine
{
	TPCameraComponent::TPCameraComponent(const std::string& name, int zDepth)
		: CameraComponent(name, zDepth),
		targetHeight(10.0f),
		camDist(400.0f),
		motBlend(2.0f),
		fixed(false),
		physicsSys(Game::getInstance().getPhysicsSystem())
	{
	}


	TPCameraComponent::~TPCameraComponent()
	{}


	void TPCameraComponent::onInit(GameObject* object)
	{
		CameraComponent::onInit(object);
		auto& dir = ownerObject->transform()->forward();
		dir.normalise();
		const auto& ownerPos = ownerObject->transform()->position();

		camera->setPosition(ownerPos - dir*camDist + Ogre::Vector3(0, height, 0));
		camera->lookAt(ownerPos + Ogre::Vector3(0, targetHeight, 0));
	}


	void TPCameraComponent::onPostUpdate(float t, float dt)
	{
		const auto& ownerPos = ownerObject->transform()->position() + Ogre::Vector3(0, targetHeight, 0);
		auto& dir = ownerObject->transform()->forward();
		dir.normalise();
		auto newPos = ownerPos - dir*camDist + Ogre::Vector3(0, height, 0);

		btVector3 btCamPos(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
		btVector3 btOwnerPos(ownerPos.x, ownerPos.y, ownerPos.z);
		auto ray = physicsSys->rayTest(btCamPos, btOwnerPos);

		if (ray.hasHit())
		{
			btVector3 hitPoint = ray.m_hitPointWorld;
			btVector3 hitNormal = ray.m_hitNormalWorld;
			if (hitPoint.z() > btOwnerPos.z())
				camDist -= motBlend * 0.1f;
		}
		else if (camDist < 40.0f)
			camDist += motBlend * 0.1f;

		float w = motBlend * dt;

		if (!fixed)
			camera->setPosition(w * newPos + (1.0f - w) * camera->getPosition());
		camera->lookAt(ownerPos/* + Ogre::Vector3(0, targetHeight, 0)*/);
	}
}