#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class CameraProcessor : public TagProcessor
	{
	public:
		CameraProcessor() : TagProcessor("cameracomponent") {}
		virtual void process(TiXmlElement* elem) override;
	};
}