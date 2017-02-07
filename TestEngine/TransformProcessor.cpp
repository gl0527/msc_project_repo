#include "TransformProcessor.h"
#include "TransformComponent.h"

namespace Engine
{
	Component* TransformProcessor::process(TiXmlElement* elem)
	{	
		const char* name = elem->Attribute("name");
		TransformComponent* transform = new TransformComponent(name);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			const char* childName = child->Value();
			
			if (strcmp(childName, "position") == 0)
			{	
				const Ogre::Vector3& pos = XMLParser::getInstance().parse3f_XYZ(child);
				transform->setPosition(pos);
			}
			else if (strcmp(childName, "rotation") == 0)
			{
				const Ogre::Quaternion& rot = XMLParser::getInstance().parse4f_WXYZ(child);
				transform->setRotation(rot);
			}
			else if (strcmp(childName, "scale") == 0)
			{
				const Ogre::Vector3& scale = XMLParser::getInstance().parse3f_XYZ(child);
				transform->setScale(scale);
			}
		}
		return transform;
	}
}