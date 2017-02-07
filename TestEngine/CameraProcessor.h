#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class DLL_SPEC CameraProcessor : public TagProcessor
	{
	public:
		CameraProcessor() : TagProcessor("cameracomponent") {}
		virtual Component* process(TiXmlElement* elem) override;
	};
}