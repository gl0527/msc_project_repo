#include "CameraComponent.h"

namespace Engine
{
	CameraComponent::CameraComponent(const char* name, float zDepth)
		: camera(nullptr), viewport(nullptr), renderTexture(nullptr)
	{
		camera = Game::getInstance().getRenderSystem()->getSceneManager()->createCamera(name);
		createNode();
		node->attachObject(camera);

		viewport = Game::getInstance().getRenderSystem()->getRenderWindow()->addViewport(camera, zOrder);
	}


	const Ogre::Ray& CameraComponent::getRay(float screenX, float screenY)
	{
		return camera->getCameraToViewportRay(screenX, screenY);
	}


	CameraComponent::~CameraComponent()
	{
	}


}

