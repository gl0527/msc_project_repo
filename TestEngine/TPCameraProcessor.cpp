#include "TPCameraProcessor.h"
#include "TPCameraComponent.h"

namespace Engine
{
	void TPCameraProcessor::process(TiXmlElement* elem)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		int zDepth = XMLParser::getInstance().parseInt(elem, "zdepth");
		std::shared_ptr<TPCameraComponent> comp(new TPCameraComponent(name, zDepth));

		foreach_child(elem)
		{
			std::string childName(child->Value());

			if (childName == "height")
			{
				float height = XMLParser::getInstance().parseFloat(child, "value");
				comp->setCameraHeight(height);
			}
			else if (childName == "targetHeight")
			{
				float targetHeight = XMLParser::getInstance().parseFloat(child, "value");
				comp->setTargetHeight(targetHeight);
			}
			else if (childName == "distfromtarget")
			{
				float distFromTarget = XMLParser::getInstance().parseFloat(child, "value");
				comp->setCameraDist(distFromTarget);
			}
			else if (childName == "motionblend")
			{
				float motionBlend = XMLParser::getInstance().parseFloat(child, "value");
				comp->setMotionBlend(motionBlend);
			}
			else if (childName == "fixed")
			{
				bool isFixed = XMLParser::getInstance().parseBoolean(child, "value");
				comp->setFixed(isFixed);
			}
		}
		const auto& objectName = XMLParser::getInstance().parseString((TiXmlElement*)elem->Parent(), "name");
		const auto& object = ObjectManager::getInstance().getGameObject(objectName);
		object->addComponent(comp);
	}
}

