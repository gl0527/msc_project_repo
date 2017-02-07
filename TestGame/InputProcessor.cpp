#include "InputProcessor.h"
#include "InputComponent.h"

Component* InputProcessor::process(TiXmlElement * elem)
{
	const char* name = elem->Attribute("name");
	InputComponent* input = new InputComponent(name);

	for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
	{
		const char* childName = child->Value();

		if (strcmp(childName, "movespeed") == 0)
		{
			float value = XMLParser::getInstance().parse1f(child, "value");
			input->setMoveSpeed(value);
		}
		else if (strcmp(childName, "turnspeed") == 0)
		{
			float value = XMLParser::getInstance().parse1f(child, "value");
			input->setTurnSpeed(value);
		}
		else if (strcmp(childName, "mousesens") == 0)
		{
			float value = XMLParser::getInstance().parse1f(child, "value");
			input->setMouseSens(value);
		}
		else if (strcmp(childName, "maxdelay") == 0)
		{
			int value = XMLParser::getInstance().parse1i(child, "value");
			input->setMaxDelay(value);
		}
	}
	return input;
}