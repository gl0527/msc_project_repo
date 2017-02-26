#pragma once
#include "TagProcessor.h"

using namespace Engine;

class InputProcessor : public TagProcessor
{
public:
	InputProcessor() : TagProcessor("inputcomponent") {}
	virtual void process(TiXmlElement* elem) override;
};