#include "GameObjectProcessor.h"

namespace Engine
{
	void GameObjectProcessor::process(TiXmlElement* elem)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		const auto& object = ObjectManager::getInstance().createGameObject(name);
		object->removeComponent(name); // a régi transform kitörlése
	}
}

