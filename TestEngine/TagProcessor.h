#pragma once
#include "Component.h"
#include "tinyxml.h"
#include "XMLParser.h"
#include "ObjectManager.h"
#include "GameObject.h"

#define foreach_child(elem) for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())

namespace Engine
{
	class TagProcessor
	{
	protected:
		std::string tag;

		virtual void addToParentObject(TiXmlElement* elem, const std::shared_ptr<Component>& component)
		{
			const auto& objectName = XMLParser::getInstance().parseString((TiXmlElement*)elem->Parent(), "name");
			const auto& object = ObjectManager::getInstance().getGameObject(objectName);
			if (auto& obj = object.lock())
				obj->addComponent(component);
		}
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


