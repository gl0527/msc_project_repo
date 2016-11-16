#pragma once
#include "Component.h"
#include "stdafx.h"

namespace Engine
{
	class DLL_SPEC IComponentFactory
	{
		
	public:
		IComponentFactory();
		
		virtual Component* create() = 0;
	};
}


