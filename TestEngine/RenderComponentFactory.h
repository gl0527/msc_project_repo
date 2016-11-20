#pragma once
#include "IComponentFactory.h"
#include "RenderComponent.h"

namespace Engine
{
	class RenderComponentFactory : public IComponentFactory
	{
		const char* entityName;
		const char* meshName;
	public:
		RenderComponentFactory(const char* eName, const char* mName);

		//virtual RenderComponent* create() override;
	};
}


