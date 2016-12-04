#pragma once
#include "IComponentFactory.h"
#include "PhysicsComponent.h"

namespace Engine
{
	class PhysicsComponentFactory : public IComponentFactory
	{
	public:
		virtual PhysicsComponent* create(Component::InitStruct* init) override;
	};
}


