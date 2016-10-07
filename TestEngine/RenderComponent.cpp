#include "RenderComponent.h"
#include "GameObject.h"

namespace Engine
{
	RenderComponent::RenderComponent() : Component(0)
	{
	}

	void RenderComponent::onPostUpdate(float t, float dt)
	{
		node->setPosition(ownerObject->getPosition());
		node->setOrientation(ownerObject->getOrientation());
	}

	void RenderComponent::createNode(Ogre::SceneNode* parentNode)
	{

	}

	void RenderComponent::createEntity(const Ogre::String& entityName, const Ogre::String& meshName)
	{

	}

	RenderComponent::~RenderComponent()
	{
	}
}

