#pragma once
#include "IComponentFactory.h"
#include "RenderComponent.h"

namespace Engine
{
	class RenderComponentFactory : public IComponentFactory
	{
	public:
		virtual RenderComponent* create(Component::InitStruct* init) override;
	};
}


