#include "TransformProcessor.h"
#include "TransformComponent.h"

namespace Engine
{
	void TransformProcessor::process(TiXmlElement* elem)
	{	
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		std::shared_ptr<TransformComponent> comp(new TransformComponent(name));

		foreach_child(elem)
		{
			std::string childName(child->Value());
			
			if (childName == "position")
			{	
				const auto& pos = XMLParser::getInstance().parseFloat3_XYZ(child);
				comp->setPosition(pos);
			}
			else if (childName == "rotation")
			{
				const auto& rot = XMLParser::getInstance().parseFloat4_WXYZ(child);
				comp->setRotation(rot);
			}
			else if (childName == "scale")
			{
				const auto& scale = XMLParser::getInstance().parseFloat3_XYZ(child);
				comp->setScale(scale);
			}
		}
		const auto& objectName = XMLParser::getInstance().parseString((TiXmlElement*)elem->Parent(), "name");
		const auto& object = ObjectManager::getInstance().getGameObject(objectName);
		object->addComponent(comp);
	}
}