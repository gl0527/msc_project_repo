#include "RenderComponent.h"
#include "GameObject.h"

namespace Engine
{
	RenderComponent::RenderComponent(const char* eName, const char* mName)
		: Component(1),
		parentNode(nullptr),
		currentNode(nullptr),
		entity(nullptr),
		entityName(eName),
		meshName(mName)
	{
		parentNode = Game::getInstance().getRenderSystem()->getRootNode();
		createEntity();
	}

	RenderComponent::RenderComponent(const InitStruct& init)
		: Component(1),
		parentNode(nullptr),
		currentNode(nullptr),
		entity(nullptr),
		entityName(init.eName),
		meshName(init.mName)
	{
		parentNode = Game::getInstance().getRenderSystem()->getRootNode();
		createEntity();
	}


	void RenderComponent::onStart()
	{
		createNode();
	}


	void RenderComponent::onPostUpdate(float t, float dt)
	{
		currentNode->setPosition(ownerObject->getPosition());
		currentNode->setOrientation(ownerObject->getOrientation());
		currentNode->setScale(ownerObject->getScale());	
	}


	void RenderComponent::createNode()
	{
		GameObject* ownerParent = ownerObject->getParent();
		if (ownerParent)
		{	
			if (Ogre::SceneNode* pNode = ownerParent->getFirstComponentByType<RenderComponent>()->getNode())
				parentNode = pNode;
		}
		currentNode = parentNode->createChildSceneNode();
		
		if (entity)
			currentNode->attachObject(entity);
	}


	void RenderComponent::createEntity()
	{
		if (meshName != "")
			entity = Game::getInstance().getRenderSystem()->getSceneManager()->createEntity(entityName, meshName);
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
		std::cout << "RenderComponent destructor called.\n";
	}


}

