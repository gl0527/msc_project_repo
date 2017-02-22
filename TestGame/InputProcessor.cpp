#include "InputProcessor.h"
#include "InputComponent.h"

void InputProcessor::process(TiXmlElement * elem, GameObject* object)
{
	const std::string& name = XMLParser::getInstance().parseString(elem, "name");
	InputComponent* input = new InputComponent(name);

	for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		std::string childName(child->Value());

		if (childName == "movespeed")
		{
			float value = XMLParser::getInstance().parseFloat(child, "value");
			input->setMoveSpeed(value);
		}
		else if (childName == "turnspeed")
		{
			float value = XMLParser::getInstance().parseFloat(child, "value");
			input->setTurnSpeed(value);
		}
		else if (childName == "mousesens")
		{
			float value = XMLParser::getInstance().parseFloat(child, "value");
			input->setMouseSens(value);
		}
		else if (childName == "maxdelay")
		{
			int value = XMLParser::getInstance().parseInt(child, "value");
			input->setMaxDelay(value);
		}
	}
	object->addComponent(input);
}