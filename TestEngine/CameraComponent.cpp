#include "CameraComponent.h"
#include "GameObject.h"

namespace Engine
{
	CameraComponent::CameraComponent(const char* name, float zDepth, const Ogre::ColourValue& clear)
		: RenderComponent(name),
		zOrder(zDepth),
		camera(nullptr),
		viewport(nullptr),
		renderWnd(nullptr),
		renderTexture(nullptr),
		clearColor(clear),
		targetObject(nullptr)
	{
		camera = sceneMgr->createCamera(name);
		object = camera;
		renderWnd = Game::getInstance().getRenderSystem()->getRenderWindow();
		viewport = renderWnd->addViewport(camera, zOrder);
		camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
	}


	void CameraComponent::onDestroy()
	{
		renderWnd->removeViewport(zOrder);
		sceneMgr->destroyCamera(objName);
		sceneMgr->destroySceneNode(currentNode);
		currentNode = nullptr;
		sceneMgr->destroyEntity(objName);
	}


	const Ogre::Ray& CameraComponent::getRay(float screenX, float screenY) const
	{
		return camera->getCameraToViewportRay(screenX, screenY);
	}


	CameraComponent::~CameraComponent()
	{
	}


}

