#pragma once
#include "Component.h"
#include "stdafx.h"
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC IComponentFactory
	{
		
	public:
		IComponentFactory();
		
		template<class T>
		static Component* create(const std::string& compType, T* creatingStructure)
		{ 
			if (compType == "RenderComponent")
			{
				//if (RenderComponent::InitStruct* initStruct = dynamic_cast<RenderComponent::InitStruct*>(creatingStructure))
				//{
					return new RenderComponent(*creatingStructure);
				//}
			}
		}
	};
}


