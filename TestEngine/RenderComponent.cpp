#include "RenderComponent.h"
#include "GameObject.h"

namespace Engine
{
	RenderComponent::RenderComponent(const std::string& name)
		: Component(name),
		parentNode(Game::getInstance().getRenderSystem()->getRootNode()),
		currentNode(nullptr),
		object(nullptr),
		sceneMgr(Game::getInstance().getRenderSystem()->getSceneManager())
	{

	}


	void RenderComponent::onInit(GameObject* obj)
	{
		ownerObject = obj;
		createNode();
		currentNode->attachObject(object);
	}


	void RenderComponent::onPostUpdate(float t, float dt)
	{
		currentNode->setPosition(ownerObject->transform()->position());
		currentNode->setOrientation(ownerObject->transform()->rotation());
		currentNode->setScale(ownerObject->transform()->scale());
	}


	void RenderComponent::onDestroy()
	{
		sceneMgr->destroySceneNode(currentNode);
		currentNode = nullptr;
	}


	void RenderComponent::createNode()
	{
		if (const auto& ownerParent = ownerObject->getParent().lock())
		
		{	
			if (const auto& ownerRenderer = ownerParent->getFirstComponentByType<RenderComponent>().lock())
			{
				if (auto pNode = ownerRenderer->getNode())
					parentNode = pNode;
			}
		}
		currentNode = parentNode->createChildSceneNode();
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

