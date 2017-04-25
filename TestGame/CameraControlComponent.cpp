#include "CameraControlComponent.h"
#include "GameObject.h"

CameraControlComponent::CameraControlComponent(const std::string& name)
	: Component(name),
	camHeight(0.0f),
	targetHeight(0.0f),
	camDist(0.0f),
	motBlend(0.0f),
	fixed(false),
	world(Game::getInstance().getPhysicsSystem()),
	ownerCam(std::shared_ptr<CameraComponent>(nullptr))
{
}


CameraControlComponent::~CameraControlComponent()
{
}


void CameraControlComponent::onStart()
{
	ownerCam = ownerObject->getFirstComponentByType<CameraComponent>();
	if (ownerCam.lock() == nullptr)
		ownerObject->removeComponent(name);
}


void CameraControlComponent::onPostUpdate(float t, float dt)
{
	if (auto& ownerCamera = ownerCam.lock())
	{

	}
}
