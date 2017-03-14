#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class DLL_SPEC ParticleProcessor : public TagProcessor
	{
	public:
		ParticleProcessor() : TagProcessor("particlecomponent") {}
		virtual void process(TiXmlElement* elem) override;
	};

}