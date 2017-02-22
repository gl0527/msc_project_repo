#pragma once
#include "Component.h"
#include "tinyxml.h"
#include "stdafx.h"
#include "XMLParser.h"
#include "GameObject.h"

namespace Engine
{
	class DLL_SPEC TagProcessor
	{
	protected:
		std::string tag;
	public:
		TagProcessor(const std::string& tagName)
			: tag(tagName)
		{
			XMLParser::getInstance().addProcessor(this); 
		}

		virtual void process(TiXmlElement* elem, GameObject* object) = 0;
		const std::string& getTag() const { return tag; }
	};
}


