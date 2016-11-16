#include "RenderComponent.h"
#include "GameObject.h"

namespace Engine
{
	RenderComponent::RenderComponent(const char* eName, const char* mName)
		: Component(1), currentNode(nullptr), entity(nullptr), entityName(eName), meshName(mName)
	{
		createEntity();
	}


	void RenderComponent::onStart()
	{
		createNode();
	}


	void RenderComponent::onPostUpdate(float t, float dt)
	{
		if (ownerObject)
		{
			currentNode->setPosition(ownerObject->getPosition());
			currentNode->setOrientation(ownerObject->getOrientation());
			currentNode->setScale(ownerObject->getScale());
		}
	}


	void RenderComponent::createNode()
	{
		GameObject* ownerParent = ownerObject->getParent();
		if (ownerParent)
		{
			if(Ogre::SceneNode* parentNode = ownerParent->getFirstComponentByType<RenderComponent>()->getNode())
				currentNode = parentNode->createChildSceneNode();
		}
		else
			currentNode = Game::getInstance().getRenderSystem()->getRootNode()->createChildSceneNode();
		if (entity)
			currentNode->attachObject(entity);
	}


	void RenderComponent::createEntity()
	{
		if (meshName != "")
		{
			entity = Game::getInstance().getRenderSystem()->getSceneManager()->createEntity(entityName, meshName);
			if (currentNode)
				currentNode->attachObject(entity);
		}
	}


	void RenderComponent::onDestroy()
	{
		Game::getInstance().getRenderSystem()->getSceneManager()->destroySceneNode(currentNode);
		currentNode = nullptr;
		Game::getInstance().getRenderSystem()->getSceneManager()->destroyEntity(entityName);
		entity = nullptr;
	}


	RenderComponent::~RenderComponent()
	{
	}


}

