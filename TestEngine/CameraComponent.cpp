#include "CameraComponent.h"
#include "GameObject.h"

namespace Engine
{
	CameraComponent::CameraComponent(const std::string& name, int zDepth)
		: RenderComponent(name),
		zOrder(zDepth),
		camera(nullptr),
		viewport(nullptr),
		renderWnd(nullptr),
		renderTexture(nullptr)
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


	Ogre::Ray CameraComponent::getRay(float screenX, float screenY) const
	{
		return camera->getCameraToViewportRay(screenX, screenY);
	}


	void CameraComponent::setRenderTexture(Ogre::RenderTexture* rt)
	{
		renderTexture = rt;
		viewport = renderTexture->addViewport(camera, zOrder + 1);
		//renderWnd->removeViewport(zOrder);
		
	}


	CameraComponent::~CameraComponent()
	{
	}


}

