#include "CameraComponent.h"

namespace Engine
{
	CameraComponent::CameraComponent(const char* name, float zDepth)
		: RenderComponent(name), nearCullingPlane(0.1f), farCullingPlane(1000.0f),
		zOrder(zDepth), camera(nullptr), viewport(nullptr), renderTexture(nullptr)
	{
		camera = Game::getInstance().getRenderSystem()->getSceneManager()->createCamera(name);
		viewport = Game::getInstance().getRenderSystem()->getRenderWindow()->addViewport(camera, zOrder);
	}


	void CameraComponent::onStart()
	{
		createNode();
		currentNode->attachObject(camera);
	}


	void CameraComponent::onDestroy()
	{
		Game::getInstance().getRenderSystem()->getRenderWindow()->removeViewport(zOrder);
		Game::getInstance().getRenderSystem()->getSceneManager()->destroyCamera(entityName);
		Game::getInstance().getRenderSystem()->getSceneManager()->destroySceneNode(currentNode);
		currentNode = nullptr;
		Game::getInstance().getRenderSystem()->getSceneManager()->destroyEntity(entityName);
		entity = nullptr;
	}


	const Ogre::Ray& CameraComponent::getRay(float screenX, float screenY)
	{
		return camera->getCameraToViewportRay(screenX, screenY);
	}


	CameraComponent::~CameraComponent()
	{
	}


}

