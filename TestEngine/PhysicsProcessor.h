#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class DLL_SPEC PhysicsProcessor : public TagProcessor
	{
	public:
		PhysicsProcessor() : TagProcessor("physicscomponent") {}
		virtual void process(TiXmlElement* elem, GameObject* object) override;
	};
}