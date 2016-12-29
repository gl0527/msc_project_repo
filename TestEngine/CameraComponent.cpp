#include "CameraComponent.h"
#include "GameObject.h"

namespace Engine
{
	CameraComponent::CameraComponent(const char* name, float zDepth, const Ogre::ColourValue& clear)
		: RenderComponent(name),
		nearCullingPlane(0.1f),
		farCullingPlane(1000.0f),
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


	/*void CameraComponent::onStart()
	{
		createNode();
		currentNode->attachObject(camera);
	}*/


	void CameraComponent::onPostUpdate(float t, float dt)
	{
		if (targetObject)
		{
			const Ogre::Vector3& dir = targetObject->getDirection();
			
			currentNode->setPosition(targetObject->getPosition() + Ogre::Vector3(0,300,0) - dir*500);
			camera->lookAt(targetObject->getPosition());
			//currentNode->setOrientation(targetObject->getOrientation());
			//currentNode->setScale(ownerObject->getScale());
		}
		else
		{
			currentNode->setPosition(ownerObject->getPosition());
			currentNode->setOrientation(ownerObject->getOrientation());
			currentNode->setScale(ownerObject->getScale());
		}
	}


	void CameraComponent::onDestroy()
	{
		renderWnd->removeViewport(zOrder);
		//Game::getInstance().getRenderSystem()->getSceneManager()->destroyCamera(entityName);
		sceneMgr->destroySceneNode(currentNode);
		currentNode = nullptr;
		//sceneMgr->destroyEntity(entityName);
	}


	const Ogre::Ray& CameraComponent::getRay(float screenX, float screenY)
	{
		return camera->getCameraToViewportRay(screenX, screenY);
	}


	CameraComponent::~CameraComponent()
	{
	}


}

