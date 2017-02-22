#include "CameraProcessor.h"
#include "CameraComponent.h"

namespace Engine
{
	void CameraProcessor::process(TiXmlElement* elem, GameObject* object)
	{
		const std::string& name = XMLParser::getInstance().parseString(elem, "name");
		int zOrder = XMLParser::getInstance().parseInt(elem, "zOrder");

		CameraComponent* cam = new CameraComponent(name, zOrder);
	
		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			std::string childName(child->Value());

			if (childName == "lookat")
			{
				Ogre::Vector3 lookat = XMLParser::getInstance().parseFloat3_XYZ(child);
				cam->setLookAt(lookat);
			}
			else if (childName == "renderdist")
			{
				float renderDist = XMLParser::getInstance().parseFloat(child, "dist");
				cam->setRenderDist(renderDist);
			}
		}
		object->addComponent(cam);
	}
}