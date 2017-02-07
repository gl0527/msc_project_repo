#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class DLL_SPEC MeshProcessor : public TagProcessor
	{
	public:
		MeshProcessor() : TagProcessor("meshcomponent") {}
		virtual Component* process(TiXmlElement* elem) override;
	};
}