#include "InputProcessor.h"
#include "InputComponent.h"

Component* InputProcessor::process(TiXmlElement * elem)
{
	const char* name = XMLParser::getInstance().parseString(elem, "name");
	InputComponent* input = new InputComponent(name);

	for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		const char* childName = child->Value();

		if (strcmp(childName, "movespeed") == 0)
		{
			float value = XMLParser::getInstance().parseFloat(child, "value");
			input->setMoveSpeed(value);
		}
		else if (strcmp(childName, "turnspeed") == 0)
		{
			float value = XMLParser::getInstance().parseFloat(child, "value");
			input->setTurnSpeed(value);
		}
		else if (strcmp(childName, "mousesens") == 0)
		{
			float value = XMLParser::getInstance().parseFloat(child, "value");
			input->setMouseSens(value);
		}
		else if (strcmp(childName, "maxdelay") == 0)
		{
			int value = XMLParser::getInstance().parseInt(child, "value");
			input->setMaxDelay(value);
		}
	}
	return input;
}