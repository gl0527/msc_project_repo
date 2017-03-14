#include "GameObjectProcessor.h"

namespace Engine
{
	void GameObjectProcessor::process(TiXmlElement* elem)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		const auto& object = ObjectManager::getInstance().createGameObject(name);
		object->removeComponent(name); // a régi transform kitörlése

		TiXmlElement* parent = (TiXmlElement*)elem->Parent();
		std::string parentTag(parent->Value());

		if (parentTag == "gameobject")
		{
			const auto& parentName = XMLParser::getInstance().parseString(parent, "name");
			object->setParent(parentName);
		}
	}
}

