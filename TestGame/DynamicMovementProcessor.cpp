#include "DynamicMovementProcessor.h"
#include "DynamicMovementComponent.h"

void DynamicMovementProcessor::process(TiXmlElement* elem)
{
	const auto& name = XMLParser::getInstance().parseString(elem, "name");
	std::shared_ptr<DynamicMovementComponent> comp(new DynamicMovementComponent(name));

	addToParentObject(elem, comp);

	foreach_child(elem)
	{
		std::string childName(child->Value());

		if (childName == "speed")
		{
			float speed = XMLParser::getInstance().parseFloat(child, "value");
			comp->setMoveSpeed(speed);
		}
	}
}
