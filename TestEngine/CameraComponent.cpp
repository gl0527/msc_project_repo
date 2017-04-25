#include "CameraComponent.h"
#include "GameObject.h"

namespace Engine
{
	CameraComponent::CameraComponent(const std::string& name, int zDepth)
		: RenderComponent(name),
		zOrder(zDepth),
		camera(nullptr),
		viewport(nullptr),
		renderWnd(Game::getInstance().getRenderSystem()->getRenderWindow()),
		renderTexture(nullptr)
	{
		
	}


	void CameraComponent::onInit(GameObject* obj)
	{
		ownerObject = obj;
		camera = sceneMgr->createCamera(obj->getName() + Ogre::StringConverter::toString(zOrder));

		while (renderWnd->hasViewportWithZOrder(zOrder))
			++zOrder;

		viewport = renderWnd->addViewport(camera, zOrder);
		camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
		object = camera;

		createNode();
		currentNode->attachObject(object);
	}


	void CameraComponent::onDestroy()
	{
		if (renderWnd)
			renderWnd->removeViewport(zOrder);
		if (sceneMgr)
		{
			sceneMgr->destroyCamera(camera->getName());
			sceneMgr->destroySceneNode(currentNode);
		}
		currentNode = nullptr;
		//sceneMgr->destroyEntity(camera->getName());
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

