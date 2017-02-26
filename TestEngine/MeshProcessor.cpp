#include "MeshProcessor.h"
#include "MeshComponent.h"

namespace Engine
{
	void Engine::MeshProcessor::process(TiXmlElement* elem, GameObject* object)
	{
		const auto& entityName = XMLParser::getInstance().parseString(elem, "ename");
		const auto& meshName = XMLParser::getInstance().parseString(elem, "mname");

		auto* comp = new MeshComponent(entityName, meshName);

		foreach_child(elem)
		{
			std::string childName(child->Value());

			if (childName == "material")
			{
				const auto& material = XMLParser::getInstance().parseString(child, "name");
				comp->setMaterial(material.c_str());
			}
			else if (childName == "shadows")
			{
				bool castShadows = XMLParser::getInstance().parseBoolean(child, "value");
				comp->setCastShadows(castShadows);
			}
		}
		object->addComponent(comp);
	}
}

