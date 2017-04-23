#include "GameObjectProcessor.h"

namespace Engine
{
	void GameObjectProcessor::process(TiXmlElement* elem)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		const auto& object = ObjectManager::getInstance().createGameObject(name);

		if (auto& obj = object.lock())
		{
			auto parent = (TiXmlElement*)elem->Parent();
			std::string parentTag(parent->Value());

			if (parentTag == "gameobject")
			{
				const auto& parentName = XMLParser::getInstance().parseString(parent, "name");
				obj->setParent(parentName);
			}
		}
	}
}

