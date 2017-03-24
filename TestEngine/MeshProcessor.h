#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class MeshProcessor : public TagProcessor
	{
	public:
		MeshProcessor() : TagProcessor("meshcomponent") {}
		virtual void process(TiXmlElement* elem) override;
	};
}