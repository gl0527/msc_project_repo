#include "InputProcessor.h"
#include "InputComponent.h"

void InputProcessor::process(TiXmlElement* elem)
{
	const auto& name = XMLParser::getInstance().parseString(elem, "name");
	std::shared_ptr<InputComponent> comp(new InputComponent(name));

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
	const auto& objectName = XMLParser::getInstance().parseString((TiXmlElement*)elem->Parent(), "name");
	const auto& object = ObjectManager::getInstance().getGameObject(objectName);
	object->addComponent(comp);
}