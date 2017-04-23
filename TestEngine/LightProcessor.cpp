#include "LightProcessor.h"
#include "LightComponent.h"

namespace Engine
{
	void LightProcessor::process(TiXmlElement* elem)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		const auto& type = XMLParser::getInstance().parseString(elem, "type");
		Ogre::Light::LightTypes lightType;
		
		if (type == "point")
			lightType = Ogre::Light::LT_POINT;
		else if (type == "directional")
			lightType = Ogre::Light::LT_DIRECTIONAL;
		else if(type == "spot")
			lightType = Ogre::Light::LT_SPOTLIGHT;
		
		std::shared_ptr<LightComponent> comp(new LightComponent(name, lightType));

		addToParentObject(elem, comp);

		foreach_child(elem)
		{
			std::string childName(child->Value());

			if (childName == "diffusecolor")
			{
				const auto& diffCol = XMLParser::getInstance().parseFloat3_RGB(child);
				comp->setDiffuseColor(diffCol);
			}
			else if (childName == "specularcolor")
			{
				const auto& specCol = XMLParser::getInstance().parseFloat3_RGB(child);
				comp->setSpecularColor(specCol);
			}
			else if (childName == "intensity")
			{
				float intensity = XMLParser::getInstance().parseFloat(child, "value");
				comp->setIntensity(intensity);
			}
			else if (childName == "attenuation")
			{
				float range = XMLParser::getInstance().parseFloat(child, "range");
				float constant = XMLParser::getInstance().parseFloat(child, "constant");
				float linear = XMLParser::getInstance().parseFloat(child, "linear");
				float quadric = XMLParser::getInstance().parseFloat(child, "quadric");
				comp->setAttenuation(range, constant, linear, quadric);
			}
			else if (childName == "angle")
			{
				float inner = XMLParser::getInstance().parseFloat(child, "inner");
				float outer = XMLParser::getInstance().parseFloat(child, "outer");
				comp->setSpotRange(Ogre::Degree(inner), Ogre::Degree(outer));
			}
		}
	}
}