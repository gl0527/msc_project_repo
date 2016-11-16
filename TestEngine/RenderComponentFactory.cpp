#include "RenderComponentFactory.h"

namespace Engine
{
	RenderComponentFactory::RenderComponentFactory(const char* eName, const char* mName)
		: entityName(eName), meshName(mName)
	{
		
	}


	RenderComponent* RenderComponentFactory::create()
	{
		return nullptr;
	}
}

