#include "MeshProcessor.h"
#include "MeshComponent.h"

namespace Engine
{
	Component* Engine::MeshProcessor::process(TiXmlElement* elem)
	{
		const char* entityName = XMLParser::getInstance().parseString(elem, "ename");
		const char* meshName = XMLParser::getInstance().parseString(elem, "mname");

		MeshComponent* meshRenderer = new MeshComponent(entityName, meshName);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			const char* childName = child->Value();

			if (strcmp(childName, "material") == 0)
			{
				const char* material = XMLParser::getInstance().parseString(child, "name");
				meshRenderer->setMaterial(material);
			}
			else if (strcmp(childName, "shadows") == 0)
			{
				bool castShadows = XMLParser::getInstance().parseBoolean(child, "value");
				meshRenderer->setCastShadows(castShadows);
			}
		}
		return meshRenderer;
	}
}

