#pragma once
#include "TagProcessor.h"

using namespace Engine;

class DynamicMovementProcessor : public TagProcessor
{
public:
	DynamicMovementProcessor() : TagProcessor("dynamicmovementcomponent") {}
	virtual void process(TiXmlElement* elem) override;
};