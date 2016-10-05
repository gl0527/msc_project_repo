#pragma once
#include "Component.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
		float mass;
		bool isTrigger;
	public:
		PhysicsComponent();
		~PhysicsComponent();
	};

}

