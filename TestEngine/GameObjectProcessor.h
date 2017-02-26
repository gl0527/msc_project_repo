#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class DLL_SPEC GameObjectProcessor : public TagProcessor
	{
	public:
		GameObjectProcessor() : TagProcessor("gameobject") {}
		virtual void process(TiXmlElement* elem) override;
	};
}