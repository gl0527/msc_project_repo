#include "CameraComponent.h"

namespace Engine
{
	CameraComponent::CameraComponent(const char* name, float zDepth)
	{
	}

	const Ogre::Ray& CameraComponent::getRay(float screenX, float screenY)
	{
		return camera->getCameraToViewportRay(screenX, screenY);
	}

	CameraComponent::~CameraComponent()
	{
	}
}

