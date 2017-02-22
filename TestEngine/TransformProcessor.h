#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class DLL_SPEC TransformProcessor : public TagProcessor
	{
	public:
		TransformProcessor() : TagProcessor("transformcomponent") {}
		virtual void process(TiXmlElement* elem, GameObject* object) override;
	};

}