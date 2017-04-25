#include "TPCameraComponent.h"
#include "GameObject.h"
#include "PhysicsSystem.h"

namespace Engine
{
	TPCameraComponent::TPCameraComponent(const std::string& name, int zDepth)
		: CameraComponent(name, zDepth),
		camHeight(0.0f),
		targetHeight(0.0f),
		camDist(0.0f),
		motBlend(0.0f),
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

		camera->setPosition(ownerPos - dir*camDist + Ogre::Vector3(0, camHeight, 0));
		camera->lookAt(ownerPos + Ogre::Vector3(0, targetHeight, 0));
	}


	void TPCameraComponent::onPostUpdate(float t, float dt)
	{
		const auto& ownerPos = ownerObject->transform()->position() + Ogre::Vector3(0, targetHeight, 0);
		auto& dir = ownerObject->transform()->forward();
		dir.normalise();
		auto newPos = ownerPos - dir*camDist + Ogre::Vector3(0, camHeight, 0);

		//int sgn = camera->getDirection().z < 0.0f ? -1 : 1;

		btVector3 btCamPos(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
		btVector3 btOwnerPos(ownerPos.x, ownerPos.y, ownerPos.z);
		auto& ray = physicsSys->rayTest(btOwnerPos, btCamPos);

		if (ray.hasHit())
		{
			//auto& hitPoint = ray.m_hitPointWorld;
			//auto& hitNormal = ray.m_hitNormalWorld;
			//if (hitPoint.z() > btOwnerPos.z())
			camDist *= 0.8f;
		}
		else if (fabs(camDist) < 40.0f)
		{
			camDist *= 1.2f;
		}

		float w = motBlend * dt;

		if (!fixed)
			camera->setPosition(w * newPos + (1.0f - w) * camera->getPosition());
		camera->lookAt(ownerPos/* + Ogre::Vector3(0, targetHeight, 0)*/);
	}
}