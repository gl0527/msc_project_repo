#include "RenderComponent.h"
#include "GameObject.h"

namespace Engine
{
	RenderComponent::RenderComponent() : Component(0), node(nullptr), entity(nullptr)
	{
	}


	void RenderComponent::onPostUpdate(float t, float dt)
	{
		node->setPosition(ownerObject->getPosition());
		node->setOrientation(ownerObject->getOrientation());
	}


	void RenderComponent::createNode(Ogre::SceneNode* parentNode)
	{
		if (parentNode)
			node = parentNode->createChildSceneNode();
		else
			node = Game::getInstance().getRenderSystem()->getRootNode()->createChildSceneNode();
		if (entity)
			node->attachObject(entity);
	}


	void RenderComponent::createEntity(const Ogre::String& entityName, const Ogre::String& meshName)
	{
		entity = Game::getInstance().getRenderSystem()->getSceneManager()->createEntity(entityName, meshName);
		if (node)
			node->attachObject(entity);
	}


	void RenderComponent::onDestroy()
	{
		Game::getInstance().getRenderSystem()->getSceneManager()->destroySceneNode(node);
	}


	RenderComponent::~RenderComponent()
	{
	}


}

