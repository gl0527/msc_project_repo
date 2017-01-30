#pragma once
#include "Component.h"
#include "tinyxml.h"
#include "stdafx.h"

namespace Engine
{
	class DLL_SPEC TagProcessor
	{
	protected:
		std::string tag;
	public:
		TagProcessor(const char* tagName);

		virtual Component* process(TiXmlElement* elem) = 0;
		const std::string& getTag() const { return tag; }
	};
}


