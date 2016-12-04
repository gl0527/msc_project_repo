#include "RenderComponentFactory.h"

namespace Engine
{
	RenderComponent* RenderComponentFactory::create(Component::InitStruct* init)
	{
		if (RenderComponent::InitStruct* rInit = static_cast<RenderComponent::InitStruct*>(init))
			return new RenderComponent(*rInit);
		else
			return nullptr;
	}
}

