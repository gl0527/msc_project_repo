#include "stdafx.h"
#include "Component.h"

namespace Engine
{
	Component::Component(unsigned int id, bool uniq) : ID(id), unique(uniq)
	{
	}


	void Component::setGameObject(GameObject* object)
	{
		ownerObject = object;
	}


	Component::~Component()
	{
	}
}
