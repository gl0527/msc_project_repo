#include "RenderComponent.h"
#include "GameObject.h"

namespace Engine
{
	RenderComponent::RenderComponent(const std::string& name)
		: Component(name),
		parentNode(nullptr),
		currentNode(nullptr),
		object(nullptr),
		objName(name)
	{
		parentNode = Game::getInstance().getRenderSystem()->getRootNode();
		sceneMgr = Game::getInstance().getRenderSystem()->getSceneManager();
	}


	void RenderComponent::onStart()
	{
		createNode();
		currentNode->attachObject(object);
	}


	void RenderComponent::onPostUpdate(float t, float dt)
	{
		currentNode->setPosition(ownerObject->transform()->position());
		currentNode->setOrientation(ownerObject->transform()->rotation());
		currentNode->setScale(ownerObject->transform()->scale());
	}


	void RenderComponent::createNode()
	{
		const auto& ownerParent = ownerObject->getParent();
		if (ownerParent)
		{	
			if (Ogre::SceneNode* pNode = ownerParent->getFirstComponentByType<RenderComponent>()->getNode())
				parentNode = pNode;
		}
		currentNode = parentNode->createChildSceneNode();
	}


	void RenderComponent::onDestroy()
	{
		sceneMgr->destroySceneNode(currentNode);
		currentNode = nullptr;
	}


	RenderComponent::~RenderComponent()
	{
		std::cout << "RenderComponent destructor called.\n";
	}


	void RenderComponent::setCastShadows(bool cast)
	{
		if (object)
			object->setCastShadows(cast);
	}


	void RenderComponent::setVisible(bool visible)
	{
		if (object)
			object->setVisible(visible);
	}


}

