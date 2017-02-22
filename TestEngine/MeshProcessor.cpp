#include "MeshProcessor.h"
#include "MeshComponent.h"

namespace Engine
{
	void Engine::MeshProcessor::process(TiXmlElement* elem, GameObject* object)
	{
		const std::string& entityName = XMLParser::getInstance().parseString(elem, "ename");
		const std::string& meshName = XMLParser::getInstance().parseString(elem, "mname");

		MeshComponent* meshRenderer = new MeshComponent(entityName, meshName);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			std::string childName(child->Value());

			if (childName == "material")
			{
				const std::string& material = XMLParser::getInstance().parseString(child, "name");
				meshRenderer->setMaterial(material.c_str());
			}
			else if (childName == "shadows")
			{
				bool castShadows = XMLParser::getInstance().parseBoolean(child, "value");
				meshRenderer->setCastShadows(castShadows);
			}
		}
		object->addComponent(meshRenderer);
	}
}

