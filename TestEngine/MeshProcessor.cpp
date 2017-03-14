
#include "MeshProcessor.h"
#include "MeshComponent.h"

namespace Engine
{
	void Engine::MeshProcessor::process(TiXmlElement* elem)
	{
		const auto& entityName = XMLParser::getInstance().parseString(elem, "ename");
		const auto& meshName = XMLParser::getInstance().parseString(elem, "mname");

		std::shared_ptr<MeshComponent> comp(new MeshComponent(entityName, meshName));

		foreach_child(elem)
		{
			std::string childName(child->Value());

			if (childName == "material")
			{
				const auto& material = XMLParser::getInstance().parseString(child, "name");
				comp->setMaterial(material);
			}
			else if (childName == "shadows")
			{
				bool castShadows = XMLParser::getInstance().parseBoolean(child, "value");
				comp->setCastShadows(castShadows);
			}
		}
		const auto& objectName = XMLParser::getInstance().parseString((TiXmlElement*)elem->Parent(), "name");
		const auto& object = ObjectManager::getInstance().getGameObject(objectName);
		object->addComponent(comp);
	}
}

