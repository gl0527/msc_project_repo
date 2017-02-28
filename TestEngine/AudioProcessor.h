#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class DLL_SPEC AudioProcessor : public TagProcessor
	{
	public:
		AudioProcessor() : TagProcessor("audiocomponent") {}
		virtual void process(TiXmlElement* elem) override;
	};
}