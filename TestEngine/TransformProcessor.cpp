#include "TransformProcessor.h"
#include "TransformComponent.h"

namespace Engine
{
	Component* TransformProcessor::process(TiXmlElement* elem)
	{
		if(strcmp(elem->Value(), tag.c_str()) != 0)
			return nullptr;
		
		const char* name = elem->Attribute("name");
		TransformComponent* transform = new TransformComponent(name);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			const char* childTag = child->Value();
			
			if (strcmp(childTag, "position") == 0)
			{
				float x, y, z;

				child->QueryFloatAttribute("x", &x);
				child->QueryFloatAttribute("y", &y);
				child->QueryFloatAttribute("z", &z);

				Ogre::Vector3 pos(x,y,z);

				transform->setPosition(pos);
			}
			else if (strcmp(childTag, "rotation") == 0)
			{
				float qx, qy, qz, qw;

				child->QueryFloatAttribute("qx", &qx);
				child->QueryFloatAttribute("qy", &qy);
				child->QueryFloatAttribute("qz", &qz);
				child->QueryFloatAttribute("qw", &qw);

				Ogre::Quaternion rot(qw, qx, qy, qz);

				transform->setRotation(rot);
			}
			else if (strcmp(childTag, "scale") == 0)
			{
				float x, y, z;

				child->QueryFloatAttribute("x", &x);
				child->QueryFloatAttribute("y", &y);
				child->QueryFloatAttribute("z", &z);

				Ogre::Vector3 scale(x, y, z);

				transform->setScale(scale);
			}
		}
		return transform;
	}
}