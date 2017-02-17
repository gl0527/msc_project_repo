#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class DLL_SPEC TPCameraProcessor : public TagProcessor
	{
	public:
		TPCameraProcessor() : TagProcessor("tpcameracomponent") {}
		virtual Component* process(TiXmlElement* elem) override;
	};
}