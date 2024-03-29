#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class PhysicsProcessor : public TagProcessor
	{
	public:
		PhysicsProcessor() : TagProcessor("physicscomponent") {}
		virtual void process(TiXmlElement* elem) override;
	};
}