#pragma once
#include "Component.h"
#include "tinyxml.h"
#include "stdafx.h"
#include "XMLParser.h"
#include "ObjectManager.h"
#include "GameObject.h"

#define foreach_child(elem) for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())

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

		virtual void process(TiXmlElement* elem) = 0;
		const std::string& getTag() const { return tag; }
	};
}


