#include "TPCameraProcessor.h"
#include "TPCameraComponent.h"

namespace Engine
{
	void TPCameraProcessor::process(TiXmlElement* elem, GameObject* object)
	{
		const std::string& name = XMLParser::getInstance().parseString(elem, "name");
		int zDepth = XMLParser::getInstance().parseInt(elem, "zdepth");
		TPCameraComponent* tpcam = new TPCameraComponent(name, zDepth);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			std::string childName(child->Value());

			if (childName == "height")
			{
				float height = XMLParser::getInstance().parseFloat(child, "value");
				tpcam->setCameraHeight(height);
			}
			else if (childName == "targetHeight")
			{
				float targetHeight = XMLParser::getInstance().parseFloat(child, "value");
				tpcam->setTargetHeight(targetHeight);
			}
			else if (childName == "distfromtarget")
			{
				float distFromTarget = XMLParser::getInstance().parseFloat(child, "value");
				tpcam->setCameraDist(distFromTarget);
			}
			else if (childName == "motionblend")
			{
				float motionBlend = XMLParser::getInstance().parseFloat(child, "value");
				tpcam->setMotionBlend(motionBlend);
			}
			else if (childName == "fixed")
			{
				bool isFixed = XMLParser::getInstance().parseBoolean(child, "value");
				tpcam->setFixed(isFixed);
			}
		}
		object->addComponent(tpcam);
	}
}

