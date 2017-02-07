#include "CameraProcessor.h"
#include "CameraComponent.h"

namespace Engine
{
	Component* CameraProcessor::process(TiXmlElement* elem)
	{
		const char* name = elem->Attribute("name");
		int zOrder = XMLParser::getInstance().parse1i(elem, "zOrder");

		CameraComponent* cam = new CameraComponent(name, zOrder);
	
		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			const char* childName = child->Value();

			if (strcmp(childName, "lookat") == 0)
			{
				Ogre::Vector3 lookat = XMLParser::getInstance().parse3f_XYZ(child);
				cam->setLookAt(lookat);
			}
			else if (strcmp(childName, "renderdist") == 0)
			{
				float renderDist = XMLParser::getInstance().parse1f(child, "dist");
				cam->setRenderDist(renderDist);
			}
		}
		return cam;
	}
}