#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class TransformProcessor : public TagProcessor
	{
		virtual void addToParentObject(TiXmlElement* elem, const std::shared_ptr<Component>& component)
		{
			const auto& objectName = XMLParser::getInstance().parseString((TiXmlElement*)elem->Parent(), "name");
			const auto& object = ObjectManager::getInstance().getGameObject(objectName);
			if (auto& obj = object.lock())
			{
				obj->removeComponent(obj->getName()); // a régi transform kitörlése
				obj->addComponent(component);
			}
		}
	public:
		TransformProcessor() : TagProcessor("transformcomponent") {}
		virtual void process(TiXmlElement* elem) override;
	};

}