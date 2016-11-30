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
		
		template<typename IS>
		static Component* create(const std::string& T, IS* initStruct) // initstruct kimazsolazasa az xml-bol
		{ 
			if (T == "RenderComponent")
			{
				//if (RenderComponent::InitStruct* initStruct = dynamic_cast<RenderComponent::InitStruct*>(creatingStructure))
				//{
					return new RenderComponent(*initStruct);
				//}
			}
		}
	};
}


