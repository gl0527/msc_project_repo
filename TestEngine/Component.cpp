#include "stdafx.h"
#include "Component.h"

namespace Engine
{
	Component::Component(const std::string& ident, bool uniq)
		: name(ident),
		unique(uniq),
		enabled(true),
		ownerObject(nullptr)
	{
	}


	Component::~Component()
	{
	}
}
