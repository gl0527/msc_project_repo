#pragma once
#include "IComponentFactory.h"
#include "PhysicsComponent.h"

namespace Engine
{
	class PhysicsComponentFactory : public IComponentFactory
	{
	public:
		PhysicsComponentFactory();

		//virtual PhysicsComponent* create() override;
	};
}


