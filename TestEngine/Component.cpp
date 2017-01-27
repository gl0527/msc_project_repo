#include "stdafx.h"
#include "Component.h"

namespace Engine
{
	Component::Component(const std::string& ident, bool uniq)
		: id(ident),
		unique(uniq),
		enabled(true),
		ownerObject(nullptr)
	{
	}


	Component::~Component()
	{
	}
}
