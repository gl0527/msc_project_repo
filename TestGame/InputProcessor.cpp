#include "InputProcessor.h"
#include "InputComponent.h"

void InputProcessor::process(TiXmlElement* elem)
{
	const auto& name = XMLParser::getInstance().parseString(elem, "name");
	std::shared_ptr<InputComponent> comp(new InputComponent(name));

	addToParentObject(elem, comp);

	foreach_child(elem)
	{
		std::string childName(child->Value());

		if (childName == "movespeed")
		{
			float value = XMLParser::getInstance().parseFloat(child, "value");
			comp->setMoveSpeed(value);
		}
		else if (childName == "turnspeed")
		{
			float value = XMLParser::getInstance().parseFloat(child, "value");
			comp->setTurnSpeed(value);
		}
		else if (childName == "mousesens")
		{
			float value = XMLParser::getInstance().parseFloat(child, "value");
			comp->setMouseSens(value);
		}
		else if (childName == "maxdelay")
		{
			int value = XMLParser::getInstance().parseInt(child, "value");
			comp->setMaxDelay(value);
		}
	}
}