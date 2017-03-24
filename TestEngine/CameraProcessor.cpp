#include "CameraProcessor.h"
#include "CameraComponent.h"

namespace Engine
{
	void CameraProcessor::process(TiXmlElement* elem)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		int zOrder = XMLParser::getInstance().parseInt(elem, "zOrder");

		std::shared_ptr<CameraComponent> comp(new CameraComponent(name, zOrder));

		foreach_child(elem)
		{
			std::string childName(child->Value());
			
			if (childName == "frustum")
			{
				float nearPlane = XMLParser::getInstance().parseFloat(child, "near");
				float farPlane = XMLParser::getInstance().parseFloat(child, "far");
				comp->setNearClip(nearPlane);
				comp->setFarClip(farPlane);
			}
			else if (childName == "height")
			{
				float height = XMLParser::getInstance().parseFloat(child, "value");
				comp->setHeight(height);
			}
			else if (childName == "lookat")
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
		addToParentObject(elem, comp);
	}
}