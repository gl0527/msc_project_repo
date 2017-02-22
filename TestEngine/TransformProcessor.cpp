#include "TransformProcessor.h"
#include "TransformComponent.h"

namespace Engine
{
	void TransformProcessor::process(TiXmlElement* elem, GameObject* object)
	{	
		const std::string& name = XMLParser::getInstance().parseString(elem, "name");
		TransformComponent* transform = new TransformComponent(name);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			std::string childName(child->Value());
			
			if (childName == "position")
			{	
				const Ogre::Vector3& pos = XMLParser::getInstance().parseFloat3_XYZ(child);
				transform->setPosition(pos);
			}
			else if (childName == "rotation")
			{
				const Ogre::Quaternion& rot = XMLParser::getInstance().parseFloat4_WXYZ(child);
				transform->setRotation(rot);
			}
			else if (childName == "scale")
			{
				const Ogre::Vector3& scale = XMLParser::getInstance().parseFloat3_XYZ(child);
				transform->setScale(scale);
			}
		}
		object->addComponent(transform);
	}
}