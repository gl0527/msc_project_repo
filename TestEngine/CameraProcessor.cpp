#include "CameraProcessor.h"
#include "CameraComponent.h"

namespace Engine
{
	void CameraProcessor::process(TiXmlElement* elem, GameObject* object)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		int zOrder = XMLParser::getInstance().parseInt(elem, "zOrder");

		auto* comp = new CameraComponent(name, zOrder);
	
		foreach_child(elem)
		{
			std::string childName(child->Value());

			if (childName == "lookat")
			{
				const auto& lookat = XMLParser::getInstance().parseFloat3_XYZ(child);
				comp->setLookAt(lookat);
			}
			else if (childName == "renderdist")
			{
				float renderDist = XMLParser::getInstance().parseFloat(child, "dist");
				comp->setRenderDist(renderDist);
			}
		}
		object->addComponent(comp);
	}
}