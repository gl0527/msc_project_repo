#include "TransformProcessor.h"
#include "TransformComponent.h"

namespace Engine
{
	void TransformProcessor::process(TiXmlElement* elem, GameObject* object)
	{	
		const char* name = XMLParser::getInstance().parseString(elem, "name");
		TransformComponent* transform = new TransformComponent(name);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			const char* childName = child->Value();
			
			if (strcmp(childName, "position") == 0)
			{	
				const Ogre::Vector3& pos = XMLParser::getInstance().parseFloat3_XYZ(child);
				transform->setPosition(pos);
			}
			else if (strcmp(childName, "rotation") == 0)
			{
				const Ogre::Quaternion& rot = XMLParser::getInstance().parseFloat4_WXYZ(child);
				transform->setRotation(rot);
			}
			else if (strcmp(childName, "scale") == 0)
			{
				const Ogre::Vector3& scale = XMLParser::getInstance().parseFloat3_XYZ(child);
				transform->setScale(scale);
			}
		}
		object->addComponent(transform);
	}
}