#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class LightProcessor : public TagProcessor
	{
	public:
		LightProcessor() : TagProcessor("lightcomponent") {}
		virtual void process(TiXmlElement* elem) override;
	};
}