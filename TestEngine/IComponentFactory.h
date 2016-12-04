#pragma once
#include "Component.h"
#include "stdafx.h"

namespace Engine
{
	class DLL_SPEC IComponentFactory
	{
	public:
		virtual Component* create(Component::InitStruct* init) = 0;
	};
}


