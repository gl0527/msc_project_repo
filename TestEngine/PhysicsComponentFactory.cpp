#include "PhysicsComponentFactory.h"

namespace Engine
{
	PhysicsComponent* PhysicsComponentFactory::create(Component::InitStruct* init)
	{
		/*if (PhysicsComponent::InitStruct* phyInit = static_cast<PhysicsComponent::InitStruct*>(init))
			return new PhysicsComponent(*phyInit);
		else*/
			return nullptr;
	}
}

