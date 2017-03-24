#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class TPCameraProcessor : public TagProcessor
	{
	public:
		TPCameraProcessor() : TagProcessor("tpcameracomponent") {}
		virtual void process(TiXmlElement* elem) override;
	};
}