#include "TPCameraProcessor.h"
#include "TPCameraComponent.h"

namespace Engine
{
	Component* TPCameraProcessor::process(TiXmlElement* elem)
	{
		const char* name = XMLParser::getInstance().parseString(elem, "name");
		int zDepth = XMLParser::getInstance().parseInt(elem, "zdepth");
		TPCameraComponent* tpcam = new TPCameraComponent(name, zDepth);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			const char* childName = child->Value();

			if (strcmp(childName, "height") == 0)
			{
				float height = XMLParser::getInstance().parseFloat(child, "value");
				tpcam->setCameraHeight(height);
			}
			else if (strcmp(childName, "targetHeight") == 0)
			{
				float targetHeight = XMLParser::getInstance().parseFloat(child, "value");
				tpcam->setTargetHeight(targetHeight);
			}
			else if (strcmp(childName, "distfromtarget") == 0)
			{
				float distFromTarget = XMLParser::getInstance().parseFloat(child, "value");
				tpcam->setCameraDist(distFromTarget);
			}
			else if (strcmp(childName, "motionblend") == 0)
			{
				float motionBlend = XMLParser::getInstance().parseFloat(child, "value");
				tpcam->setMotionBlend(motionBlend);
			}
			else if (strcmp(childName, "fixed") == 0)
			{
				bool isFixed = XMLParser::getInstance().parseBoolean(child, "value");
				tpcam->setFixed(isFixed);
			}
		}
		return tpcam;
	}
}

