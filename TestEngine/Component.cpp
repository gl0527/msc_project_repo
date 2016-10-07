#include "stdafx.h"
#include "Component.h"

namespace Engine
{
	Component::Component(unsigned int ident, bool uniq) : id(ident), unique(uniq), ownerObject(nullptr)
	{
	}


	Component::~Component()
	{
	}
}
